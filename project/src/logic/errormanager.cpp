#include "errormanager.h"

InvalidDistributionParams::InvalidDistributionParams(const std::string& _msg) : msg(_msg) {
    std::cerr << "Invalid distribution params inserted: " << _msg << std::endl;
}

const std::string& InvalidDistributionParams::getMessage() const {
    return msg;
}

InvalidSensorParams::InvalidSensorParams(const std::string& _msg) : msg(_msg) {
    std::cerr << "Invalid sensor params inserted: " << _msg << std::endl;
}

const std::string& InvalidSensorParams::getMessage() const {
    return msg;
}

SensorTypeNotFound::SensorTypeNotFound(const std::string& _msg) : msg(_msg) {
    std::cerr << "Sensor type not found: " << _msg << std::endl;
}

DistributionTypeNotFound::DistributionTypeNotFound(const std::string& _msg) : msg(_msg) {
    std::cerr << "Distribution type not found: " << _msg << std::endl;
}

OpenFileFailed::OpenFileFailed(const std::string& _msg) : msg(_msg) {
    std::cerr << "Failure opening file: " << _msg << std::endl;
}
