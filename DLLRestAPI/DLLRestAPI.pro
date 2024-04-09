QT += gui core widgets network

TEMPLATE = lib
DEFINES += DLLRESTAPI_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dllrestapi.cpp \
    login.cpp \
    transactions.cpp \
    withdrawcall.cpp

HEADERS += \
    DLLRestAPI_global.h \
    dllrestapi.h \
    login.h \
    transactions.h \
    withdrawcall.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    transactions.ui
