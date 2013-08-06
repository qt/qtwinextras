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

#include "qwinthumbnailtoolbutton.h"
#include "qwinthumbnailtoolbutton_p.h"

QT_BEGIN_NAMESPACE

/*!
    \class QWinThumbnailToolButton
    \inmodule QtWinExtras
    \since 5.2
    \brief The QWinThumbnailToolButton class represents a button in the window's thumbnail toolbar.
 */

/*!
    \fn void QWinThumbnailToolButton::clicked()

    This signal is emitted when the button is clicked.
 */

/*!
    \internal
    \fn void QWinThumbnailToolButton::changed()
 */

/*!
    Constructs a QWinThumbnailToolButton with the specified \a parent.
 */
QWinThumbnailToolButton::QWinThumbnailToolButton(QObject *parent) :
    QObject(parent), d_ptr(new QWinThumbnailToolButtonPrivate)
{
}

/*!
    Destroys the QWinThumbnailToolButton.
 */
QWinThumbnailToolButton::~QWinThumbnailToolButton()
{
}

/*!
    \property QWinThumbnailToolButton::toolTip
    \brief the tooltip of the button
 */
void QWinThumbnailToolButton::setToolTip(const QString &toolTip)
{
    Q_D(QWinThumbnailToolButton);
    if (d->toolTip != toolTip) {
        d->toolTip = toolTip;
        emit changed();
    }
}

QString QWinThumbnailToolButton::toolTip() const
{
    Q_D(const QWinThumbnailToolButton);
    return d->toolTip;
}

/*!
    \property QWinThumbnailToolButton::icon
    \brief the icon of the button
 */
void QWinThumbnailToolButton::setIcon(const QIcon &icon)
{
    Q_D(QWinThumbnailToolButton);
    if (d->icon.cacheKey() != icon.cacheKey()) {
        d->icon = icon;
        emit changed();
    }
}

QIcon QWinThumbnailToolButton::icon() const
{
    Q_D(const QWinThumbnailToolButton);
    return d->icon;
}

/*!
    \property QWinThumbnailToolButton::enabled
    \brief whether the button is enabled

    This property's default is true.
 */
void QWinThumbnailToolButton::setEnabled(bool enabled)
{
    Q_D(QWinThumbnailToolButton);
    if (d->enabled != enabled) {
        d->enabled = enabled;
        emit changed();
    }
}

bool QWinThumbnailToolButton::isEnabled() const
{
    Q_D(const QWinThumbnailToolButton);
    return d->enabled;
}

/*!
    \property QWinThumbnailToolButton::interactive
    \brief whether the button is interactive

    This property's default is true.

    If not interactive, the button remains enabled, but no pressed or mouse-over
    states are drawn. Set this property to false to use this button as a
    notification icon.
 */
void QWinThumbnailToolButton::setInteractive(bool interactive)
{
    Q_D(QWinThumbnailToolButton);
    if (d->interactive != interactive) {
        d->interactive = interactive;
        emit changed();
    }
}

bool QWinThumbnailToolButton::isInteractive() const
{
    Q_D(const QWinThumbnailToolButton);
    return d->interactive;
}

/*!
    \property QWinThumbnailToolButton::visible
    \brief whether the button is visible

    This property's default is true.
 */
void QWinThumbnailToolButton::setVisible(bool visible)
{
    Q_D(QWinThumbnailToolButton);
    if (d->visible != visible) {
        d->visible = visible;
        emit changed();
    }
}

bool QWinThumbnailToolButton::isVisible() const
{
    Q_D(const QWinThumbnailToolButton);
    return d->visible;
}

/*!
    \property QWinThumbnailToolButton::dismissOnClick
    \brief whether the window thumbnail is dismissed after a button click

    This property's default is false.
 */
void QWinThumbnailToolButton::setDismissOnClick(bool dismiss)
{
    Q_D(QWinThumbnailToolButton);
    if (d->dismiss != dismiss) {
        d->dismiss = dismiss;
        emit changed();
    }
}

bool QWinThumbnailToolButton::dismissOnClick() const
{
    Q_D(const QWinThumbnailToolButton);
    return d->dismiss;
}

/*!
    \property QWinThumbnailToolButton::flat
    \brief whether the button background and frame are not drawn

    This property's default is false.
 */
void QWinThumbnailToolButton::setFlat(bool flat)
{
    Q_D(QWinThumbnailToolButton);
    if (d->flat != flat) {
        d->flat = flat;
        emit changed();
    }
}

bool QWinThumbnailToolButton::isFlat() const
{
    Q_D(const QWinThumbnailToolButton);
    return d->flat;
}

/*!
    Performs a click. The clicked() signal is emitted as appropriate.

    Does nothing if the button is disabled or non-interactive.
 */
void QWinThumbnailToolButton::click()
{
    Q_D(QWinThumbnailToolButton);
    if (d->enabled && d->interactive)
        emit clicked();
}

QT_END_NAMESPACE
