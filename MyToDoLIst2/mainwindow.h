#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mycalendar.h"
#include "scheduleeditor.h"
#include "scheduleeditormanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow //主窗口类
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MyCalendar *calendar;
    ScheduleEditorManager *editorManager;
    QWidget *centralWidget;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
