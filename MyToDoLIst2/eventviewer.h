#ifndef EVENTVIEWER_H
#define EVENTVIEWER_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QList>

class ScheduleFile;  // 前向声明

class EventViewer : public QDialog {//ScheduleFile查看窗口类
    Q_OBJECT

public:
    EventViewer(const QList<ScheduleFile*> &scheduleFiles, QWidget *parent = nullptr);

private:
    QList<ScheduleFile*> scheduleFiles;  // 存储的日程文件
};

#endif // EVENTVIEWER_H
