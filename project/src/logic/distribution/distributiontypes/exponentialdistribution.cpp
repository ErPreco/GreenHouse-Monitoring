#include "exponentialdistribution.h"

ExponentialDistribution::ExponentialDistribution(double _min, double _max, double _lambda)
: Distribution("Exponential", _min, _max), lambda(_lambda) {}

ExponentialDistribution::ExponentialDistribution(double _min, double _max, double _lambda, unsigned int _hours)
: Distribution("Exponential", _min, _max, _hours), lambda(_lambda) {}

ExponentialDistribution* ExponentialDistribution::clone() const {
    return new ExponentialDistribution(*this);
}

// getter

double ExponentialDistribution::getLambda() const {
    return lambda;
}

// setter

void ExponentialDistribution::setLambda(double _v) {
    lambda = _v;
}

// data

void ExponentialDistribution::validParams(const std::vector<double>& _params) const {
    Distribution::validParams(_params);
    // lambda check
    if (_params[3] <= 0.0)
        throw InvalidDistributionParams("\"lambda\" must be strictly greater than 0.");
}

std::vector<double> ExponentialDistribution::generateDistribution() const {
    std::vector<double> v;
    srand(time(0));
    // creates noise to vary
    double p = 0.4;
    double f = (double)rand() / RAND_MAX;
    double lambdaNoise = lambda * p * (2 * f - 1);

    // generates data
    unsigned int samples = hours + 1;
    double data[samples] = {};
    for (unsigned int x = 0; x < samples; x++)
        data[x] = (lambda + lambdaNoise) * exp(-(lambda + lambdaNoise) * x);
    
    // shifts the data in the sensor interval
    double a = data[samples - 1];
    double b = data[0];
    for (unsigned int i = 0; i < samples; i++) {
        double shiftedValue = min + ((max - min) / (b - a)) * (data[i] - a);
        v.push_back(shiftedValue);
    }

    return v;
}

// visitor

void ExponentialDistribution::accept(IDistributionVisitor& _visitor) {
    _visitor.visit(*this);
}

void ExponentialDistribution::accept(IDistributionConstVisitor& _visitor) const {
    _visitor.visit(*this);
}
