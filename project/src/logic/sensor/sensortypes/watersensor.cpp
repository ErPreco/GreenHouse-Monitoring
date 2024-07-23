#include "watersensor.h"

WaterSensor::WaterSensor(Distribution* _distribution, double _maxRecycledWaterPerc, const std::string& _unitOfMeasurement, const std::string& _name)
: Sensor("Water", _distribution, _unitOfMeasurement, _name), maxRecycledWaterPerc(_maxRecycledWaterPerc) {}

// getter

std::vector<double> WaterSensor::getRecycledWater() const {
    return recycledWater;
}

double WaterSensor::getRecycledWaterAmount() const {
    return std::accumulate(recycledWater.begin(), recycledWater.end(), 0);
}

double WaterSensor::getRecycledWaterPercentage() const {
    std::vector<double> data = getData();
    return getRecycledWaterAmount() / std::accumulate(data.begin(), data.end(), 0);
}

double WaterSensor::getMaxRecyledWaterPerc() const {
    return maxRecycledWaterPerc;
}

// setter

void WaterSensor::generateRecycledWater() {
    recycledWater.clear();
    for (auto data : getData()) {
        double f = (double)rand() / RAND_MAX * maxRecycledWaterPerc;
        recycledWater.push_back((data - getDistribution()->getMin()) * f);
    }
}

void WaterSensor::setMaxRecycledWaterPerc(double _v) {
    maxRecycledWaterPerc = _v;
}

// data

void WaterSensor::validParams(const std::string& _name, const std::vector<double>& _params) const {
    Sensor::validParams(_name, _params);
    // maxRecycledWaterPerc check
    if (_params[0] < 0.0 || _params[0] > 1.0)
        throw InvalidSensorParams("\"max recycled water perc\" must be between 0 and 1 included.");
}

// visitor

void WaterSensor::accept(ISensorVisitor& _visitor) {
    _visitor.visit(*this);
}

void WaterSensor::accept(ISensorConstVisitor& _visitor) const {
    _visitor.visit(*this);
}
