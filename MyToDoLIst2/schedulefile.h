#ifndef SCHEDULEFILE_H
#define SCHEDULEFILE_H

#include <QObject>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

class ScheduleFile : public QObject {//日程文件类
    Q_OBJECT

public:
    ScheduleFile(const QString &title, const QDateTime &startTime, const QDateTime &endTime, const QString &type, const QString &description, QObject *parent = nullptr);

    QString getTitle() const;
    void setTitle(const QString &title);

    QDateTime getDeadLineTime() const;
    void setStartTime(const QDateTime &startTime);

    QDateTime getReminderTime() const;
    void setEndTime(const QDateTime &endTime);

    QString getType() const;
    void setType(const QString &type);

    QString getDescription() const;
    void setDescription(const QString &description);


    QJsonObject toJson() const {
        QJsonObject jsonObj;
        jsonObj["title"] = title;
        jsonObj["startTime"] = DeadlineTime.toString();
        jsonObj["type"] = type;
        jsonObj["endTime"] = RemindTime.toString();
        jsonObj["description"]=description;
        return jsonObj;
    }

    // 从 JSON 恢复数据
    static ScheduleFile fromJson(const QJsonObject &jsonObj) {
        QString _title = jsonObj["title"].toString();
        QDateTime _startTime = QDateTime::fromString(jsonObj["startTime"].toString());
        QString _type = jsonObj["type"].toString();
        QDateTime _endTime= QDateTime::fromString(jsonObj["endTime"].toString());
        QString _description=jsonObj["description"].toString();
        return ScheduleFile(_title, _startTime,_endTime, _type,_description);
    }
public:
    void setReminderTime(const QDateTime &reminderTime);

    void updateRemindTime();

signals:
    void reminderTriggered(ScheduleFile *file);

private slots:
    void onReminderTimeout();

private:
    QTimer *reminderTimer;


private:
    QString title;
    QDateTime DeadlineTime;
    QDateTime RemindTime;
    QString type;
    QString description;
};

#endif // SCHEDULEFILE_H
