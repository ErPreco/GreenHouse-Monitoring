#ifndef I_DISTRIBUTION_VISITOR_H
#define I_DISTRIBUTION_VISITOR_H

class UniformDistribution;
class NormalDistribution;
class ExponentialDistribution;

class IDistributionVisitor {
    public:
        virtual ~IDistributionVisitor() = default;

        virtual void visit(UniformDistribution&) = 0;
        virtual void visit(NormalDistribution&) = 0;
        virtual void visit(ExponentialDistribution&) = 0;
};

#endif
