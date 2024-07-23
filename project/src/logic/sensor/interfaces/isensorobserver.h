#ifndef I_SENSOR_OBSERVER_H
#define I_SENSOR_OBSERVER_H

class Sensor;

class ISensorObserver {
    public:
        virtual ~ISensorObserver() = default;
        virtual void notifySimulation(Sensor&) = 0;
        virtual void notifyModification(const Sensor&) = 0;
};

#endif
