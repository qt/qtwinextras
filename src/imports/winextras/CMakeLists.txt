# Generated from winextras.pro.

#####################################################################
## qml_winextras Plugin:
#####################################################################

qt_add_qml_module(qml_winextras
    URI "QtWinExtras"
    VERSION "1.${CMAKE_PROJECT_VERSION_MINOR}"
    CLASSNAME QWinExtrasQmlPlugin
    SOURCES
        plugin.cpp
        qquickdwmfeatures.cpp qquickdwmfeatures_p.h
        qquickdwmfeatures_p_p.h
        qquickiconloader.cpp qquickiconloader_p.h
        qquickjumplist.cpp qquickjumplist_p.h
        qquickjumplistcategory.cpp qquickjumplistcategory_p.h
        qquickjumplistitem.cpp qquickjumplistitem_p.h
        qquicktaskbarbutton.cpp qquicktaskbarbutton_p.h
        qquickthumbnailtoolbar.cpp qquickthumbnailtoolbar_p.h
        qquickthumbnailtoolbutton.cpp qquickthumbnailtoolbutton_p.h
        qquickwin_p.h
    LIBRARIES
        Qt::WinExtrasPrivate
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::WinExtras
)

#### Keys ignored in scope 1:.:.:winextras.pro:<TRUE>:
# CXX_MODULE = "qml"
# IMPORT_VERSION = "1.$$QT_MINOR_VERSION"
# OTHER_FILES = "qmldir" "JumpListLink.qml" "JumpListDestination.qml" "JumpListSeparator.qml"
# QML_FILES = "JumpListLink.qml" "JumpListDestination.qml" "JumpListSeparator.qml"
# TARGETPATH = "QtWinExtras"

## Scopes:
#####################################################################

qt_extend_target(qml_winextras CONDITION QT_FEATURE_dynamicgl OR NOT TARGET Qt::OpenGL
    LIBRARIES
        user32
)

set(qml_files
    "JumpListLink.qml"
    "JumpListDestination.qml"
    "JumpListSeparator.qml"
)
set_source_files_properties(JumpListLink.qml PROPERTIES
    QT_QML_SOURCE_VERSION "1.0"
)
set_source_files_properties(JumpListDestination.qml PROPERTIES
    QT_QML_SOURCE_VERSION "1.0"
)
set_source_files_properties(JumpListSeparator.qml PROPERTIES
    QT_QML_SOURCE_VERSION "1.0"
)

qt6_target_qml_files(qml_winextras
    FILES
        ${qml_files}
)
