#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <string>
#include <vector>
#include "interfaces/idistributionvisitor.h"
#include "interfaces/idistributionconstvisitor.h"
#include "../errormanager.h"

class Distribution {
    protected:
        std::string typeName;
        unsigned int hours;

        double min;
        double max;
    
    public:
        Distribution(const std::string&, double, double, unsigned int = 24);
        Distribution(const Distribution&) = default;
        virtual ~Distribution() = default;

        virtual Distribution* clone() const = 0;

        const std::string& getTypeName() const;
        unsigned int getHours() const;
        double getMin() const;
        double getMax() const;

        void setHours(unsigned int);
        void setMin(double);
        void setMax(double);

        // Checks whether the given params are valid, throws InvalidDistributionParams exception if they are not.
        virtual void validParams(const std::vector<double>&) const;
        // Returns a vector of data.
        virtual std::vector<double> generateDistribution() const = 0;

        virtual void accept(IDistributionVisitor&) = 0;
        virtual void accept(IDistributionConstVisitor&) const = 0;
};

#endif
