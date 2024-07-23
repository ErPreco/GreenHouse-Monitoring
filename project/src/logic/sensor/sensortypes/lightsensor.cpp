#include "lightsensor.h"

LightSensor::LightSensor(Distribution* _distribution, unsigned int _sunriseHour, unsigned int _sunsetHour, double _dailyMinLight, const std::string& _unitOfMeasurement, const std::string& _name)
: Sensor("Light", _distribution, _unitOfMeasurement, _name), sunriseHour(_sunriseHour), sunsetHour(_sunsetHour), dailyMinLight(_dailyMinLight) {}

// getter

unsigned int LightSensor::getSunriseHour() const {
    return sunriseHour;
}

unsigned int LightSensor::getSunsetHour() const {
    return sunsetHour;
}

double LightSensor::getDailyMinLight() const {
    return dailyMinLight;
}

// setter

void LightSensor::setSunriseHour(unsigned int _v) {
    sunriseHour = _v;
}

void LightSensor::setSunsetHour(unsigned int _v) {
    sunsetHour = _v;
}

void LightSensor::setDailyMinLight(double _v) {
    dailyMinLight = _v;
}

// data

bool LightSensor::checkArtificialLights() const {
    std::vector<double> v = getData();    
    for (unsigned int i = sunriseHour; i < ((v.size() < sunsetHour) ? v.size() : sunsetHour); i++) {
        if (v[i] < dailyMinLight)
            return true;
    }
    return false;
}

void LightSensor::validParams(const std::string& _name, const std::vector<double>& _params) const {
    Sensor::validParams(_name, _params);
    // sunriseHour check
    if (_params[0] < 0 || _params[0] > 24)
        throw InvalidSensorParams("\"sunrise hour\" must be a valid hour in a 24h day.");
    // sunsetHour check
    if (_params[1] < 0 || _params[1] > 24)
        throw InvalidSensorParams("\"sunset hour\" must be a valid hour in a 24h day.");
    // sunriseHour/sunsetHour check
    if (_params[0] >= _params[1])
        throw InvalidSensorParams("\"sunrise hour\" must be strictly less than \"sunset hour\".");
    // dailyMinLight check
    if (_params[2] < 0.0)
        throw InvalidSensorParams("\"daily min light\" must be strictly greater than 0.");
}

// visitor

void LightSensor::accept(ISensorVisitor& _visitor) {
    _visitor.visit(*this);
}

void LightSensor::accept(ISensorConstVisitor& _visitor) const {
    _visitor.visit(*this);
}
