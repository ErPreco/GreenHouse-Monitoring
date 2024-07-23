#ifndef I_SENSORS_MANAGER_OBSERVER_H
#define I_SENSORS_MANAGER_OBSERVER_H

#include <vector>

class Sensor;

class ISensorsManagerObserver {
    public:
        virtual ~ISensorsManagerObserver() = default;
        virtual void notifyCreatedSensor(Sensor&) = 0;
        virtual void notifyRemovedSensor(unsigned int) = 0;
        virtual void notifyFilteredSensors(const std::vector<Sensor*>&) = 0;
        virtual void notifyOpenedFile() = 0;
};

#endif
