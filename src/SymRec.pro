QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SymRec
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    layer.cpp \
    main.cpp \
    mainwindow.cpp \
    neuralnetwork.cpp \
    scene.cpp \
    view.cpp

HEADERS += \
    layer.h \
    mainwindow.h \
    neuralnetwork.h \
    scene.h \
    view.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
