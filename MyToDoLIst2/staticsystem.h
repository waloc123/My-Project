#ifndef STATICSYSTEM_H
#define STATICSYSTEM_H

#include <QWidget>

class StaticSystem : public QWidget//日程信息统计类
{
    Q_OBJECT
public:
    explicit StaticSystem(QWidget *parent = nullptr);
    void TaskFinishingStatistics();
    void TaskDistributionStatistics();
    void GetAdvice();
signals:

};

#endif // STATICSYSTEM_H
