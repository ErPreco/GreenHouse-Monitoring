#include "uniformdistribution.h"

UniformDistribution::UniformDistribution(double _min, double _max)
: Distribution("Uniform", _min, _max), maxDelta(_max - _min) {}

UniformDistribution::UniformDistribution(double _min, double _max, unsigned int _hours)
: Distribution("Uniform", _min, _max, _hours), maxDelta(_max - _min) {}


UniformDistribution* UniformDistribution::clone() const {
    return new UniformDistribution(*this);
}

// getters

double UniformDistribution::getMaxDelta() const {
    return maxDelta;
}

// setters

void UniformDistribution::setMaxDelta(double _v) {
    maxDelta = _v;
}

// data

void UniformDistribution::validParams(const std::vector<double>& _params) const {
    Distribution::validParams(_params);
    // maxDelta check
    if (_params[3] < 0)
        throw InvalidDistributionParams("\"maximum delta\" must be greater or equal to 0.");
}

std::vector<double> UniformDistribution::generateDistribution() const {
    std::vector<double> v;
    srand(time(0));
    double f = (double)rand() / RAND_MAX;
    v.push_back(getMin() + f * (max - min));
    for (unsigned int x = 1; x < hours + 1; x++) {
        float value;
        do {
            f = (double)rand() / RAND_MAX;
            // adds a random positive or negative delta to the previous data between 0 and maxDelta
            value = v[x - 1] + maxDelta * (f * 2 - 1);
        } while (value < min || value > max);
        v.push_back(value);
    }
    
    return v;
}

// visitor

void UniformDistribution::accept(IDistributionVisitor& _visitor) {
    _visitor.visit(*this);
}

void UniformDistribution::accept(IDistributionConstVisitor& _visitor) const {
    _visitor.visit(*this);
}
