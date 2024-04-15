QT       += core gui widgets
QT += serialport
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    creditdebitq.cpp \
    data.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp

HEADERS += \
    admin.h \
    creditdebitq.h \
    mainmenu.h \
    data.h \
    mainwindow.h

FORMS += \
    admin.ui \
    creditdebitq.ui \
    mainmenu.ui \
    mainwindow.ui

# Default rules for deployment.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DLLPinCode/build/release/ -lDLLPinCode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DLLPinCode/build/debug/ -lDLLPinCode

INCLUDEPATH += $$PWD/../DLLPinCode
DEPENDPATH += $$PWD/../DLLPinCode

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DLLRestAPI/build/release/ -lDLLRestAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DLLRestAPI/build/debug/ -lDLLRestAPI

INCLUDEPATH += $$PWD/../DLLRestAPI
DEPENDPATH += $$PWD/../DLLRestAPI

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DLLSerialport/build/release/ -lDLLSerialport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DLLSerialport/build/debug/ -lDLLSerialport

INCLUDEPATH += $$PWD/../DLLSerialport
DEPENDPATH += $$PWD/../DLLSerialport
