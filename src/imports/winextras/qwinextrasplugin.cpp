/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the QtWinExtras module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Digia.  For licensing terms and
 ** conditions see http://qt.digia.com/licensing.  For further information
 ** use the contact form at http://qt.digia.com/contact-us.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Digia gives you certain additional
 ** rights.  These rights are described in the Digia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "qwinextrasplugin.h"
#include "qquickwindwmfeatures.h"
#include "qquickwintaskbarbutton.h"
#include "qquickjumplist.h"
#include "qquickwinthumbnailtoolbar.h"
#include "qquickwinthumbnailtoolbutton.h"

#include <QtQml/QtQml>

QT_BEGIN_NAMESPACE

QWinExtrasQmlPlugin::QWinExtrasQmlPlugin(QObject *parent) :
    QQmlExtensionPlugin(parent)
{
}

void QWinExtrasQmlPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("QtWinExtras"));
    qmlRegisterType<QQuickWinDwmFeatures>(uri, 1, 0, "WinDwmFeatures");
    qmlRegisterType<QQuickWinTaskbarButton>(uri, 1, 0, "WinTaskbarButton");
    qmlRegisterUncreatableType<QWinTaskbarProgress>(uri, 1, 0, "WinTaskbarProgress", "Cannot create WinTaskbarProgress - use WinTaskbarButton.progress instead.");
    qmlRegisterType<QQuickJumpList>(uri, 1, 0, "JumpList");
    qmlRegisterType<QQuickJumpListItem>(uri, 1, 0, "JumpListItem");
    qmlRegisterType<QQuickJumpListCategory>(uri, 1, 0, "JumpListCategory");
    qmlRegisterType<QQuickWinThumbnailToolBar>(uri, 1, 0, "ThumbnailToolBar");
    qmlRegisterType<QQuickWinThumbnailToolButton>(uri, 1, 0, "ThumbnailToolButton");
}

QT_END_NAMESPACE
