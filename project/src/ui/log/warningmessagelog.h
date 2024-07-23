#ifndef WARNING_MESSAGE_LOG_H
#define WARNING_MESSAGE_LOG_H

#include <QMessageBox>
#include "messagelog.h"

class WarningMessageLog : public MessageLog {
    private:
        QMessageBox::StandardButtons buttons;
        QMessageBox::StandardButton result;

    public:
        WarningMessageLog(const QString&, const QString& = "Warning message", const QMessageBox::StandardButtons& = QMessageBox::Ok);

        QMessageBox::StandardButton getResult() const;

        void showMessage() override;
};

#endif
