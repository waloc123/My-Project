#include "eventeditor.h"
#include "schedulefile.h"

EventEditor::EventEditor(ScheduleFile *scheduleFile, QWidget *parent)
    : QDialog(parent), scheduleFile(scheduleFile) {

    setWindowTitle("编辑日程");
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 初始化控件并连接数据
    titleEdit = new QLineEdit(this);
    titleEdit->setText(scheduleFile->getTitle());
    layout->addWidget(new QLabel("标题:"));
    layout->addWidget(titleEdit);

    startTimeEdit = new QDateTimeEdit(scheduleFile->getDeadLineTime(), this);
    layout->addWidget(new QLabel("截止时间:"));
    layout->addWidget(startTimeEdit);

    endTimeEdit = new QDateTimeEdit(scheduleFile->getReminderTime(), this);
    layout->addWidget(new QLabel("提醒时间:"));
    layout->addWidget(endTimeEdit);

    typeBox = new QComboBox(this);
    typeBox->addItems({"普通型", "重要型", "每日型", "每周型"});
    typeBox->setCurrentText(scheduleFile->getType());
    layout->addWidget(new QLabel("任务类型:"));
    layout->addWidget(typeBox);

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setText(scheduleFile->getDescription());
    layout->addWidget(new QLabel("描述:"));
    layout->addWidget(descriptionEdit);

    // 保存按钮
    QPushButton *saveButton = new QPushButton("保存", this);
    layout->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, this, &EventEditor::saveEvent);
}

ScheduleFile* EventEditor::getUpdatedScheduleFile() const {
    return scheduleFile;
}

void EventEditor::saveEvent() {
    // 更新 ScheduleFile 对象的数据
    scheduleFile->setTitle(titleEdit->text());
    scheduleFile->setStartTime(startTimeEdit->dateTime());
    scheduleFile->setEndTime(endTimeEdit->dateTime());
    scheduleFile->setType(typeBox->currentText());
    scheduleFile->setDescription(descriptionEdit->toPlainText());

    accept();  // 关闭对话框
}
