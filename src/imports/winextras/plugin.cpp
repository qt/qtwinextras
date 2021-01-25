/****************************************************************************
 **
 ** Copyright (C) 2016 Ivan Vizir <define-true-false@yandex.com>
 ** Copyright (C) 2021 The Qt Company Ltd.
 ** Contact: https://www.qt.io/licensing/
 **
 ** This file is part of the QtWinExtras module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:COMM$
 **
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and The Qt Company. For licensing terms
 ** and conditions see https://www.qt.io/terms-conditions. For further
 ** information use the contact form at https://www.qt.io/contact-us.
 **
 ** $QT_END_LICENSE$
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 **
 ****************************************************************************/

#include "qquickdwmfeatures_p.h"
#include "qquicktaskbarbutton_p.h"
#include "qquickjumplist_p.h"
#include "qquickjumplistitem_p.h"
#include "qquickjumplistcategory_p.h"
#include "qquickthumbnailtoolbar_p.h"
#include "qquickthumbnailtoolbutton_p.h"
#include "qquickwin_p.h"

#include <QtQml/qqmlextensionplugin.h>

QT_BEGIN_NAMESPACE

class QWinExtrasQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QWinExtrasQmlPlugin(QObject *parent = nullptr) : QQmlExtensionPlugin(parent) { }
    void registerTypes(const char *uri) Q_DECL_OVERRIDE
    {
        Q_ASSERT(uri == QLatin1String("QtWinExtras"));
        qmlRegisterModule(uri, 1, QT_VERSION_MINOR);
        qmlRegisterUncreatableType<QQuickWin>(uri, 1, 0, "QtWin", "Cannot create an instance of the QtWin namespace.");
        qmlRegisterType<QQuickDwmFeatures>(uri, 1, 0, "DwmFeatures");
        qmlRegisterType<QQuickTaskbarButton>(uri, 1, 0, "TaskbarButton");
        qmlRegisterUncreatableType<QWinTaskbarProgress>(uri, 1, 0, "TaskbarProgress", "Cannot create TaskbarProgress - use TaskbarButton.progress instead.");
        qmlRegisterUncreatableType<QQuickTaskbarOverlay>(uri, 1, 0, "TaskbarOverlay", "Cannot create TaskbarOverlay - use TaskbarButton.overlay instead.");
        qmlRegisterType<QQuickJumpList>(uri, 1, 0, "JumpList");
        qmlRegisterType<QQuickJumpListItem>(uri, 1, 0, "JumpListItem");
        qmlRegisterType<QQuickJumpListCategory>(uri, 1, 0, "JumpListCategory");
        qmlRegisterType<QQuickThumbnailToolBar>(uri, 1, 0, "ThumbnailToolBar");
        qmlRegisterType<QQuickThumbnailToolButton>(uri, 1, 0, "ThumbnailToolButton");
    }
};

QT_END_NAMESPACE

#include "plugin.moc"
