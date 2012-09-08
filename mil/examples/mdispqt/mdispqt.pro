# -------------------------------------------------
# Project created by QtCreator 2010-03-03T16:49:29
# -------------------------------------------------
TARGET = mdispqt
TEMPLATE = app
INCLUDEPATH += ${MILDIR}/include
LIBS += -L${MILDIR}/lib -lmil
SOURCES += main.cpp \
    mainframe.cpp \
    mdispqtapp.cpp \
    roiprefsdlg.cpp \
    aboutbox.cpp \
    childframe.cpp \
    mdispqtview.cpp
HEADERS += mainframe.h \
    mdispqtapp.h \
    roiprefsdlg.h \
    aboutbox.h \
    childframe.h \
    mdispqtview.h
FORMS += mainframe.ui \
    roiprefsdlg.ui \
    aboutbox.ui
RESOURCES += mdispqt.qrc
