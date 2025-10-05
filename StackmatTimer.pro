QT += opengl gui network xml widgets

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/threadchrono.cpp \
    src/lcdnumber_stackmat.cpp \
    src/variables.cpp \
    src/tabwidgetscores.cpp \
    src/helpclass.cpp \
    src/qlabelstackmat.cpp
HEADERS += src/mainwindow.h \
    src/constants.h \
    src/threadchrono.h \
    src/lcdnumber_stackmat.h \
    src/variables.h \
    src/tabwidgetscores.h \
    src/helpclass.h \
    src/qlabelstackmat.h
RESOURCES += stackmat.qrc
RC_FILE = qtStackmat.rc
