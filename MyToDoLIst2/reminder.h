#ifndef REMINDER_H
#define REMINDER_H

#include <QWidget>
#include "schedulefile.h"

class Reminder : public QWidget//提醒窗口类
{
    Q_OBJECT
public:
    explicit Reminder(QWidget *parent = nullptr);

public:
    void handleReminder(ScheduleFile *file);

private:
    void showReminderPopup(ScheduleFile *file);

signals:

};

#endif // REMINDER_H
