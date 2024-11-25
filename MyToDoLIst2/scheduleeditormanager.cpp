#include "scheduleeditormanager.h"
#include "scheduleeditor.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "mycalendar.h"
#include <QDebug>

ScheduleEditorManager::ScheduleEditorManager(QWidget *parent,MyCalendar*Calendar)
    : QWidget(parent), currentDate(QDate::currentDate()) {

     reminder = new Reminder(this); // 创建 Reminder 实例
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->calendar=Calendar;
    stackedWidget = new QStackedWidget(this);
    layout->addWidget(stackedWidget);

    QPushButton *prevDayButton = new QPushButton("前一天", this);
    QPushButton *nextDayButton = new QPushButton("后一天", this);
    layout->addWidget(prevDayButton);
    layout->addWidget(nextDayButton);

    connect(prevDayButton, &QPushButton::clicked, [this]() {
        currentDate = currentDate.addDays(-1);
        showScheduleEditorForDate(currentDate);
    });

    connect(nextDayButton, &QPushButton::clicked, [this]() {
        currentDate = currentDate.addDays(1);
        showScheduleEditorForDate(currentDate);
    });

}

void ScheduleEditorManager::showScheduleEditorForDate(const QDate &date) {
    if (!scheduleEditors.contains(date)) {
        createScheduleEditorForDate(date);
    }

    stackedWidget->setCurrentWidget(scheduleEditors[date]);
}

void ScheduleEditorManager::createScheduleEditorForDate(const QDate &date) {
    ScheduleEditor *editor = new ScheduleEditor(date, this);
    scheduleEditors[date] = editor;
    stackedWidget->addWidget(editor);
    connect(editor, &ScheduleEditor::scheduleChanged, calendar, &MyCalendar::updateScheduleTexts);
    connect(editor, &ScheduleEditor::editorReminderTriggered, reminder, &Reminder::handleReminder);
}

ScheduleEditor* ScheduleEditorManager::getScheduleEditor(QDate date)
{
    return scheduleEditors[date];
}

QMap<QDate, ScheduleEditor*> ScheduleEditorManager::getScheduleEditorMap()
{
    return this->scheduleEditors;
}



