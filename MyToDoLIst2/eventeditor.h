#ifndef EVENTEDITOR_H
#define EVENTEDITOR_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ScheduleFile;  // 前向声明

class EventEditor : public QDialog {//ScheduleFile编辑窗口类
    Q_OBJECT

public:
    EventEditor(ScheduleFile *scheduleFile, QWidget *parent = nullptr);

    // 获取更新后的 ScheduleFile 数据
    ScheduleFile* getUpdatedScheduleFile() const;

private slots:
    void saveEvent();  // 保存事件

private:
    // 用于编辑日程文件的字段
    QLineEdit *titleEdit;
    QDateTimeEdit *startTimeEdit;
    QDateTimeEdit *endTimeEdit;
    QComboBox *typeBox;
    QTextEdit *descriptionEdit;

    ScheduleFile *scheduleFile;  // 关联的 ScheduleFile 对象
};

#endif // EVENTEDITOR_H
