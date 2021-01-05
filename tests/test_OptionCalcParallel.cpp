#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <spdlog/spdlog.h>
#include <OptionCalcParallel/MCEuroOptPricer.h>

TEST_CASE("OptionCalcParallel") {

  SECTION("Sequential") {
    double strike = 102.0;
    double spot = 100.0;
    double riskFreeRate = 0.025;
    double volatility = 0.06;
    double quantity = 1.00;	// 1.0;  (Number of contracts)
    unsigned numTimeSteps = 120;		// 5 years, quarterly time steps
    double tau = 5.0;
    int numScenarios = 10000;
    int initSeed = -106;
    OptionType call = OptionType::CALL;

    MCEuroOptPricer qlCall(strike, spot, riskFreeRate, volatility, tau,
                           call, numTimeSteps, numScenarios, false, initSeed, quantity);

    double res = qlCall();
    spdlog::info("Number of time steps = {}, number of scenarios = {}" , numTimeSteps ,numScenarios);
    spdlog::info("Runtime (NOT in parallel) = {} ms, price = {}", qlCall.time(), res);

    REQUIRE(res == Approx(11.6278));

  }

  SECTION("Parallel") {
    double strike = 102.0;
    double spot = 100.0;
    double riskFreeRate = 0.025;
    double volatility = 0.06;
    double quantity = 1.00;	// 1.0;  (Number of contracts)
    unsigned numTimeSteps = 120;		// 5 years, quarterly time steps
    double tau = 5.0;
    int numScenarios = 10000;
    int initSeed = -106;
    OptionType call = OptionType::CALL;

    MCEuroOptPricer qlCall(strike, spot, riskFreeRate, volatility, tau,
                           call, numTimeSteps, numScenarios, true, initSeed, quantity);

    double res = qlCall();

    spdlog::info("Number of time steps = {}, number of scenarios = {}" , numTimeSteps ,numScenarios);
    spdlog::info("Runtime (IS RUN in parallel) = {} ms, price = {}", qlCall.time(), res);

    REQUIRE(res == Approx(11.6278));

  }
}
