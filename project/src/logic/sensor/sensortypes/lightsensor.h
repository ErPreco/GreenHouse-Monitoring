#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "../sensor.h"

class LightSensor : public Sensor {
    private:
        unsigned int sunriseHour;
        unsigned int sunsetHour;
        double dailyMinLight;
    
    public:
        LightSensor(Distribution*, unsigned int, unsigned int, double, const std::string&, const std::string& = "");
        LightSensor(const LightSensor&) = default;

        unsigned int getSunriseHour() const;
        unsigned int getSunsetHour() const;
        double getDailyMinLight() const;

        void setSunriseHour(unsigned int);
        void setSunsetHour(unsigned int);
        void setDailyMinLight(double);

        // Checks whether the artificial lights must be turned on (data are below minimum light level allowed)
        bool checkArtificialLights() const;

        // Checks whether the given params are valid, throws InvalidSensorParams exception if they are not.
        void validParams(const std::string&, const std::vector<double>&) const override;

        void accept(ISensorVisitor&) override;
        void accept(ISensorConstVisitor&) const override;
};

#endif
