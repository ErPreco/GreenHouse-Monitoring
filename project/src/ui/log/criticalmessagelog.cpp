#include "criticalmessagelog.h"

CriticalMessageLog::CriticalMessageLog(const QString& _message, const QString& _title) : MessageLog(_title, _message) {}

void CriticalMessageLog::showMessage() {
    QMessageBox::critical(this, title, message);
}
