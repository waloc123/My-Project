#ifndef MYCALENDAR_H
#define MYCALENDAR_H

#include <QCalendarWidget>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include "scheduleeditormanager.h"
#include <QVector>

class MyCalendar : public QCalendarWidget {  //日历窗口类
    Q_OBJECT

public:
    MyCalendar(QWidget *parent = nullptr,ScheduleEditorManager *editorManager=nullptr);
    void updateScheduleTexts(const QDate &date);
private slots:
    void onDateClicked(const QDate &date);//点击日历窗口切换ScheduleEditor
protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate date) const override;//绘制日历界面
    void drawSampleText(QPainter *painter, const QRect &rect, const QDate &date) const;//绘制任务时间线

private:
    ScheduleEditorManager *editorManager;

private:
    QMap<QDate, QStringList> scheduleTexts; // 每个日期与对应的时间线文本列表
private:
    QFont eventFont; // 时间线文本字体
    QFont dateFont;
    QColor eventTextColor; // 时间线文本颜色
    QColor dateTextColor;
    int Page_month;
    int Page_year;
};

#endif // MYCALENDAR_H
