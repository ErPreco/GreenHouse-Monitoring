#include "createpanel.h"

CreatePanel::CreatePanel(SearchPanel* _searchPanel) : sensorTypeField(new QComboBox()), nameInputField(new QLineEdit()), distributionTypeField(new QComboBox()), searchPanel(_searchPanel) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 10, 20, 10);

    // title
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->setAlignment(Qt::AlignHCenter);
    QLabel* createText = new QLabel("create");
    createText->setStyleSheet("font-weight:bold; font-size:22px");
    titleLayout->addWidget(createText);
    layout->addLayout(titleLayout);

    QGridLayout* gridLayout = new QGridLayout();
    layout->addLayout(gridLayout);

    // sensor type
    gridLayout->addWidget(new QLabel("Type"), 0, 0, Qt::AlignRight);
    sensorTypeField->setStyleSheet("background-color:white; color:black");
    sensorTypeField->addItem("Water");
    sensorTypeField->addItem("Light");
    sensorTypeField->addItem("Heat");
    sensorTypeField->setFixedWidth(200);
    gridLayout->addWidget(sensorTypeField, 0, 1, Qt::AlignLeft);

    // name input field
    gridLayout->addWidget(new QLabel("Name"), 1, 0, Qt::AlignRight);
    nameInputField->setStyleSheet("background-color:white");
    nameInputField->setMaxLength(Sensor::getNameMaxLength());
    nameInputField->setPlaceholderText("type...");
    nameInputField->setFixedWidth(200);
    gridLayout->addWidget(nameInputField, 1, 1, Qt::AlignLeft);

    // distribution type
    gridLayout->addWidget(new QLabel("Distribution"), 2, 0, Qt::AlignRight);
    distributionTypeField->setStyleSheet("background-color:white; color:black");
    distributionTypeField->addItem("Uniform");
    distributionTypeField->addItem("Normal");
    distributionTypeField->addItem("Exponential");
    distributionTypeField->setFixedWidth(200);
    gridLayout->addWidget(distributionTypeField, 2, 1, Qt::AlignLeft);

    // create button
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignHCenter);
    layout->addLayout(buttonLayout);

    QPushButton* createBtn = new QPushButton("create");
    createBtn->setStyleSheet("background-color:white; font-size:16px");
    createBtn->setMaximumWidth(150);
    buttonLayout->addWidget(createBtn);
    connect(createBtn, &QPushButton::pressed, this, &CreatePanel::createSensor);
}

void CreatePanel::createSensor() {
    // creates the distribution with default params
    Distribution* distribution;
    std::map<std::string, std::any> params = SensorsManager::instance()->getDistributionsDefaultParams()[sensorTypeField->currentText().toStdString()];
    QString type = distributionTypeField->currentText();
    if (type == "Uniform")
        distribution = new UniformDistribution(std::any_cast<double>(params["min"]), std::any_cast<double>(params["max"]));
    else if (type == "Normal")
        distribution = new NormalDistribution(std::any_cast<double>(params["min"]), std::any_cast<double>(params["max"]), std::any_cast<double>(params["normalMean"]), std::any_cast<double>(params["normalStddev"]));
    else if (type == "Exponential")
        distribution = new ExponentialDistribution(std::any_cast<double>(params["min"]), std::any_cast<double>(params["max"]), std::any_cast<double>(params["exponentialLambda"]));
    else
        throw DistributionTypeNotFound("\"" + type.toStdString() + "\" not found when attempting to create sensor");

    // creates the sensor with default params
    Sensor* sensor;
    params = SensorsManager::instance()->getSensorsDefaultParams()[sensorTypeField->currentText().toStdString()];
    type = sensorTypeField->currentText();
    std::string name = nameInputField->text().trimmed().toStdString();
    if (type == "Water")
        sensor = new WaterSensor(distribution, std::any_cast<double>(params["maxRecycledWaterPerc"]), std::any_cast<std::string>(params["unitOfMeasurement"]), name);
    else if (type == "Light")
        sensor = new LightSensor(distribution, std::any_cast<unsigned int>(params["sunriseHour"]), std::any_cast<unsigned int>(params["sunsetHour"]), std::any_cast<double>(params["dailyMinLight"]), std::any_cast<std::string>(params["unitOfMeasurement"]), name);
    else if (type == "Heat")
        sensor = new HeatSensor(distribution, std::any_cast<double>(params["minAllowedTemp"]), std::any_cast<double>(params["maxAllowedTemp"]), std::any_cast<std::string>(params["unitOfMeasurement"]), name);
    else
        throw SensorTypeNotFound("\"" + type.toStdString() + "\" not found when attempting to create sensor");

    SensorsManager::instance()->addSensor(sensor);
    JsonManager::instance()->setIsModified(true);
    
    // check if any filter is hiding the sensor
    FilterVisitor visitor = searchPanel->getFilterVisitor();    
    visitor.setIsAllMatch(false);
    
    sensor->accept(visitor);
    sensor->getDistribution()->accept(visitor);
    
    if (!visitor.getIsNameMatch() ||
        (!visitor.getIsSensorTypesEmpty() && !visitor.getIsSensorTypeMatch()) ||
        (!visitor.getIsDistributionTypesEmpty() && !visitor.getIsDistributionTypeMatch())) {
        SensorsManager::instance()->filterSensors(searchPanel->getFilteredSensors());
        QString msg = "The new sensor has been created but cannot be displayed due to mismatching filters.";
        WarningMessageLog warningMessageLog(msg, "Impossible sensor display");
        warningMessageLog.showMessage();
    }

    nameInputField->setText("");
}
