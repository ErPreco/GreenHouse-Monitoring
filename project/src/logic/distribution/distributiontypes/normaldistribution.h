#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H

#include <time.h>
#include <math.h>
#include <algorithm>
#include "../distribution.h"

class NormalDistribution : public Distribution {
    private:
        double mean;
        double stddev;
    
    public:
        NormalDistribution(double, double, double, double);
        NormalDistribution(double, double, double, double, unsigned int);

        NormalDistribution* clone() const override;

        double getMean() const;
        double getStddev() const;

        void setMean(double);
        void setStddev(double);
        
        // Checks whether the given params are valid, throws InvalidDistributionParams exception if they are not.
        void validParams(const std::vector<double>&) const override;
        // Returns a vector of data.
        std::vector<double> generateDistribution() const override;

        void accept(IDistributionVisitor&) override;
        void accept(IDistributionConstVisitor&) const override;
};

#endif
