#include "reminder.h"
#include <QMessageBox>

Reminder::Reminder(QWidget *parent)
    : QWidget{parent}
{

}

void Reminder::handleReminder(ScheduleFile *file) {
    showReminderPopup(file);
}

void Reminder::showReminderPopup(ScheduleFile *file) {
    QMessageBox::information(nullptr, "提醒", "即将到期的日程：" + file->getTitle());
}
