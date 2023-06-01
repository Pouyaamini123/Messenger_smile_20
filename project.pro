QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mythread.cpp \
    sign_up_page.cpp \
    user_account.cpp \
    user_page.cpp

HEADERS += \
    mainwindow.h \
    mythread.h \
    sign_up_page.h \
    user_account.h \
    user_page.h

FORMS += \
    mainwindow.ui \
    sign_up_page.ui \
    user_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
