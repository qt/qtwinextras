# Generated from dwmfeatures.pro.

#####################################################################
## dwmfeatures Binary:
#####################################################################

qt_add_manual_test(dwmfeatures
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

#### Keys ignored in scope 1:.:.:dwmfeatures.pro:<TRUE>:
# TEMPLATE = "app"
