#include "distributionsetvisitor.h"

DistributionSetVisitor::DistributionSetVisitor(const std::vector<double>& _params) : params(_params) {}

void DistributionSetVisitor::visit(UniformDistribution& _distribution) {
    _distribution.setHours(params[0]);
    _distribution.setMin(params[1]);
    _distribution.setMax(params[2]);
    _distribution.setMaxDelta(params[3]);
}

void DistributionSetVisitor::visit(NormalDistribution& _distribution) {
    _distribution.setHours(params[0]);
    _distribution.setMin(params[1]);
    _distribution.setMax(params[2]);
    _distribution.setMean(params[3]);
    _distribution.setStddev(params[4]);
}

void DistributionSetVisitor::visit(ExponentialDistribution& _distribution) {
    _distribution.setHours(params[0]);
    _distribution.setMin(params[1]);
    _distribution.setMax(params[2]);
    _distribution.setLambda(params[3]);
}
