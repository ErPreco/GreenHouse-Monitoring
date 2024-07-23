#ifndef FILTER_VISITOR_H
#define FILTER_VISITOR_H

#include <string>
#include "../../../logic/sensor/interfaces/isensorconstvisitor.h"
#include "../../../logic/distribution/interfaces/idistributionconstvisitor.h"
#include "../../../logic/sensor/sensortypes/watersensor.h"
#include "../../../logic/sensor/sensortypes/lightsensor.h"
#include "../../../logic/sensor/sensortypes/heatsensor.h"
#include "../../../logic/distribution/distributiontypes/uniformdistribution.h"
#include "../../../logic/distribution/distributiontypes/normaldistribution.h"
#include "../../../logic/distribution/distributiontypes/exponentialdistribution.h"

class FilterVisitor : public ISensorConstVisitor, public IDistributionConstVisitor {
    private:
        std::string name;
        bool caseSensitive;

        bool filterWater;
        bool filterLight;
        bool filterHeat;

        bool filterUniform;
        bool filterNormal;
        bool filterExponential;

        bool isNameMatch;
        bool isSensorTypeMatch;
        bool isDistributionTypeMatch;

        std::string toLowercase(std::string) const;
        void checkName(const Sensor&);

    public:
        FilterVisitor();

        bool getIsNameMatch() const;
        bool getIsSensorTypeMatch() const;
        bool getIsDistributionTypeMatch() const;
        bool getIsSensorTypesEmpty() const;
        bool getIsDistributionTypesEmpty() const;

        void setName(const std::string&);
        void setCaseSensitive(bool);
        void setFilterWater(bool);
        void setFilterLight(bool);
        void setFilterHeat(bool);
        void setFilterUniform(bool);
        void setFilterNormal(bool);
        void setFilterExponential(bool);
        void setIsAllMatch(bool);

        void visit(const WaterSensor&) override;
        void visit(const LightSensor&) override;
        void visit(const HeatSensor&) override;

        void visit(const UniformDistribution&) override;
        void visit(const NormalDistribution&) override;
        void visit(const ExponentialDistribution&) override;
};

#endif
