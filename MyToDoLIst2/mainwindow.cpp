#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建日历组件
    editorManager = new ScheduleEditorManager(this,calendar);
    calendar = new MyCalendar(this,editorManager);
    editorManager->calendar=calendar;
    editorManager->showScheduleEditorForDate(QDate::currentDate());  // 初始化显示当前日期的日程
    // 创建日程编辑器管理器

    // 使用QSplitter来分隔日历和日程编辑器
    QSplitter *splitter = new QSplitter(Qt::Horizontal, centralWidget);
    splitter->addWidget(calendar);  // 添加日历到左边
    splitter->addWidget(editorManager);  // 添加日程编辑器管理器到右边

    splitter->setStretchFactor(0, 3);  // 左侧日历占2份
    splitter->setStretchFactor(1, 1);  // 右侧编辑器占1份

    // 设置中央部件的布局
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(splitter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

