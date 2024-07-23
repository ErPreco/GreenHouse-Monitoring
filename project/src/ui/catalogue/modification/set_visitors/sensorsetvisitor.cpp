#include "sensorsetvisitor.h"

SensorSetVisitor::SensorSetVisitor(const std::string& _name, const std::vector<double>& _params) : name(_name), params(_params) {}

void SensorSetVisitor::visit(WaterSensor& _sensor) {
    _sensor.setName(name);
    _sensor.setMaxRecycledWaterPerc(params[0]);
}

void SensorSetVisitor::visit(LightSensor& _sensor) {
    _sensor.setName(name);
    _sensor.setSunriseHour(params[0]);
    _sensor.setSunsetHour(params[1]);
    _sensor.setDailyMinLight(params[2]);
}

void SensorSetVisitor::visit(HeatSensor& _sensor) {
    _sensor.setName(name);
    _sensor.setMinAllowedTemp(params[0]);
    _sensor.setMaxAllowedTemp(params[1]);
}
