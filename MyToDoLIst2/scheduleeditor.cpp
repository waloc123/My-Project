#include "scheduleeditor.h"
#include "schedulefile.h"
#include "eventeditor.h"
#include "eventviewer.h"
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <algorithm>
#include "mycalendar.h"

ScheduleEditor::ScheduleEditor(const QDate &date, QWidget *parent)
    : QWidget(parent), date(date) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    eventListWidget = new QListWidget(this);
    layout->addWidget(eventListWidget);

    QPushButton *newEventButton = new QPushButton("新建日程", this);
    layout->addWidget(newEventButton);
    connect(newEventButton, &QPushButton::clicked, this, &ScheduleEditor::createNewEvent);

    deleteEventButton = new QPushButton("删除选中日程", this);
    layout->addWidget(deleteEventButton);
    connect(deleteEventButton, &QPushButton::clicked, this, &ScheduleEditor::deleteSelectedEvent);


    // 初始化显示当前日期的所有日程
    refreshEventList();
    connect(eventListWidget, &QListWidget::itemClicked, this, &ScheduleEditor::viewEventDetails);

}

void ScheduleEditor::createNewEvent() {
    ScheduleFile *newSchedule = new ScheduleFile("", QDateTime(), QDateTime(), "", "", this);
    QString datestr = date.toString("yyyy/MM/dd");
    QDateTime datetime = QDateTime::fromString(datestr, "yyyy/MM/dd");
    newSchedule->setStartTime(datetime);
    newSchedule->setEndTime(datetime);

    EventEditor editor(newSchedule, this);
    if (editor.exec() == QDialog::Accepted) {
        scheduleFiles.append(newSchedule);
        sortScheduleFiles(); // 排序
        refreshEventList();  // 更新显示
        connect(newSchedule, &ScheduleFile::reminderTriggered, this, &ScheduleEditor::handleScheduleReminder);
    } else {
        delete newSchedule; // 如果未保存，删除对象
    }

}

void ScheduleEditor::viewEventDetails(QListWidgetItem *item) {
    // 从 QListWidgetItem 获取对应的 ScheduleFile 指针
    ScheduleFile *scheduleFile = item->data(Qt::UserRole).value<ScheduleFile *>();

    if (scheduleFile) {
        EventEditor editor(scheduleFile, this);
        if (editor.exec() == QDialog::Accepted) {
            sortScheduleFiles(); // 重新排序
            refreshEventList();  // 更新显示
        }
    } else {
        QMessageBox::warning(this, "错误", "无法找到对应的日程文件！");
    }
}

void ScheduleEditor::sortScheduleFiles() {
    // 按开始时间排序
    std::sort(scheduleFiles.begin(), scheduleFiles.end(), [](ScheduleFile *a, ScheduleFile *b) {
        return a->getDeadLineTime() < b->getDeadLineTime();
    });
}

void ScheduleEditor::refreshEventList() {
    eventListWidget->clear(); // 清空显示列表

    // 按排序后的顺序重新添加项目
    for (const auto &scheduleFile : scheduleFiles) {
        QString displayText = scheduleFile->getTitle() + " - " + scheduleFile->getDeadLineTime().toString();
        QListWidgetItem *item = new QListWidgetItem(displayText, eventListWidget);

        // 将 ScheduleFile 指针存储在 QListWidgetItem 中
        item->setData(Qt::UserRole, QVariant::fromValue(scheduleFile));
        emit scheduleChanged(scheduleFile->getDeadLineTime().date());

        scheduleFile->updateRemindTime();
    }
}

QList<ScheduleFile*> ScheduleEditor::getScheduleFiles()
{
    return this->scheduleFiles;
}


void ScheduleEditor::deleteSelectedEvent() {
    QListWidgetItem *selectedItem = eventListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "提示", "请选择要删除的日程！");
        return;
    }

    ScheduleFile *scheduleFile = selectedItem->data(Qt::UserRole).value<ScheduleFile *>();
    if (!scheduleFile) {
        QMessageBox::warning(this, "错误", "无法找到对应的日程文件！");
        return;
    }

    int reply = QMessageBox::question(this, "确认删除", "确认删除该日程？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        scheduleFiles.removeOne(scheduleFile);  // 从列表中移除
        delete scheduleFile;  // 删除对象
        refreshEventList();  // 更新界面
    }
}



void ScheduleEditor::handleScheduleReminder(ScheduleFile *file) {
    emit editorReminderTriggered(file);
}

void ScheduleEditor::LoadScheduleFileData()
{
    //todo;
}

void ScheduleEditor::SaveScheduleFileData()
{
    //todo;
}
