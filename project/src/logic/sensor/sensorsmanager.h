#ifndef SENSORS_MANAGER_H
#define SENSORS_MANAGER_H

#include <vector>
#include <map>
#include <any>
#include "sensor.h"
#include "interfaces/isensorsmanagerobserver.h"

class SensorsManager {
    private:
        static SensorsManager* ptr;

        std::vector<Sensor*> sensors;
        std::map<std::string, std::map<std::string, std::any>> sensorsDefaultParams;
        std::map<std::string, std::map<std::string, std::any>> distributionsDefaultParams;
        std::vector<ISensorsManagerObserver*> observers;

        SensorsManager();
    
    public:
        SensorsManager(const SensorsManager&) = delete;
        ~SensorsManager();
        SensorsManager& operator=(const SensorsManager&) = delete;

        static SensorsManager* instance();

        std::map<std::string, std::map<std::string, std::any>> getSensorsDefaultParams() const;
        std::map<std::string, std::map<std::string, std::any>> getDistributionsDefaultParams() const;
        std::vector<const Sensor*> getSensors() const;

        std::vector<Sensor*> setSensors() const;
        
        // Adds the given sensor to the list.
        void addSensor(Sensor*);
        // Remove the fiven sensor from the list.
        void removeSensor(Sensor*);
        // Filters the given list.
        void filterSensors(const std::vector<Sensor*>&) const;
        // Clears the list of sensors.
        void clearSensors();

        void registerObserver(ISensorsManagerObserver*);
        void unregisterObserver(ISensorsManagerObserver*);
};

#endif
