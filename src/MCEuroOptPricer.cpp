//
// Created by suhasghorp on 1/2/2021.
//

#include <OptionCalcParallel/MCEuroOptPricer.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <future>
#include <limits>
#include <execution>
#include <memory>

MCEuroOptPricer::MCEuroOptPricer(double strike, double spot, double riskFreeRate, double volatility,
                                 double timeToExpiry, OptionType porc, int numTimeSteps, int numScenarios,
                                 bool runParallel, int initSeed, double quantity) :strike_(strike), spot_(spot),
                                                                                   riskFreeRate_(riskFreeRate), volatility_(volatility), timeToExpiry_(timeToExpiry), porc_(porc),
                                                                                   numTimeSteps_(numTimeSteps), numScenarios_(numScenarios), runParallel_(runParallel),
                                                                                   initSeed_(initSeed), quantity_(quantity)
{
    discFactor_ = std::exp(-riskFreeRate_ * timeToExpiry_);
    calculate_();
}

double MCEuroOptPricer::operator()() const
{
    return price_;
}

double MCEuroOptPricer::time() const
{
    return time_;
}

void MCEuroOptPricer::calculate_()
{
    const auto start = std::chrono::steady_clock::now();
    computePrice_();
    const auto end = std::chrono::steady_clock::now();
    time_ = std::chrono::duration <double, std::milli>(end - start).count();
}

// Private helper functions:
void MCEuroOptPricer::computePrice_()
{
    if (runParallel_)
    {
        computePriceAsync_();
    }
    else
    {
        computePriceNoParallel_();
    }
}

void MCEuroOptPricer::computePriceNoParallel_()
{
    std::unique_ptr<EquityPriceGenerator> epg(std::make_unique<EquityPriceGenerator>(spot_, numTimeSteps_, timeToExpiry_, riskFreeRate_, volatility_));
    generateSeeds_();

    std::vector<double> discountedPayoffs(numScenarios_, 0.0);

    std::transform(std::execution::seq,
                   seeds_.begin(), seeds_.end(), discountedPayoffs.begin(),
                   [&](auto s) {
                       std::vector<double> prices = epg->operator()(s);
                       double terminalPrice = prices.back();
                       double payoff = payoff_(terminalPrice);
                       return discFactor_ * payoff;
                   }
    );

    double numScens = static_cast<double>(numScenarios_);
    price_ = quantity_ * (1.0 / numScens) *
             std::accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);
}

void MCEuroOptPricer::computePriceAsync_()
{
    std::unique_ptr<EquityPriceGenerator> epg(std::make_unique<EquityPriceGenerator>(spot_, numTimeSteps_, timeToExpiry_, riskFreeRate_, volatility_));
    generateSeeds_();

    std::vector<double> discountedPayoffs(numScenarios_, 0.0);

    std::transform(std::execution::par,
                   seeds_.begin(), seeds_.end(), discountedPayoffs.begin(),
                   [&](auto s) {
                       std::vector<double> prices = epg->operator()(s);
                       double terminalPrice = prices.back();
                       double payoff = payoff_(terminalPrice);
                       return discFactor_ * payoff;
                    }
    );

    double numScens = static_cast<double>(numScenarios_);
    price_ = quantity_ * (1.0 / numScens) *
             std::accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);
}

void MCEuroOptPricer::generateSeeds_()
{
    seeds_.resize(numScenarios_);

    // This is a contrived way of setting a different seed for
    // each scenario.  There are more robust ways to do this if desired.
    std::iota(seeds_.begin(), seeds_.end(), initSeed_);
}

double MCEuroOptPricer::payoff_(double terminalPrice)
{
    double payoff = 0.0;
    switch (porc_)
    {
        case OptionType::CALL:
            payoff = std::max(terminalPrice - strike_, 0.0);
            break;
        case OptionType::PUT:
            payoff = std::max(strike_ - terminalPrice, 0.0);
            break;
        default:	// This case should NEVER happen
            payoff = std::numeric_limits<double>::quiet_NaN();
            break;
    }
    return payoff;
}
