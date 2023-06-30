QT       += core gui
QT       += network
QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp/father_thread.cpp \
    cpp/get_thread.cpp \
    cpp/main.cpp \
    cpp/mainwindow.cpp \
    cpp/mythread.cpp \
    cpp/send_page.cpp \
    cpp/sign_up_page.cpp \
    cpp/thread_write.cpp \
    cpp/user_account.cpp \
    cpp/user_page.cpp \
    cpp/thread10.cpp



HEADERS += \
    header/father_thread.h \
    header/get_thread.h \
    header/mainwindow.h \
    header/mythread.h \
    header/send_page.h \
    header/sign_up_page.h \
    header/thread_write.h \
    header/user_account.h \
    header/user_page.h \
    header/thread10.h


FORMS += \
    mainwindow.ui \
    send_page.ui \
    sign_up_page.ui \
    user_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
