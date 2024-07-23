#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <vector>
#include <algorithm>
#include "../distribution/distribution.h"
#include "interfaces/isensorobserver.h"
#include "interfaces/isensorvisitor.h"
#include "interfaces/isensorconstvisitor.h"
#include "../errormanager.h"

class Sensor {
    private:
        static unsigned int idStarter;
        static unsigned int nameMaxLength;

        unsigned int id;
        const std::string typeName;
        Distribution* distribution;
        std::vector<double> data;
        std::string unitOfMeasurement;
        std::string name;

        std::vector<ISensorObserver*> observers;
    
        // Clears the data vector.
        void clearData();

    public:
        Sensor(const std::string&, Distribution*, const std::string&, const std::string& = "");
        Sensor(const Sensor&);
        virtual ~Sensor();
        Sensor& operator=(const Sensor&) = delete;

        unsigned int getId() const;
        const std::string& getTypeName() const;
        const Distribution* getDistribution() const;
        const std::vector<double>& getData() const;
        const std::string& getUnitOfMeasurement() const;
        const std::string& getName() const;
        static unsigned int getNameMaxLength();

        static void resetIdStarter();
        void setId(unsigned int);
        void setDistribution(const Distribution*);
        void setUnitOfMeasurement(const std::string&);
        void setName(const std::string&);

        // Generates the data and starts the simulation.
        void startSimulation();
        // Clears the data and stops the simulation.
        void stopSimulation();

        // Checks whether the given params are valid, throws InvalidSensorParams exception if they are not.
        virtual void validParams(const std::string&, const std::vector<double>&) const;
        void modified();

        void registerObserver(ISensorObserver*);
        void unregisterObserver(ISensorObserver*);

        virtual void accept(ISensorVisitor&) = 0;
        virtual void accept(ISensorConstVisitor&) const = 0;
};

#endif
