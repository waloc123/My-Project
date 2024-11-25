#include "eventviewer.h"

#include "schedulefile.h"
#include "eventeditor.h"

EventViewer::EventViewer(const QList<ScheduleFile*> &scheduleFiles, QWidget *parent)
    : QDialog(parent), scheduleFiles(scheduleFiles) {

    setWindowTitle("查看日程");
    QVBoxLayout *layout = new QVBoxLayout(this);

    QListWidget *listWidget = new QListWidget(this);

    for (const auto &scheduleFile : scheduleFiles) {
        // 只显示指定日期的日程文件
        listWidget->addItem(scheduleFile->getTitle() + " - " + scheduleFile->getDeadLineTime().toString());
    }

    layout->addWidget(listWidget);

    QPushButton *editButton = new QPushButton("修改选中日程", this);
    layout->addWidget(editButton);
    connect(editButton, &QPushButton::clicked, [=]() {
        // 获取选中的项目并启动编辑
        // 你可以添加编辑逻辑，这里是一个简化的例子
        // 假设我们会打开编辑界面
        ScheduleFile *selectedFile = scheduleFiles.at(listWidget->currentRow());
        EventEditor editor(selectedFile, this);
        editor.exec();
    });
}
