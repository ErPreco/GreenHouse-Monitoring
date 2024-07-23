#include "pagecontrollerpanel.h"

PageControllerPanel::PageControllerPanel(unsigned int _pagesCount)
: pagesCount(_pagesCount), pageIndicator(new QLabel("1")), totPageIndicator(new QLabel(QString::number(_pagesCount))) {
    setStyleSheet("background-color:#4AA042");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);

    // left arrow button
    QPushButton* leftArrowBtn = new QPushButton();
    leftArrowBtn->setIcon(QIcon(":/leftarrowicon"));
    layout->addWidget(leftArrowBtn);
    connect(leftArrowBtn, &QPushButton::pressed, this, &PageControllerPanel::prevPage);

    // page indicators label
    layout->addWidget(pageIndicator);
    layout->addWidget(new QLabel("/"));
    layout->addWidget(totPageIndicator);

    // right arrow button
    QPushButton* rightArrowBtn = new QPushButton();
    rightArrowBtn->setIcon(QIcon(":/rightarrowicon"));
    layout->addWidget(rightArrowBtn);
    connect(rightArrowBtn, &QPushButton::pressed, this, &PageControllerPanel::nextPage);
}

void PageControllerPanel::setPagesCount(unsigned int _v) {
    pagesCount = _v;
    totPageIndicator->setText(QString::number(_v));
}

void PageControllerPanel::updatePagesCount(bool _increase) {
    pagesCount += _increase ? 1 : (pagesCount == 1 ? 0 : -1);
    totPageIndicator->setText(QString::number(pagesCount));
}

void PageControllerPanel::setPageIndicator(unsigned int _v) {
    pageIndicator->setText(QString::number(_v));
}

void PageControllerPanel::prevPage() {
    if (auto curPageIdx = pageIndicator->text().toUInt(); curPageIdx > 1) {
        pageIndicator->setText(QString::number(curPageIdx - 1));
        emit changePage(true);
    }
}

void PageControllerPanel::nextPage() {
    if (auto curPageIdx = pageIndicator->text().toUInt(); curPageIdx < pagesCount) {
        pageIndicator->setText(QString::number(curPageIdx + 1));
        emit changePage(false);
    }
}

void PageControllerPanel::paintEvent(QPaintEvent* _event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(_event);
}
