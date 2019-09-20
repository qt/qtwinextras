# Generated from dwmfeatures.pro.

#####################################################################
## dwmfeatures Binary:
#####################################################################

add_qt_executable(dwmfeatures
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
