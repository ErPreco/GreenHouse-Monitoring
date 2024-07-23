#ifndef ERROR_MANAGER_H
#define ERROR_MANAGER_H

#include <string>
#include <iostream>

class InvalidDistributionParams {
    private:
        std::string msg;
    
    public:
        InvalidDistributionParams(const std::string&);

        const std::string& getMessage() const;
};

class InvalidSensorParams {
    private:
        std::string msg;
    
    public:
        InvalidSensorParams(const std::string&);

        const std::string& getMessage() const;
};

class SensorTypeNotFound {
    private:
        std::string msg;
    
    public:
        SensorTypeNotFound(const std::string&);
};

class DistributionTypeNotFound {
    private:
        std::string msg;
    
    public:
        DistributionTypeNotFound(const std::string&);
};

class OpenFileFailed {
    private:
        std::string msg;
    
    public:
        OpenFileFailed(const std::string&);
};

#endif
