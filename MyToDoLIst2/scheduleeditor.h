#ifndef SCHEDULEEDITOR_H
#define SCHEDULEEDITOR_H

#include "schedulefile.h"
#include <QWidget>
#include <QDate>
#include <QList>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMap>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class ScheduleFile;  // 前向声明

class ScheduleEditor : public QWidget {//日程文件编辑界面类
    Q_OBJECT

public:
    ScheduleEditor(const QDate &date, QWidget *parent = nullptr);
    QList<ScheduleFile*> getScheduleFiles();

    void LoadScheduleFileData();//todo
    void SaveScheduleFileData();//todo

private slots:
    void createNewEvent();  // 新建日程
    void viewEventDetails(QListWidgetItem *item);  // 查看日程详情
      void deleteSelectedEvent();  // 删除选中日程
private:
    QDate date;  // 当前编辑的日期
    QListWidget *eventListWidget;  // 显示日程列表的控件
    QList<ScheduleFile*> scheduleFiles;  // 存储当前日期的日程文件
     QPushButton *deleteEventButton;  // 删除按钮
    void sortScheduleFiles();
    void refreshEventList();



signals:
    void editorReminderTriggered(ScheduleFile *file);//提醒触发信号

private slots:
    void handleScheduleReminder(ScheduleFile *file);

signals:
    void scheduleChanged(const QDate &date);  //日程文件信息变更信号
};

#endif // SCHEDULEEDITOR_H
