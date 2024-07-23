#include "filtervisitor.h"

FilterVisitor::FilterVisitor()
: name(""), filterWater(false), filterLight(false), filterHeat(false),
filterUniform(false), filterNormal(false), filterExponential(false),
isNameMatch(false), isSensorTypeMatch(false), isDistributionTypeMatch(false) {}

std::string FilterVisitor::toLowercase(std::string s) const {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){return std::tolower(c);});
    return s;
}

void FilterVisitor::checkName(const Sensor& _sensor) {
    if (caseSensitive) {
        if (_sensor.getName().find(name) != std::string::npos)
            isNameMatch = true;
    } else if (toLowercase(_sensor.getName()).find(toLowercase(name)) != std::string::npos)
        isNameMatch = true;
}

// getter

bool FilterVisitor::getIsNameMatch() const {
    return isNameMatch;
}

bool FilterVisitor::getIsSensorTypeMatch() const {
    return isSensorTypeMatch;
}

bool FilterVisitor::getIsDistributionTypeMatch() const {
    return isDistributionTypeMatch;
}

bool FilterVisitor::getIsSensorTypesEmpty() const {
    return !filterWater && !filterLight && !filterHeat;
}

bool FilterVisitor::getIsDistributionTypesEmpty() const {
    return !filterUniform && !filterNormal && !filterExponential;
}

// setter

void FilterVisitor::setName(const std::string& _v) {
    name = _v;
}

void FilterVisitor::setCaseSensitive(bool _v) {
    caseSensitive = _v;
}

void FilterVisitor::setFilterWater(bool _v) {
    filterWater = _v;
}

void FilterVisitor::setFilterLight(bool _v) {
    filterLight = _v;
}

void FilterVisitor::setFilterHeat(bool _v) {
    filterHeat = _v;
}

void FilterVisitor::setFilterUniform(bool _v) {
    filterUniform = _v;
}

void FilterVisitor::setFilterNormal(bool _v) {
    filterNormal = _v;
}

void FilterVisitor::setFilterExponential(bool _v) {
    filterExponential = _v;
}

void FilterVisitor::setIsAllMatch(bool _v) {
    isNameMatch = isSensorTypeMatch = isDistributionTypeMatch = _v;
}

// visit

void FilterVisitor::visit(const WaterSensor& _sensor) {
    checkName(_sensor);

    if (filterWater)
        isSensorTypeMatch = true;
}

void FilterVisitor::visit(const LightSensor& _sensor) {
    checkName(_sensor);
    
    if (filterLight)
        isSensorTypeMatch = true;
}

void FilterVisitor::visit(const HeatSensor& _sensor) {
    checkName(_sensor);
    
    if (filterHeat)
        isSensorTypeMatch = true;
}

void FilterVisitor::visit(const UniformDistribution& _distribution) {
    // necessary to avoid "unused parameter" warning
    (void)_distribution;
    if (filterUniform)
        isDistributionTypeMatch = true;
}

void FilterVisitor::visit(const NormalDistribution& _distribution) {
    // necessary to avoid "unused parameter" warning
    (void)_distribution;
    if (filterNormal)
        isDistributionTypeMatch = true;
}

void FilterVisitor::visit(const ExponentialDistribution& _distribution) {
    // necessary to avoid "unused parameter" warning
    (void)_distribution;
    if (filterExponential)
        isDistributionTypeMatch = true;
}
