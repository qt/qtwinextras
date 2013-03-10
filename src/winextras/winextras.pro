TARGET = QtWinExtras

load(qt_module)

SOURCES += \
    qwinfunctions.cpp \
    qwinfunctions_p.cpp \
    qwintaskbarbutton.cpp \
    windowsguidsdefs.cpp \
    qjumplist.cpp \
    qwincolorizationcolorchangeevent.cpp \
    qwincompositionstatechangeevent.cpp \
    qwineventfilter.cpp \
    qwintaskbarbuttoncreatedevent.cpp \
    qwinthemechangeevent.cpp

HEADERS += \
    qwinfunctions.h \
    qwinextrasglobal.h \
    qwinfunctions_p.h \
    qwintaskbarbutton_p.h \
    qwintaskbarbutton.h \
    qjumplist.h \
    qwincolorizationcolorchangeevent.h \
    qwincolorizationcolorchangeevent_p.h \
    qwincompositionstatechangeevent.h \
    qwincompositionstatechangeevent_p.h \
    qwintaskbarbuttoncreatedevent.h \
    qwintaskbarbuttoncreatedevent_p.h \
    winshobjidl_p.h \
    winpropkey_p.h \
    qwineventfilter_p.h \
    qwinthemechangeevent.h \
    qwinthemechangeevent_p.h

QMAKE_DOCS = $$PWD/doc/qtwinextras.qdocconf

LIBS += -lole32 -lshlwapi
LIBS -= -luuid

OTHER_FILES += \
    doc/qtwinextras.qdocconf \
    doc/src/qtwinextras-index.qdoc \
    doc/src/qtwinextras-module-cpp.qdoc \
    doc/src/qtwinextras-module-qml.qdoc \
    doc/snippets/code/use-qtwinextras.pro \
    doc/snippets/code/jumplist.cpp \
    doc/snippets/code/use-qtwinextras.cpp
