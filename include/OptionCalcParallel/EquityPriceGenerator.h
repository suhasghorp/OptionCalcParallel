//
// Created by suhasghorp on 1/2/2021.
//

#ifndef OPTIONCALC_EQUITYPRICEGENERATOR_H
#define OPTIONCALC_EQUITYPRICEGENERATOR_H

#include <vector>

class EquityPriceGenerator {
public:
  /// Generates Equity Price scenarios using the Stochastic Diff Eq
  /// S(t) = S(t-1) * exp [(drift - (vol^2/2)) * dt + vol * std.norm.var * sqrt(dt)]
  /// \param initEquityPrice - Spot Price
  /// \param numTimeSteps - 4 Steps per year in this example
  /// \param timeToExpiry - years
  /// \param drift - Risk free rate
  /// \param volatility - 6% assumed
    EquityPriceGenerator(double initEquityPrice, unsigned numTimeSteps, double timeToExpiry, double drift, double volatility);
    std::vector<double> operator()(int seed) const;

private:
    double dt_;
    const double initEquityPrice_;
    const int numTimeSteps_;
    const double drift_;
    const double volatility_;

};


#endif //OPTIONCALC_EQUITYPRICEGENERATOR_H
