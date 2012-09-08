TARGET = mdispwindowqt
TEMPLATE = app
CONFIG += qt debug
INCLUDEPATH += ${MILDIR}/include
LIBS += -L${MILDIR}/lib -lmil
SOURCES += mdispwindowqt.cpp
HEADERS += mdispwindowqt.h
