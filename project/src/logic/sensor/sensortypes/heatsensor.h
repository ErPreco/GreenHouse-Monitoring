#ifndef HEAT_SENSOR_H
#define HEAT_SENSOR_H

#include <algorithm>
#include "../sensor.h"

class HeatSensor : public Sensor {
    private:
        double minAllowedTemp;
        double maxAllowedTemp;

    public:
        HeatSensor(Distribution*, double, double, const std::string&, const std::string& = "");
        HeatSensor(const HeatSensor&) = default;

        double getMaxAllowedTemp() const;
        double getMinAllowedTemp() const;

        void setMaxAllowedTemp(double);
        void setMinAllowedTemp(double);

        // Checks whether the data are between the minimum and maximum temperatures allowed.
        bool checkAllowedTemp() const;

        // Checks whether the given params are valid, throws InvalidSensorParams exception if they are not.
        void validParams(const std::string&, const std::vector<double>&) const override;

        void accept(ISensorVisitor&) override;
        void accept(ISensorConstVisitor&) const override;
};

#endif
