#ifndef CRITICAL_MESSAGE_LOG_H
#define CRITICAL_MESSAGE_LOG_H

#include <QMessageBox>
#include "messagelog.h"

class CriticalMessageLog : public MessageLog {
    public:
        CriticalMessageLog(const QString&, const QString& = "Error message");

        void showMessage() override;
};

#endif
