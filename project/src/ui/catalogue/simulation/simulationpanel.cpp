#include "simulationpanel.h"

SimulationPanel::SimulationPanel() = default;

void SimulationPanel::notifySimulation(Sensor& _sensor) {
    QDialog* dialog = new QDialog();
    dialog->setFixedSize(1200, 600);
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    // series of data
    QLineSeries* series = new QLineSeries();
    std::vector<double> data = _sensor.getData();
    for (unsigned int i = 0; i < data.size(); i++)
        series->append(i, data[i]);

    // line chart
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(QString("plot of %1 (type: %2, ID: %3)").arg(QString::fromStdString(_sensor.getName())).arg(QString::fromStdString(_sensor.getTypeName())).arg(_sensor.getId()));
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->markers(series)[0]->setVisible(false);
    // X axis
    QValueAxis* axisX = new QValueAxis();
    axisX->setRange(0, data.size() - 1);
    axisX->setTickCount(data.size());
    axisX->setLabelFormat("%2d");
    axisX->setTitleText("hours from midnight");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    // Y axis
    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(_sensor.getDistribution()->getMin(), _sensor.getDistribution()->getMax());
    axisY->setTickCount(10);
    axisY->setLabelFormat("%2.1f");
    axisY->setTitleText(QString("measurements (%1)").arg(QString::fromStdString(_sensor.getUnitOfMeasurement())));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);

    // label
    QHBoxLayout* labelLayout = new QHBoxLayout();
    labelLayout->setAlignment(Qt::AlignHCenter);
    layout->addLayout(labelLayout);
    QLabel* label = new QLabel();
    label->setStyleSheet("font-size:17px");
    labelLayout->addWidget(label);

    // custom chart
    SimulationVisitor visitor(chart, axisX, axisY, label);
    _sensor.accept(visitor);

    dialog->setModal(true);
    if (dialog->exec() == QDialog::Accepted)
        _sensor.stopSimulation();
    dialog->deleteLater();
}

void SimulationPanel::notifyModification(const Sensor&) {}
