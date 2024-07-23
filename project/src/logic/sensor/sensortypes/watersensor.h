#ifndef WATER_SENSOR_H
#define WATER_SENSOR_H

#include <numeric>
#include "../sensor.h"

class WaterSensor : public Sensor {
    private:
        std::vector<double> recycledWater;
        double maxRecycledWaterPerc;

    public:
        WaterSensor(Distribution*, double, const std::string&, const std::string& = "");
        WaterSensor(const WaterSensor&) = default;

        std::vector<double> getRecycledWater() const;
        double getRecycledWaterAmount() const;
        double getRecycledWaterPercentage() const;
        double getMaxRecyledWaterPerc() const;

        void generateRecycledWater();
        void setMaxRecycledWaterPerc(double);

        // Checks whether the given params are valid, throws InvalidSensorParams exception if they are not.
        void validParams(const std::string&, const std::vector<double>&) const override;

        void accept(ISensorVisitor&) override;
        void accept(ISensorConstVisitor&) const override;
};

#endif
