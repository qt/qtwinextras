# Generated from jumplist.pro.

#####################################################################
## jumplist Binary:
#####################################################################

qt_add_manual_test(jumplist # special case
    GUI
    SOURCES
        main.cpp
        testwidget.cpp testwidget.h testwidget.ui
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Widgets
        Qt::WinExtras
    ENABLE_AUTOGEN_TOOLS
        uic
)

#### Keys ignored in scope 1:.:.:jumplist.pro:<TRUE>:
# TEMPLATE = "app"
