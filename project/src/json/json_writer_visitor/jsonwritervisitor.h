#ifndef JSON_WRITER_VISITOR_H
#define JSON_WRITER_VISITOR_H

#include <QJsonObject>
#include "../../logic/sensor/interfaces/isensorconstvisitor.h"
#include "../../logic/distribution/interfaces/idistributionconstvisitor.h"
#include "../../logic/sensor/sensortypes/watersensor.h"
#include "../../logic/sensor/sensortypes/lightsensor.h"
#include "../../logic/sensor/sensortypes/heatsensor.h"
#include "../../logic/distribution/distributiontypes/uniformdistribution.h"
#include "../../logic/distribution/distributiontypes/normaldistribution.h"
#include "../../logic/distribution/distributiontypes/exponentialdistribution.h"

class JsonWriterVisitor : public ISensorConstVisitor, public IDistributionConstVisitor {
    private:
        QJsonObject object;

    public:
        QJsonObject getJsonObject() const;

        void visit(const WaterSensor&) override;
        void visit(const LightSensor&) override;
        void visit(const HeatSensor&) override;
        
        void visit(const UniformDistribution&) override;
        void visit(const NormalDistribution&) override;
        void visit(const ExponentialDistribution&) override;
};

#endif
