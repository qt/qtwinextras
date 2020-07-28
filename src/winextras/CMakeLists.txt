# Generated from winextras.pro.

#####################################################################
## WinExtras Module:
#####################################################################

qt_add_module(WinExtras
    SOURCES
        qwinevent.cpp qwinevent.h
        qwineventfilter.cpp qwineventfilter_p.h
        qwinextrasglobal.h
        qwinfunctions.cpp qwinfunctions.h qwinfunctions_p.h
        qwinjumplist.cpp qwinjumplist.h qwinjumplist_p.h
        qwinjumplistcategory.cpp qwinjumplistcategory.h qwinjumplistcategory_p.h
        qwinjumplistitem.cpp qwinjumplistitem.h qwinjumplistitem_p.h
        qwinmime.cpp qwinmime.h
        qwintaskbarbutton.cpp qwintaskbarbutton.h qwintaskbarbutton_p.h
        qwintaskbarprogress.cpp qwintaskbarprogress.h
        qwinthumbnailtoolbar.cpp qwinthumbnailtoolbar.h qwinthumbnailtoolbar_p.h
        qwinthumbnailtoolbutton.cpp qwinthumbnailtoolbutton.h qwinthumbnailtoolbutton_p.h
        windowsguidsdefs.cpp windowsguidsdefs_p.h
        winpropkey_p.h
        winshobjidl_p.h
    LIBRARIES
        Qt::CorePrivate
        Qt::GuiPrivate
        dwmapi
        ole32
        shell32
        shlwapi
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
    PRIVATE_MODULE_INTERFACE
        Qt::CorePrivate
        Qt::GuiPrivate
)

#### Keys ignored in scope 1:.:.:winextras.pro:<TRUE>:
# OTHER_FILES = "doc/qtwinextras.qdocconf" "doc/src/qtwinextras-index.qdoc" "doc/src/qtwinextras-module-cpp.qdoc" "doc/src/qtwinextras-module-qml.qdoc" "doc/snippets/code/use-qtwinextras.pro" "doc/snippets/code/jumplist.cpp" "doc/snippets/code/use-qtwinextras.cpp" "doc/snippets/code/thumbbar.cpp" "doc/snippets/code/thumbbar.qml"

## Scopes:
#####################################################################

qt_extend_target(WinExtras CONDITION QT_FEATURE_dynamicgl OR (WIN32 AND NOT TARGET Qt::OpenGL)
    LIBRARIES
        gdi32
)
qt_add_docs(WinExtras
    doc/qtwinextras.qdocconf
)

