QT += core network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        my_comparison.cpp \
        my_recurring.cpp \
        my_reply.cpp \
        reply_comparison.cpp \
        server_answer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    my_comparison.h \
    my_recurring.h \
    my_reply.h \
    reply_comparison.h \
    server_answer.h
