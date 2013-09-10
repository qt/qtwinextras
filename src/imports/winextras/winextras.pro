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
    qquickdwmfeatures_p.h \
    qquickdwmfeatures_p_p.h \
    qquicktaskbarbutton_p.h \
    qquickjumplist_p.h \
    qquickthumbnailtoolbar_p.h \
    qquickthumbnailtoolbutton_p.h \
    qquickiconloader_p.h

SOURCES += \
    plugin.cpp \
    qquickdwmfeatures.cpp \
    qquicktaskbarbutton.cpp \
    qquickjumplist.cpp \
    qquickthumbnailtoolbar.cpp \
    qquickthumbnailtoolbutton.cpp \
    qquickiconloader.cpp

OTHER_FILES += \
    qmldir \
    JumpLink.qml \
    JumpDestination.qml \
    JumpListSeparator.qml

load(qml_plugin)
