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

#include "qquickdwmfeatures_p.h"
#include "qquickdwmfeatures_p_p.h"

#include <QtWinExtras/private/qwineventfilter_p.h>
#include <QWinEvent>
#include <QQuickWindow>

QT_BEGIN_NAMESPACE

/*!
    \qmltype DwmFeatures
    \instantiates QQuickDwmFeatures
    \inqmlmodule QtWinExtras

    \brief Enables you to manage the Windows DWM features.

    \since QtWinExtras 1.0

    The DwmFeatures type enables you to extend a glass frame into the client
    area, as well as to control the behavior of Aero Peek and Flip3D.
 */

/*!
    \class QQuickDwmFeatures
    \internal
 */

QQuickDwmFeatures::QQuickDwmFeatures(QQuickItem *parent) :
    QQuickItem(parent), d_ptr(new QQuickDwmFeaturesPrivate(this))
{
    QWinEventFilter::setup();
}

QQuickDwmFeatures::~QQuickDwmFeatures()
{
}

void QQuickDwmFeatures::setCompositionEnabled(bool enabled)
{
    QtWin::setCompositionEnabled(enabled);
}

bool QQuickDwmFeatures::isCompositionEnabled() const
{
    return QtWin::isCompositionEnabled();
}

QColor QQuickDwmFeatures::colorizationColor() const
{
    return QtWin::colorizationColor();
}

QColor QQuickDwmFeatures::realColorizationColor() const
{
    return QtWin::realColorizationColor();
}

bool QQuickDwmFeatures::colorizationOpaqueBlend() const
{
    bool opaque;
    QtWin::colorizationColor(&opaque);
    return opaque;
}

/*!
    \qmlproperty int DwmFeatures::topGlassMargin

    The top glass frame margin. The default value is 0.
 */
void QQuickDwmFeatures::setTopGlassMargin(int margin)
{
    Q_D(QQuickDwmFeatures);
    if (d->topMargin == margin)
        return;

    d->topMargin = margin;
    d->update();
    emit topGlassMarginChanged();
}

/*!
    \qmlproperty int DwmFeatures::rightGlassMargin

    The right glass frame margin. The default value is 0.
 */
void QQuickDwmFeatures::setRightGlassMargin(int margin)
{
    Q_D(QQuickDwmFeatures);
    if (d->rightMargin == margin)
        return;

    d->rightMargin = margin;
    d->update();
    emit rightGlassMarginChanged();
}

/*!
    \qmlproperty int DwmFeatures::bottomGlassMargin

    The bottom glass frame margin. The default value is 0.
 */
void QQuickDwmFeatures::setBottomGlassMargin(int margin)
{
    Q_D(QQuickDwmFeatures);
    if (d->bottomMargin == margin)
        return;

    d->bottomMargin = margin;
    d->update();
    emit rightGlassMarginChanged();
}

/*!
    \qmlproperty int DwmFeatures::leftGlassMargin

    The left glass frame margin. The default value is 0.
 */
void QQuickDwmFeatures::setLeftGlassMargin(int margin)
{
    Q_D(QQuickDwmFeatures);
    if (d->leftMargin == margin)
        return;

    d->leftMargin = margin;
    d->update();
    emit leftGlassMarginChanged();
}

int QQuickDwmFeatures::topGlassMargin() const
{
    Q_D(const QQuickDwmFeatures);
    return d->topMargin;
}

int QQuickDwmFeatures::rightGlassMargin() const
{
    Q_D(const QQuickDwmFeatures);
    return d->rightMargin;
}

int QQuickDwmFeatures::bottomGlassMargin() const
{
    Q_D(const QQuickDwmFeatures);
    return d->bottomMargin;
}

int QQuickDwmFeatures::leftGlassMargin() const
{
    Q_D(const QQuickDwmFeatures);
    return d->leftMargin;
}

/*!
    \qmlproperty bool DwmFeatures::excludedFromPeek

    Specifies whether the window is excluded from Aero Peek.
    The default value is false.
 */
bool QQuickDwmFeatures::isExcludedFromPeek() const
{
    Q_D(const QQuickDwmFeatures);
    if (window())
        return QtWin::isWindowExcludedFromPeek(window());
    else
        return d->peekExcluded;
}

void QQuickDwmFeatures::setExcludedFromPeek(bool exclude)
{
    Q_D(QQuickDwmFeatures);
    if (d->peekExcluded == exclude)
        return;

    d->peekExcluded = exclude;
    d->update();
    emit excludedFromPeekChanged();
}

/*!
    \qmlproperty bool DwmFeatures::peekDisallowed

    Set this value to true if you want to forbid Aero Peek when the user hovers
    the mouse over the window thumbnail. The default value is false.
*/
bool QQuickDwmFeatures::isPeekDisallowed() const
{
    Q_D(const QQuickDwmFeatures);
    if (window())
        return QtWin::isWindowPeekDisallowed(window());
    else
        return d->peekDisallowed;
}

void QQuickDwmFeatures::setPeekDisallowed(bool disallow)
{
    Q_D(QQuickDwmFeatures);
    if (d->peekDisallowed == disallow)
        return;

    d->peekDisallowed = disallow;
    d->update();
    emit peekDisallowedChanged();
}

/*!
    \qmlproperty QtWin::WindowFlip3DPolicy DwmFeatures::flip3DPolicy

    The current Flip3D policy for the window.
 */
QQuickWin::WindowFlip3DPolicy QQuickDwmFeatures::flip3DPolicy() const
{
    Q_D(const QQuickDwmFeatures);
    if (window())
        return static_cast<QQuickWin::WindowFlip3DPolicy>(QtWin::windowFlip3DPolicy(window()));
    else
        return d->flipPolicy;
}

void QQuickDwmFeatures::setFlip3DPolicy(QQuickWin::WindowFlip3DPolicy policy)
{
    Q_D(QQuickDwmFeatures);
    if (d->flipPolicy == policy)
        return;

    d->flipPolicy = policy;
    d->update();
    emit flip3DPolicyChanged();
}

bool QQuickDwmFeatures::eventFilter(QObject *object, QEvent *event)
{
    if (object == window()) {
        if (event->type() == QWinEvent::CompositionChange) {
            emit compositionEnabledChanged();
        } else if (event->type() == QWinEvent::ColorizationChange) {
            emit colorizationColorChanged();
            emit realColorizationColorChanged();
            emit colorizationOpaqueBlendChanged();
        }
    }
    return QQuickItem::eventFilter(object, event);
}

QQuickDwmFeatures *QQuickDwmFeatures::qmlAttachedProperties(QObject *parentObject)
{
    QQuickDwmFeatures *featuresObj = new QQuickDwmFeatures();
    QQuickItem *parentItem = qobject_cast<QQuickItem *>(parentObject);
    if (parentItem)
        featuresObj->setParentItem(parentItem);
    else
        featuresObj->setParent(parentObject);
    return featuresObj;
}

void QQuickDwmFeatures::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    Q_D(QQuickDwmFeatures);
    if (change == ItemSceneChange && data.window) {
        d->update();
        data.window->installEventFilter(this);
    }
    QQuickItem::itemChange(change, data);
}



QQuickDwmFeaturesPrivate::QQuickDwmFeaturesPrivate(QQuickDwmFeatures *parent) :
    topMargin(0), rightMargin(0), bottomMargin(0), leftMargin(0),
    peekDisallowed(false), peekExcluded(false), flipPolicy(QQuickWin::FlipDefault),
    q_ptr(parent), formatSet(false)
{
}

void QQuickDwmFeaturesPrivate::update()
{
    Q_Q(QQuickDwmFeatures);
    QWindow *w = q->window();
    if (w) {
        if (!formatSet) {
            formatSet = true;
            QSurfaceFormat format = w->format();
            format.setAlphaBufferSize(8);
            w->setFormat(format);
            q->window()->setColor(Qt::transparent);
        }
        if (peekExcluded)
            QtWin::setWindowExcludedFromPeek(w, peekExcluded);
        if (peekDisallowed)
            QtWin::setWindowDisallowPeek(w, peekDisallowed);
        if (flipPolicy != QQuickWin::FlipDefault)
            QtWin::setWindowFlip3DPolicy(w, static_cast<QtWin::WindowFlip3DPolicy>(flipPolicy));
        if (topMargin || rightMargin || bottomMargin || leftMargin)
            QtWin::extendFrameIntoClientArea(w, leftMargin, topMargin, rightMargin, bottomMargin);
    }
}

QT_END_NAMESPACE
