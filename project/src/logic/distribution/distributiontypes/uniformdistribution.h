#ifndef UNIFORM_DISTRIBUTION_H
#define UNIFORM_DISTRIBUTION_H

#include <time.h>
#include "../distribution.h"

class UniformDistribution : public Distribution {    
    private:
        double maxDelta;

    public:
        UniformDistribution(double, double);
        UniformDistribution(double, double, unsigned int);

        UniformDistribution* clone() const override;

        double getMaxDelta() const;
        
        void setMaxDelta(double);

        // Checks whether the given params are valid, throws InvalidDistributionParams exception if they are not.
        void validParams(const std::vector<double>&) const override;
        // Returns a vector of data.
        std::vector<double> generateDistribution() const override;

        void accept(IDistributionVisitor&) override;
        void accept(IDistributionConstVisitor&) const override;
};

#endif
