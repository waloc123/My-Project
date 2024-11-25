#ifndef SCHEDULEEDITORMANAGER_H
#define SCHEDULEEDITORMANAGER_H

#include <QObject>
#include <QWidget>
#include <QDate>
#include <QStackedWidget>
#include <QPushButton>
#include "scheduleeditor.h"
#include <QJsonObject>
#include <QJsonArray>
#include "reminder.h"

class MyCalendar;

class ScheduleEditorManager : public QWidget {//日程编辑界面系统类，管理多个日程编辑界面
    Q_OBJECT

public:
    ScheduleEditorManager(QWidget *parent=nullptr,MyCalendar*Calendar=nullptr);

    void showScheduleEditorForDate(const QDate &date);//显示对应日期的日程编辑界面

    ScheduleEditor* getScheduleEditor(QDate date);
    QMap<QDate, ScheduleEditor*> getScheduleEditorMap();
    MyCalendar*calendar;
private:
    QStackedWidget *stackedWidget;
    QMap<QDate, ScheduleEditor*> scheduleEditors;  // 存储每个日期的日程编辑器
    QDate currentDate;

    void createScheduleEditorForDate(const QDate &date);  //创建对应日期的日程编辑界面

    void saveEditorsData();//todo
    void LoadEditorsData();//todo

private:
    Reminder *reminder;



};

#endif // SCHEDULEEDITORMANAGER_H
