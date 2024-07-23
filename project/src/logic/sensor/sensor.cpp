#include "sensor.h"

unsigned int Sensor::idStarter = 0;
unsigned int Sensor::nameMaxLength = 20;

Sensor::Sensor(const std::string& _typeName, Distribution* _distribution, const std::string& _unitOfMeasurement, const std::string& _name)
: id(idStarter++), typeName(_typeName), distribution(_distribution), unitOfMeasurement(_unitOfMeasurement), name(_name == "" ? _typeName + std::to_string(id) : _name) {}

Sensor::Sensor(const Sensor& _sensor)
: id(_sensor.id), typeName(_sensor.typeName), distribution(_sensor.distribution->clone()), data(_sensor.data), unitOfMeasurement(_sensor.unitOfMeasurement), name(_sensor.name) {}

Sensor::~Sensor() {
    delete distribution;
}

// getter

unsigned int Sensor::getId() const {
    return id;
}

const std::string& Sensor::getTypeName() const {
    return typeName;
}

const Distribution* Sensor::getDistribution() const {
    return distribution;
}

const std::vector<double>& Sensor::getData() const {
    return data;
}

const std::string& Sensor::getUnitOfMeasurement() const {
    return unitOfMeasurement;
}

const std::string& Sensor::getName() const {
    return name;
}

unsigned int Sensor::getNameMaxLength() {
    return nameMaxLength;
}

// setter

void Sensor::resetIdStarter() {
    idStarter = 0;
}

void Sensor::setId(unsigned int _v) {
    id = _v;
    if (_v >= idStarter)
        idStarter = _v + 1;
}

void Sensor::setDistribution(const Distribution* _v) {
    if (distribution != _v) {
        delete distribution;
        distribution = _v->clone();
    }
}

void Sensor::setUnitOfMeasurement(const std::string& _v) {
    unitOfMeasurement = _v;
}

void Sensor::setName(const std::string& _v) {
    name = _v;
}

// simulation

void Sensor::startSimulation() {
    clearData();
    data = distribution->generateDistribution();
    for (auto observer : observers)
        observer->notifySimulation(*this);
}

void Sensor::stopSimulation() {
    clearData();
    for (auto observer : observers)
        observer->notifySimulation(*this);
}

void Sensor::clearData() {
    data.clear();
    // necessary because the data vector is allocated in the heap
    for (auto it = data.begin(); it != data.end(); it++)
        delete &(*it);
}

// modification

void Sensor::validParams(const std::string& _name, const std::vector<double>& _params) const {
    // necessary to avoid "unused parameter" warning
    (void)_params;
    if (_name.empty())
        throw InvalidSensorParams("\"name\" field cannot be empty.");
}

void Sensor::modified() {
    for (auto observer : observers)
        observer->notifyModification(*this);
}

// observers

void Sensor::registerObserver(ISensorObserver* _observer) {
    observers.push_back(_observer);
}

void Sensor::unregisterObserver(ISensorObserver* _observer) {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        if (*it == _observer) {
            observers.erase(it);
            break;
        }
    }
}
