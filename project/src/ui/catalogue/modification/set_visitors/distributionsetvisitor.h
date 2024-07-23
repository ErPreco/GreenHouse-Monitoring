#ifndef DISTRIBUTION_SET_VISITOR_H
#define DISTRIBUTION_SET_VISITOR_H

#include "../../../../logic/distribution/interfaces/idistributionvisitor.h"
#include "../../../../logic/distribution/distributiontypes/uniformdistribution.h"
#include "../../../../logic/distribution/distributiontypes/normaldistribution.h"
#include "../../../../logic/distribution/distributiontypes/exponentialdistribution.h"

class DistributionSetVisitor : public IDistributionVisitor {
    private:
        std::vector<double> params;
    
    public:
        DistributionSetVisitor(const std::vector<double>&);

        void visit(UniformDistribution&) override;
        void visit(NormalDistribution&) override;
        void visit(ExponentialDistribution&) override;
};

#endif
