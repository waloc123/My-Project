#ifndef TOASTNOTIFICATION_H
#define TOASTNOTIFICATION_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMainWindow>

class RemindWidget : public QWidget {//提醒弹窗界面类 todo
    Q_OBJECT

public:
    explicit RemindWidget(const QString &message, QWidget *parent = nullptr);
    void showNotification(QMainWindow *parentWindow);

private:
    QLabel *messageLabel;           // 显示提醒内容的标签
    QPropertyAnimation *fadeIn;     // 渐入动画
    QPropertyAnimation *fadeOut;    // 渐出动画
    QTimer *dismissTimer;           // 定时隐藏

private slots:
    void dismiss();                 // 关闭通知
};

#endif // TOASTNOTIFICATION_H
