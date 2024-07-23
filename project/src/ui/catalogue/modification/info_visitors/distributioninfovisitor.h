#ifndef DISTRIBUTION_INFO_VISITOR_H
#define DISTRIBUTION_INFO_VISITOR_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QString>
#include <vector>
#include "../../../../logic/distribution/interfaces/idistributionconstvisitor.h"
#include "../../../../logic/distribution/distributiontypes/uniformdistribution.h"
#include "../../../../logic/distribution/distributiontypes/normaldistribution.h"
#include "../../../../logic/distribution/distributiontypes/exponentialdistribution.h"

class DistributionInfoVisitor : public IDistributionConstVisitor {
    private:
        QVBoxLayout* layout;
        std::vector<QLineEdit*> fields;
    
    public:
        QVBoxLayout* getLayout() const;
        std::vector<QLineEdit*> getFields() const;

        void visit(const UniformDistribution&) override;
        void visit(const NormalDistribution&) override;
        void visit(const ExponentialDistribution&) override;
};

#endif
