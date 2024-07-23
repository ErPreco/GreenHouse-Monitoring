#include "heatsensor.h"

HeatSensor::HeatSensor(Distribution* _distribution, double _minAllowedTemp, double _maxAllowedTemp, const std::string& _unitOfMeasurement, const std::string& _name)
: Sensor("Heat", _distribution, _unitOfMeasurement, _name), minAllowedTemp(_minAllowedTemp), maxAllowedTemp(_maxAllowedTemp) {}

// getter

double HeatSensor::getMaxAllowedTemp() const {
    return maxAllowedTemp;
}

double HeatSensor::getMinAllowedTemp() const {
    return minAllowedTemp;
}

// setter

void HeatSensor::setMaxAllowedTemp(double _v) {
    maxAllowedTemp = _v;
}

void HeatSensor::setMinAllowedTemp(double _v) {
    minAllowedTemp = _v;
}

// data

bool HeatSensor::checkAllowedTemp() const {
    std::vector<double> v = getData();
    return (*std::max_element(v.begin(), v.end()) <= maxAllowedTemp && *std::min_element(v.begin(), v.end()) >= minAllowedTemp);
}

void HeatSensor::validParams(const std::string& _name, const std::vector<double>& _params) const {
    Sensor::validParams(_name, _params);
    // minAllowedTemp/maxAllowedTemp check
    if (_params[0] >= _params[1])
        throw InvalidSensorParams("\"min allowed temp\" must be strictly less than \"max allowed temp\".");
}

// visitor

void HeatSensor::accept(ISensorVisitor& _visitor) {
    _visitor.visit(*this);
}

void HeatSensor::accept(ISensorConstVisitor& _visitor) const {
    _visitor.visit(*this);
}
