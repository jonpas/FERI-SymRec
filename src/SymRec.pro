QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SymRec
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    neuralnetwork.cpp \
    neuron.cpp \
    scene.cpp \
    symbol.cpp \
    view.cpp

HEADERS += \
    mainwindow.h \
    neuralnetwork.h \
    neuron.h \
    scene.h \
    symbol.h \
    view.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
