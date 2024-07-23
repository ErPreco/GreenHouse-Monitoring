#ifndef I_CONST_DISTRIBUTION_VISITOR_H
#define I_CONST_DISTRIBUTION_VISITOR_H

class UniformDistribution;
class NormalDistribution;
class ExponentialDistribution;

class IDistributionConstVisitor {
    public:
        virtual ~IDistributionConstVisitor() = default;

        virtual void visit(const UniformDistribution&) = 0;
        virtual void visit(const NormalDistribution&) = 0;
        virtual void visit(const ExponentialDistribution&) = 0;
};

#endif
