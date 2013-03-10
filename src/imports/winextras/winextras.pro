CXX_MODULE = qml
TARGET  = qml_winextras
TARGETPATH = QtWinExtras
IMPORT_VERSION = 1.0

QT += qml quick winextras winextras-private

QML_FILES += \
    JumpLink.qml \
    JumpDestination.qml \
    JumpListSeparator.qml

HEADERS += \
    qwinextrasplugin.h \
    qquickwindwmfeatures.h \
    qquickwindwmfeatures_p.h \
    qquickwintaskbarbutton.h \
    qquickjumplist.h

SOURCES += \
    qwinextrasplugin.cpp \
    qquickwindwmfeatures.cpp \
    qquickwintaskbarbutton.cpp \
    qquickjumplist.cpp

OTHER_FILES += \
    qmldir \
    JumpLink.qml \
    JumpDestination.qml \
    JumpListSeparator.qml

load(qml_plugin)
