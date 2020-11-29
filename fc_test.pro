QT += quick sql multimedia xml printsupport widgets network #location webengine webview concurrent

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        event.cpp \
        local_db_connection.cpp \
        local_db_serve.cpp \
        main.cpp \
        main_serve_qml.cpp \
        systemtray.cpp \
        woocommerce_connection.cpp \
        woocommerce_serve.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    Singleton.h \
    event.h \
    local_db_connection.h \
    local_db_serve.h \
    main_serve_qml.h \
    structures.h \
    systemtray.h \
    woocommerce_connection.h \
    woocommerce_serve.h
