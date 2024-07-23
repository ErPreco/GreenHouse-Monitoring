#include "distributioninfovisitor.h"

QVBoxLayout* DistributionInfoVisitor::getLayout() const {
    return layout;
}

std::vector<QLineEdit*> DistributionInfoVisitor::getFields() const {
    return fields;
}

void DistributionInfoVisitor::visit(const UniformDistribution& _distribution) {
    layout = new QVBoxLayout();
    fields.clear();

    QHBoxLayout* maxDeltaLayout = new QHBoxLayout();
    layout->addLayout(maxDeltaLayout);
    maxDeltaLayout->addWidget(new QLabel("Max delta"));
    maxDeltaLayout->addStretch();
    QLineEdit* maxDeltaInputField = new QLineEdit(QString::number(_distribution.getMaxDelta()));
    maxDeltaInputField->setValidator(new QDoubleValidator());
    maxDeltaInputField->setMaxLength(5);
    maxDeltaInputField->setFixedWidth(50);
    maxDeltaLayout->addWidget(maxDeltaInputField);
    fields.push_back(maxDeltaInputField);
}

void DistributionInfoVisitor::visit(const NormalDistribution& _distribution) {
    layout = new QVBoxLayout();
    fields.clear();

    QHBoxLayout* meanLayout = new QHBoxLayout();
    layout->addLayout(meanLayout);
    meanLayout->addWidget(new QLabel("Mean"));
    meanLayout->addStretch();
    QLineEdit* meanInputField = new QLineEdit(QString::number(_distribution.getMean()));
    meanInputField->setValidator(new QDoubleValidator());
    meanInputField->setMaxLength(5);
    meanInputField->setFixedWidth(50);
    meanLayout->addWidget(meanInputField);
    fields.push_back(meanInputField);

    QHBoxLayout* stddevLayout = new QHBoxLayout();
    layout->addLayout(stddevLayout);
    stddevLayout->addWidget(new QLabel("Standard deviation"));
    stddevLayout->addStretch();
    QLineEdit* stddevInputField = new QLineEdit(QString::number(_distribution.getStddev()));
    stddevInputField->setValidator(new QDoubleValidator());
    stddevInputField->setMaxLength(5);
    stddevInputField->setFixedWidth(50);
    stddevLayout->addWidget(stddevInputField);
    fields.push_back(stddevInputField);
}

void DistributionInfoVisitor::visit(const ExponentialDistribution& _distribution) {
    layout = new QVBoxLayout();
    fields.clear();

    QHBoxLayout* lambdaLayout = new QHBoxLayout();
    layout->addLayout(lambdaLayout);
    lambdaLayout->addWidget(new QLabel("Lambda"));
    lambdaLayout->addStretch();
    QLineEdit* lambdaInputField = new QLineEdit(QString::number(_distribution.getLambda()));
    lambdaInputField->setValidator(new QDoubleValidator());
    lambdaInputField->setMaxLength(5);
    lambdaInputField->setFixedWidth(50);
    lambdaLayout->addWidget(lambdaInputField);
    fields.push_back(lambdaInputField);
}
