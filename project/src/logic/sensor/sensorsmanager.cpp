#include "sensorsmanager.h"

SensorsManager* SensorsManager::ptr = nullptr;

SensorsManager::SensorsManager() {
    sensorsDefaultParams["Water"] = std::map<std::string, std::any> {
        { "maxRecycledWaterPerc", 1.0 },
        { "unitOfMeasurement", std::string("mL") }
    };
    sensorsDefaultParams["Light"] = std::map<std::string, std::any> {
        { "sunriseHour", (unsigned int)5 },
        { "sunsetHour", (unsigned int)19 },
        { "dailyMinLight", 40.0 },
        { "unitOfMeasurement", std::string("klx") }
    };
    sensorsDefaultParams["Heat"] = std::map<std::string, std::any> {
        { "minAllowedTemp", 23.0 },
        { "maxAllowedTemp", 27.0 },
        { "unitOfMeasurement", std::string("°C") }
    };

    distributionsDefaultParams["Water"] = std::map<std::string, std::any> {
        { "min", 0.0 },
        { "max", 50.0 },
        { "normalMean", 12.0 },
        { "normalStddev", 2.0 },
        { "exponentialLambda", 0.3 }
    };
    distributionsDefaultParams["Light"] = std::map<std::string, std::any> {
        { "min", 30.0 },
        { "max", 80.0 },
        { "normalMean", 10.0 },
        { "normalStddev", 3.5 },
        { "exponentialLambda", 0.9 }
    };
    distributionsDefaultParams["Heat"] = std::map<std::string, std::any> {
        { "min", 23.0 },
        { "max", 27.0 },
        { "normalMean", 14.0 },
        { "normalStddev", 5.0 },
        { "exponentialLambda", 0.6 }
    };
}

SensorsManager::~SensorsManager() {
    for (auto s : sensors)
        delete s;
}

SensorsManager* SensorsManager::instance() {
    if (ptr == nullptr)
        ptr = new SensorsManager();
    return ptr;
}

// getter

std::map<std::string, std::map<std::string, std::any>> SensorsManager::getSensorsDefaultParams() const {
    return sensorsDefaultParams;
}

std::map<std::string, std::map<std::string, std::any>> SensorsManager::getDistributionsDefaultParams() const {
    return distributionsDefaultParams;
}

std::vector<const Sensor*> SensorsManager::getSensors() const {
    std::vector<const Sensor*> v;
    for (auto s : sensors)
        v.push_back(s);
    return v;
}

// setter

std::vector<Sensor*> SensorsManager::setSensors() const {
    return sensors;
}

// sensors

void SensorsManager::addSensor(Sensor* _sensor) {
    sensors.push_back(_sensor);
    for (auto observer : observers)
        observer->notifyCreatedSensor(*_sensor);
}

void SensorsManager::removeSensor(Sensor* _sensor) {
    for (auto [it, idx] = std::tuple{sensors.begin(), 0}; it != sensors.end(); it++, idx++) {
        if (*it == _sensor) {
            delete *it;
            sensors.erase(it);
            for (auto observer : observers)
                observer->notifyRemovedSensor(idx);
            break;
        }
    }
}

void SensorsManager::filterSensors(const std::vector<Sensor*>& _sensors) const {
    for (auto observer : observers)
        observer->notifyFilteredSensors(_sensors);
}

void SensorsManager::clearSensors() {
    for (auto sensor : sensors)
        delete sensor;
    sensors.clear();

    for (auto observer : observers)
        observer->notifyOpenedFile();
}

// observers

void SensorsManager::registerObserver(ISensorsManagerObserver* _observer) {
    observers.push_back(_observer);
}

void SensorsManager::unregisterObserver(ISensorsManagerObserver* _observer) {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        if (*it == _observer) {
            observers.erase(it);
            break;
        }
    }
}
