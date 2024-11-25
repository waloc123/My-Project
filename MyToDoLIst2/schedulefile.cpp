#include "schedulefile.h"
#include <QDebug>

ScheduleFile::ScheduleFile(const QString &title, const QDateTime &startTime, const QDateTime &endTime, const QString &type, const QString &description, QObject *parent)
    : QObject(parent), title(title), DeadlineTime(startTime), RemindTime(endTime), type(type), description(description) {
    reminderTimer = new QTimer(this);

    updateRemindTime();


}

QString ScheduleFile::getTitle() const {
    return title;
}

void ScheduleFile::setTitle(const QString &title) {
    this->title = title;
}

QDateTime ScheduleFile::getDeadLineTime() const {
    return DeadlineTime;
}

void ScheduleFile::setStartTime(const QDateTime &startTime) {
    this->DeadlineTime = startTime;
}

QDateTime ScheduleFile::getReminderTime() const {
    return RemindTime;
}

void ScheduleFile::setEndTime(const QDateTime &endTime) {
    this->RemindTime = endTime;
}

QString ScheduleFile::getType() const {
    return type;
}

void ScheduleFile::setType(const QString &type) {
    this->type = type;
}

QString ScheduleFile::getDescription() const {
    return description;
}

void ScheduleFile::setDescription(const QString &description) {
    this->description = description;
}

void ScheduleFile::setReminderTime(const QDateTime &newReminderTime) {
    RemindTime = newReminderTime;
    reminderTimer->stop();

    qint64 msecsToReminder = QDateTime::currentDateTime().msecsTo(RemindTime);
    if (msecsToReminder > 0) {
        reminderTimer->start(msecsToReminder);
    }
}

void ScheduleFile::onReminderTimeout() {
    qDebug()<<"Remind!"<<this->title;
    emit reminderTriggered(this);
}

void ScheduleFile::updateRemindTime()
{
    qint64 msecsToReminder = QDateTime::currentDateTime().msecsTo(RemindTime);
    qDebug()<<"RemindTimer"<<RemindTime<<QDateTime::currentDateTime();
    if (msecsToReminder > 0) {
        reminderTimer->setSingleShot(true);
        reminderTimer->start(msecsToReminder);

        connect(reminderTimer, &QTimer::timeout, this, &ScheduleFile::onReminderTimeout);
    }
}
