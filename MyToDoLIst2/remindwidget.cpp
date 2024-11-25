#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include "remindwidget.h"
#include <QMainWindow>

RemindWidget::RemindWidget(const QString &message, QWidget *parent)
    : QWidget(parent), messageLabel(new QLabel(message, this)) {

    // 设置窗口样式
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    // 设置阴影效果
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(0, 4);
    setGraphicsEffect(shadowEffect);

    // 设置布局和内容
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(messageLabel);
    layout->setContentsMargins(10, 10, 10, 10);

    messageLabel->setStyleSheet("QLabel { color: white; font-size: 14px; }");
    setStyleSheet("background-color: rgba(0, 0, 0, 0.7); border-radius: 8px;");

    // 设置动画
    fadeIn = new QPropertyAnimation(this, "windowOpacity");
    fadeIn->setDuration(500);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);

    fadeOut = new QPropertyAnimation(this, "windowOpacity");
    fadeOut->setDuration(500);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);

    // 定时器，通知自动关闭
    dismissTimer = new QTimer(this);
    dismissTimer->setInterval(3000); // 通知显示 3 秒
    connect(dismissTimer, &QTimer::timeout, this, &RemindWidget::dismiss);
}

void RemindWidget::showNotification(QMainWindow *parentWindow) {
    if (!parentWindow) {
        qWarning() << "无效的父窗口";
        return;
    }

    // 获取 QMainWindow 的几何信息
    QRect parentGeometry = parentWindow->geometry();

    // 设置通知窗口的位置（父窗口的底部中央）
    int x = parentGeometry.center().x() - width() / 2;
    int y = parentGeometry.bottom() - height() - 20; // 距离父窗口底部 20px
    move(x, y);

    // 显示通知并播放渐入动画
    resize(250, 50);
    show();
    fadeIn->start();
    dismissTimer->start();

}

void RemindWidget::dismiss() {
    // 播放渐出动画并隐藏
    fadeOut->start();
    connect(fadeOut, &QPropertyAnimation::finished, this, &RemindWidget::close);
}
