/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
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

#include "qquicktaskbarbutton_p.h"
#include <QtWinExtras/private/qwintaskbarbutton_p.h>
#include <QQuickWindow>

QT_BEGIN_NAMESPACE

/*!
    \qmltype TaskbarButton
    \instantiates QQuickTaskbarButton
    \inqmlmodule QtWinExtras

    \brief Manages Windows taskbar buttons.

    \since QtWinExtras 1.0

    The TaskbarButton type enables you to set overlay icons on a taskbar
    button, to display a progress indicator, and to add a small toolbar to the
    window thumbnail popup.

    \sa QWinTaskbarButton
 */

/*!
    \class QQuickTaskbarButton
    \internal
 */

QQuickTaskbarButton::QQuickTaskbarButton(QQuickItem *parent) :
    QQuickItem(parent), button(new QWinTaskbarButton(this))
{
}

QQuickTaskbarButton::~QQuickTaskbarButton()
{
}

/*!
    \qmlproperty string TaskbarButton::progress

    The task bar progress indicator.
 */
QWinTaskbarProgress *QQuickTaskbarButton::progress() const
{
    return button->progress();
}

/*!
    \qmlproperty string TaskbarButton::icon

    The overlay icon path.
 */
QString QQuickTaskbarButton::overlayIcon() const
{
    return m_iconPath;
}

void QQuickTaskbarButton::setOverlayIcon(const QString &path)
{
    m_iconPath = path;
    button->setOverlayIcon(QIcon(m_iconPath));
}

/*!
    \qmlproperty string TaskbarButton::overlayAccessibleDescription

    The description of the overlay for accessibility purposes.
 */
QString QQuickTaskbarButton::overlayAccessibleDescription() const
{
    return button->overlayAccessibleDescription();
}

void QQuickTaskbarButton::setOverlayAccessibleDescription(const QString &description)
{
    button->setOverlayAccessibleDescription(description);
}

void QQuickTaskbarButton::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    if (change == ItemSceneChange) {
        button->setWindow(data.window);
    }
    QQuickItem::itemChange(change, data);
}

QT_END_NAMESPACE
