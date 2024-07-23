#ifndef EXPONENTIAL_DISTRIBUTION_H
#define EXPONENTIAL_DISTRIBUTION_H

#include <time.h>
#include <math.h>
#include "../distribution.h"

class ExponentialDistribution : public Distribution {
    private:
        double lambda;

    public:
        ExponentialDistribution(double, double, double);
        ExponentialDistribution(double, double, double, unsigned int);

        ExponentialDistribution* clone() const override;

        double getLambda() const;

        void setLambda(double);

        // Checks whether the given params are valid, throws InvalidDistributionParams exception if they are not.
        void validParams(const std::vector<double>&) const override;
        // Returns a vector of data.
        std::vector<double> generateDistribution() const override;

        void accept(IDistributionVisitor&) override;
        void accept(IDistributionConstVisitor&) const override;
};

#endif
