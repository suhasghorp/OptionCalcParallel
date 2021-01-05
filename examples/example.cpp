#include <OptionCalcParallel/MCEuroOptPricer.h>
#include <iostream>
#include <algorithm>
#include <spdlog/spdlog.h>

void mcOptionTestNotParallel(double tau, int numTimeSteps, int numScenarios, int initSeed = 100);
void mcOptionTestRunParallel(double tau, int numTimeSteps, int numScenarios, int initSeed = 100);

int main() {
  unsigned numTimeSteps = 120;		// 5 years, quarterly time steps
  double timeToMaturity = 5.0;

  mcOptionTestNotParallel(timeToMaturity, numTimeSteps, 10000);
  mcOptionTestRunParallel(timeToMaturity, numTimeSteps, 10000);
}


void mcOptionTestNotParallel(double tau, int numTimeSteps, int numScenarios, int initSeed)
{
  spdlog::info("--- mcOptionTestNotParallel(tau = {} ,numTimeSteps = {} ,numScenarios = {}", tau, numTimeSteps,numScenarios);

  double strike = 102.0;
  double spot = 100.0;
  double riskFreeRate = 0.025;
  double volatility = 0.06;
  double quantity = 1.00;	// 1.0;

  MCEuroOptPricer qlCall(strike, spot, riskFreeRate, volatility, tau,
                         OptionType::CALL, numTimeSteps, numScenarios, false, initSeed, quantity);
  double res = qlCall();
  spdlog::info("Number of time steps = {}, number of scenarios = {}" , numTimeSteps ,numScenarios);
  spdlog::info("Runtime (IS RUN in parallel) = {} ms, price = {}", qlCall.time(), res);

}

void mcOptionTestRunParallel(double tau, int numTimeSteps, int numScenarios, int initSeed)
{
  spdlog::info("--- mcOptionTestParallel(tau = {} ,numTimeSteps = {} ,numScenarios = {}", tau, numTimeSteps,numScenarios);

  double strike = 102.0;
  double spot = 100.0;
  double riskFreeRate = 0.025;
  double volatility = 0.06;
  double quantity = 1.00;	// 1.0;  (Number of contracts)
  OptionType call = OptionType::CALL;

  MCEuroOptPricer qlCall(strike, spot, riskFreeRate, volatility, tau,
                         call, numTimeSteps, numScenarios, true, initSeed, quantity);

  double res = qlCall();
  spdlog::info("Number of time steps = {}, number of scenarios = {}" , numTimeSteps ,numScenarios);
  spdlog::info("Runtime (NOT in parallel) = {} ms, price = {}", qlCall.time(), res);
}

