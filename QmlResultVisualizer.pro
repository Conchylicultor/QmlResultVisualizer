TEMPLATE = app

QT += qml quick widgets
QMAKE_CXXFLAGS += -std=c++11

SOURCES += src/main.cpp \
    src/sequencedetailsmodel.cpp \
    src/personlistmodel.cpp

HEADERS += \
    src/sequencedetailsmodel.h \
    src/personlistmodel.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

LIBS += `pkg-config opencv --libs`
