TEMPLATE = subdirs
win32:{
    SUBDIRS += \
        iconextractor \
        dwmfeatures \
        jumplistexample
    EXAMPLE_FILES += quickdwm

    qtHaveModule(widgets):qtHaveModule(multimedia): SUBDIRS += musicplayer
}
