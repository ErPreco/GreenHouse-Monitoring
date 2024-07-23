#include "optionspanel.h"

OptionsPanel::OptionsPanel() {
    setStyleSheet("background-color:#C0FFBE");

    QVBoxLayout* layout = new QVBoxLayout(this);

    SearchPanel* searchPanel = new SearchPanel();
    layout->addWidget(searchPanel);

    CreatePanel* createPanel = new CreatePanel(searchPanel);
    layout->addWidget(createPanel);
}

void OptionsPanel::paintEvent(QPaintEvent* _event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(_event);
}
