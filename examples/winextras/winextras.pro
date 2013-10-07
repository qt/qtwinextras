TEMPLATE = subdirs
win32 {
    SUBDIRS += \
        iconextractor
    qtHaveModule(widgets):qtHaveModule(multimedia): SUBDIRS += musicplayer
}
