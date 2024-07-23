#include "distribution.h"

Distribution::Distribution(const std::string& _typeName, double _min, double _max, unsigned int _hours)
: typeName(_typeName), hours(_hours), min(_min), max(_max) {}

// getters

const std::string& Distribution::getTypeName() const {
    return typeName;
}

unsigned int Distribution::getHours() const {
    return hours;
}

double Distribution::getMin() const {
    return min;
}

double Distribution::getMax() const {
    return max;
}

// setters

void Distribution::setHours(unsigned int _v) {
    hours = _v;
}

void Distribution::setMin(double _v) {
    min = _v;
}

void Distribution::setMax(double _v) {
    max = _v;
}

// data

void Distribution::validParams(const std::vector<double>& _params) const {
    // hours check
    if (_params[0] < 0 || _params[0] > 24)
        throw InvalidDistributionParams("\"hours\" must be a valid hour in a 24h day.");
    // min/max check
    if (_params[1] >= _params[2])
        throw InvalidDistributionParams("\"min\" must be strictly less than \"max\".");
}
