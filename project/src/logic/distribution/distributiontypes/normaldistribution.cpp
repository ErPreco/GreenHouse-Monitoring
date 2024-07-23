#include "normaldistribution.h"

NormalDistribution::NormalDistribution(double _min, double _max, double _mean, double _stddev)
: Distribution("Normal", _min, _max), mean(_mean), stddev(_stddev) {}

NormalDistribution::NormalDistribution(double _min, double _max, double _mean, double _stddev, unsigned int _hours)
: Distribution("Normal", _min, _max, _hours), mean(_mean), stddev(_stddev) {}

NormalDistribution* NormalDistribution::clone() const {
    return new NormalDistribution(*this);
}

// getters

double NormalDistribution::getMean() const {
    return mean;
}

double NormalDistribution::getStddev() const {
    return stddev;
}

// setters

void NormalDistribution::setMean(double _v) {
    mean = _v;
}

void NormalDistribution::setStddev(double _v) {
    stddev = _v;
}

// data

void NormalDistribution::validParams(const std::vector<double>& _params) const {
    Distribution::validParams(_params);
    // stddev check
    if (_params[4] == 0.0)
        throw InvalidDistributionParams("\"standard deviation\" cannot be equal to 0.");
}

std::vector<double> NormalDistribution::generateDistribution() const {
    std::vector<double> v;
    srand(time(0));
    // creates noise to vary
    double p = 0.25;
    double f = (double)rand() / RAND_MAX;
    double meanNoise = mean * p * (2 * f - 1);
    double stddevNoise = stddev * p * (2 * f - 1);
    
    // generates data
    unsigned int samples = hours + 1;
    double data[samples] = {};
    for (unsigned int x = 0; x < samples; x++) {
        double exponent = -0.5 * pow((x - mean + meanNoise) / (stddev + stddevNoise), 2);
        data[x] = 1 / ((stddev + stddevNoise) * sqrt(2 * M_PI)) * exp(exponent);
    }

    // shifts the data in the sensor interval
    double a = *std::min_element(data, data + samples);
    double b = *std::max_element(data, data + samples);
    for (unsigned int i = 0; i < samples; i++) {
        double shiftedValue = min + ((max - min) / (b - a)) * (data[i] - a);
        v.push_back(shiftedValue);
    }

    return v;
}

// visitor

void NormalDistribution::accept(IDistributionVisitor& _visitor) {
    _visitor.visit(*this);
}

void NormalDistribution::accept(IDistributionConstVisitor& _visitor) const {
    _visitor.visit(*this);
}
