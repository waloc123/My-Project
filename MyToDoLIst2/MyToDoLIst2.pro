QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    eventeditor.cpp \
    eventviewer.cpp \
    main.cpp \
    mainwindow.cpp \
    mycalendar.cpp \
    reminder.cpp \
    remindwidget.cpp \
    scheduleeditor.cpp \
    scheduleeditormanager.cpp \
    schedulefile.cpp \
    staticsystem.cpp

HEADERS += \
    eventeditor.h \
    eventviewer.h \
    mainwindow.h \
    mycalendar.h \
    reminder.h \
    remindwidget.h \
    scheduleeditor.h \
    scheduleeditormanager.h \
    schedulefile.h \
    staticsystem.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Data.qrc
