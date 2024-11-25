#include "mycalendar.h"
#include "scheduleeditormanager.h"
#include <QTextCharFormat>
#include <QToolTip>
#include <QPainter>
#include "schedulefile.h"
#include <QDebug>


MyCalendar::MyCalendar(QWidget *parent,ScheduleEditorManager *editorManager): QCalendarWidget(parent)  {
    this->editorManager = editorManager;
    connect(this, &QCalendarWidget::clicked, this, &MyCalendar::onDateClicked);
   eventFont = QFont("Arial", 9); // 设置字体
   eventTextColor = QColor(50, 50, 50); // 设置文本颜色
   dateFont=QFont("Arial", 9);
   dateFont.setBold(true);


   Page_month=QDate::currentDate().month();
   Page_year=QDate::currentDate().year();



   connect(this, &QCalendarWidget::currentPageChanged, [this](int year, int month){
       Page_month = month;
       Page_year=year;
   });

}

void MyCalendar::onDateClicked(const QDate &date) {
    editorManager->showScheduleEditorForDate(date);  // 打开对应日期的日程编辑器
}

void MyCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate date) const {

    if (date == selectedDate())
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(224,255,255));
        painter->drawRoundedRect(rect.x(), rect.y() + 3, rect.width()-1, rect.height() - 2, 3, 3);
        QRect dateRect = QRect(rect.x()+4, rect.y()+6, rect.width(), rect.height());
        painter->setFont(dateFont);
        painter->setPen(QColor(0,0,0));
        painter->drawText(dateRect, Qt::AlignTop, QString::number(date.day()));
        painter->restore();
    }

    else if (date == QDate::currentDate())
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0, 161, 255));
        painter->drawRoundedRect(rect.x(), rect.y() + 3, rect.width()-1, rect.height() - 2, 3, 3);
        painter->setBrush(QColor(255, 255, 255));
        painter->drawRoundedRect(rect.x() + 1, rect.y() + 4, rect.width() - 2, rect.height() - 3, 2, 2);
        painter->setPen(QColor(0, 161, 255));
        painter->setFont(dateFont);
        QRect dateRect = QRect(rect.x()+4, rect.y()+6, rect.width(), rect.height());
        painter->drawText(dateRect, Qt::AlignTop, QString::number(date.day()));
        painter->restore();
    }

    else if (date < minimumDate() || date > maximumDate())
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(249, 249, 249));
        painter->drawRect(rect.x(), rect.y() + 3, rect.width(), rect.height() - 6);
        painter->setPen(QColor(220, 220, 220));
        painter->drawText(rect, Qt::AlignLeft | (Qt::AlignTop), QString::number(date.day()));
        painter->restore();
    }

    else
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0, 0, 0));
        painter->drawRoundedRect(rect.x(), rect.y() + 3, rect.width()-1, rect.height() - 2, 3, 3);
        painter->setBrush(QColor(255, 255, 255));
        painter->drawRoundedRect(rect.x() + 1, rect.y() + 4, rect.width() - 2, rect.height() - 3, 2, 2);
        painter->setPen(QColor(0, 0, 0));
        if(date.month() !=Page_month||date.year()!=Page_year)
        {
            painter->setPen(QColor(145, 145, 145));
        }

        QRect dateRect = QRect(rect.x()+4, rect.y()+6, rect.width(), rect.height());
        painter->setFont(dateFont);
        painter->drawText(dateRect, Qt::AlignTop, QString::number(date.day()));
        painter->restore();

    }

    drawSampleText(painter,rect,date);
}



void MyCalendar::drawSampleText(QPainter *painter, const QRect &rect, const QDate &date) const {
    // 检查是否有 ScheduleEditor 对象
    //qDebug()<<"update2";
    if (!editorManager->getScheduleEditorMap().contains(date)) {
       // qDebug()<<"update3";
        return;
    }

    ScheduleEditor *editor = editorManager->getScheduleEditorMap().value(date);
    if (!editor) {
      //  qDebug()<<"update4";
        return;
    }

    // 获取 ScheduleEditor 的 ScheduleFile 列表
    const QList<ScheduleFile *> &scheduleFiles = editor->getScheduleFiles();
    if (scheduleFiles.isEmpty()) {
      //  qDebug()<<"update5";
        return;
    }

    // 绘制时间线文本
    qDebug()<<"update66666"<<date;
    painter->save();
    painter->setFont(eventFont);
    painter->setPen(eventTextColor);

    int textY = rect.y()+6+20; // 从日期数字下方开始绘制
    int textX=rect.x()+5;
    for (ScheduleFile *file : scheduleFiles) {

         painter->setBrush(QColor(220,220,220));
        if(file->getType()=="重要型")
            {
             painter->setBrush(QColor(12,220,220));
        }
        painter->drawRoundedRect(textX, textY, 95, 12, 3, 3);
        QString text =" "+file->getDeadLineTime().time().toString().mid(0,5)+" "+file->getTitle();
       // bool lengthFlag=text.length()==text.mid(0,11).length();
        //text=text.mid(0,11);
        //if(!lengthFlag)
         //   text+="...";
        QRect dateRect = QRect(textX, textY, rect.width(), rect.height());
        painter->drawText(dateRect, Qt::AlignLeft | Qt::AlignTop, text);
        textY += 15; // 每行间隔 15 像素
    }

    painter->restore();
}


void MyCalendar::updateScheduleTexts(const QDate &date) {
    if (editorManager->getScheduleEditorMap().contains(date)) {
        this->update();
         qDebug()<<"update1";
    }
}



