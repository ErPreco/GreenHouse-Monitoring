#include "simulationvisitor.h"

SimulationVisitor::SimulationVisitor(QChart* _chart, QValueAxis* _axisX, QValueAxis* _axisY, QLabel* _label)
: chart(_chart), axisX(_axisX), axisY(_axisY), label(_label) {}

void SimulationVisitor::visit(WaterSensor& _sensor) {
    QBarSet* set = new QBarSet("recycled water");
    _sensor.generateRecycledWater();
    for (auto percentage : _sensor.getRecycledWater())
        set->append(percentage);
    set->setBrush(Qt::blue);
    QBarSeries* series = new QBarSeries();
    series->append(set);

    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    setInfo(QString::number(_sensor.getRecycledWaterAmount()) + " " + QString::fromStdString(_sensor.getUnitOfMeasurement()) + " has been recycled (" +
            QString::number(_sensor.getRecycledWaterPercentage() * 100, 'f', 2) + "% of total used water)");
}

void SimulationVisitor::visit(LightSensor& _sensor) {
    QLineSeries* dailyMinLine = new QLineSeries();
    dailyMinLine->append(_sensor.getSunriseHour(), 0);
    dailyMinLine->append(_sensor.getSunriseHour(), _sensor.getDailyMinLight());
    dailyMinLine->append(_sensor.getSunsetHour(), _sensor.getDailyMinLight());
    dailyMinLine->append(_sensor.getSunsetHour(), 0);
    
    QPen pen(Qt::red);
    dailyMinLine->setPen(pen);

    chart->addSeries(dailyMinLine);
    dailyMinLine->attachAxis(axisX);
    dailyMinLine->attachAxis(axisY);
    chart->legend()->markers(dailyMinLine)[0]->setLabel("minimum daily light");

    if (_sensor.checkArtificialLights())
        setWarning("Artifical lights needed due to too low levels of natural light detected!");
    else
        setInfo("No artificial lights needed.");
}

void SimulationVisitor::visit(HeatSensor& _sensor) {
    QLineSeries* maxValueLine = new QLineSeries();
    QLineSeries* minValueLine = new QLineSeries();
    for (unsigned int x = 0; x < 2; x++) {
        maxValueLine->append(x * _sensor.getData().size(), _sensor.getMaxAllowedTemp());
        minValueLine->append(x * _sensor.getData().size(), _sensor.getMinAllowedTemp());
    }
    QPen pen(Qt::red);
    maxValueLine->setPen(pen);
    minValueLine->setPen(pen);
    
    chart->addSeries(maxValueLine);
    maxValueLine->attachAxis(axisX);
    maxValueLine->attachAxis(axisY);
    chart->legend()->markers(maxValueLine)[0]->setLabel("temperature limits");
    chart->addSeries(minValueLine);
    minValueLine->attachAxis(axisX);
    minValueLine->attachAxis(axisY);
    chart->legend()->markers(minValueLine)[0]->setVisible(false);

    if (_sensor.checkAllowedTemp())
        setInfo("All detected temperatures are between the allowed limits.");
    else
        setWarning("Temperatures off the allowed limits detected!");
}

void SimulationVisitor::setInfo(const QString& _message) {
    label->setText("INFO: " + _message);
}

void SimulationVisitor::setWarning(const QString& _message) {
    label->setText("WARNING: " + _message);
    label->setStyleSheet("color:red; font-size:20px");
}
