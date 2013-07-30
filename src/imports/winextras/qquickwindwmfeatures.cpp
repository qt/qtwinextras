/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of QtWinExtras in the Qt Toolkit.
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

#include "qquickwindwmfeatures.h"
#include "qquickwindwmfeatures_p.h"

#include <QtWinExtras/private/qwineventfilter_p.h>
#include <QWinColorizationColorChangeEvent>
#include <QWinCompositionStateChangeEvent>
#include <QQuickWindow>

QT_BEGIN_NAMESPACE

/*!
    \qmltype WinDwmFeatures
    \instantiates QQuickWinDwmFeatures
    \inqmlmodule QtWinExtras

    \brief Enables you to extend a glass frame into the client area, as well as
    to control the behavior of Aero Peek and Flip3D.
 */

/*!
    \class QQuickWinDwmFeatures
    \internal
 */

QQuickWinDwmFeatures::QQuickWinDwmFeatures(QQuickItem *parent) :
    QQuickItem(parent), d_ptr(new QQuickWinDwmFeaturesPrivate(this))
{
    QWinEventFilter::setup();
}

QQuickWinDwmFeatures::~QQuickWinDwmFeatures()
{
}

void QQuickWinDwmFeatures::setCompositionEnabled(bool enabled)
{
    QWinExtras::setCompositionEnabled(enabled);
}

bool QQuickWinDwmFeatures::isCompositionEnabled() const
{
    return QWinExtras::isCompositionEnabled();
}

QColor QQuickWinDwmFeatures::colorizationColor() const
{
    return QWinExtras::colorizationColor();
}

QColor QQuickWinDwmFeatures::realColorizationColor() const
{
    return QWinExtras::realColorizationColor();
}

bool QQuickWinDwmFeatures::colorizationOpaqueBlend() const
{
    bool opaque;
    QWinExtras::colorizationColor(&opaque);
    return opaque;
}

/*!
    \qmlproperty int WinDwmFeatures::topGlassMargin

    The top glass frame margin. The default value is 0.
 */
void QQuickWinDwmFeatures::setTopGlassMargin(int margin)
{
    Q_D(QQuickWinDwmFeatures);
    d->topMargin = margin;
    d->update();
}

/*!
    \qmlproperty int WinDwmFeatures::rightGlassMargin

    The right glass frame margin. The default value is 0.
 */
void QQuickWinDwmFeatures::setRightGlassMargin(int margin)
{
    Q_D(QQuickWinDwmFeatures);
    d->rightMargin = margin;
    d->update();
}

/*!
    \qmlproperty int WinDwmFeatures::bottomGlassMargin

    The bottom glass frame margin. The default value is 0.
 */
void QQuickWinDwmFeatures::setBottomGlassMargin(int margin)
{
    Q_D(QQuickWinDwmFeatures);
    d->bottomMargin = margin;
    d->update();
}

/*!
    \qmlproperty int WinDwmFeatures::leftGlassMargin

    The left glass frame margin. The default value is 0.
 */
void QQuickWinDwmFeatures::setLeftGlassMargin(int margin)
{
    Q_D(QQuickWinDwmFeatures);
    d->leftMargin = margin;
    d->update();
}

int QQuickWinDwmFeatures::topGlassMargin() const
{
    Q_D(const QQuickWinDwmFeatures);
    return d->topMargin;
}

int QQuickWinDwmFeatures::rightGlassMargin() const
{
    Q_D(const QQuickWinDwmFeatures);
    return d->rightMargin;
}

int QQuickWinDwmFeatures::bottomGlassMargin() const
{
    Q_D(const QQuickWinDwmFeatures);
    return d->bottomMargin;
}

int QQuickWinDwmFeatures::leftGlassMargin() const
{
    Q_D(const QQuickWinDwmFeatures);
    return d->leftMargin;
}

/*!
    \qmlproperty bool WinDwmFeatures::excludedFromPeek

    Specifies whether the window is excluded from Aero Peek.
    The default value is false.
 */
bool QQuickWinDwmFeatures::excludedFromPeek() const
{
    Q_D(const QQuickWinDwmFeatures);
    if (window())
        return QWinExtras::isWindowExcludedFromPeek(window());
    else
        return d->peekExcluded;
}

void QQuickWinDwmFeatures::setExcludedFromPeek(bool exclude)
{
    Q_D(QQuickWinDwmFeatures);
    d->peekExcluded = exclude;
}

/*!
    \qmlproperty bool WinDwmFeatures::peekDisallowed

    Set this value to true if you want to forbid Aero Peek when the user hovers
    the mouse over the window thumbnail. The default value is false.
*/
bool QQuickWinDwmFeatures::peekDisallowed() const
{
    Q_D(const QQuickWinDwmFeatures);
    if (window())
        return QWinExtras::isWindowPeekDisallowed(window());
    else
        return d->peekDisallowed;
}

void QQuickWinDwmFeatures::setPeekDisallowed(bool disallow)
{
    Q_D(QQuickWinDwmFeatures);
    d->peekDisallowed = disallow;
}

/*!
    \enum QQuickWinDwmFeatures::Flip3DPolicy

    See QtWinExtras::WindowFlip3DPolicy.
 */

/*!
    \qmlproperty WinDwmFeatures::Flip3DPolicy WinDwmFeatures::flip3DPolicy

    The current Flip3D policy for the window.
 */
QQuickWinDwmFeatures::Flip3DPolicy QQuickWinDwmFeatures::flip3DPolicy() const
{
    Q_D(const QQuickWinDwmFeatures);
    if (window())
        return static_cast<Flip3DPolicy>(QWinExtras::windowFlip3DPolicy(window()));
    else
        return static_cast<Flip3DPolicy>(d->flipPolicy);
}

void QQuickWinDwmFeatures::setFlip3DPolicy(QQuickWinDwmFeatures::Flip3DPolicy policy)
{
    Q_D(QQuickWinDwmFeatures);
    d->flipPolicy = policy;
}

bool QQuickWinDwmFeatures::eventFilter(QObject *object, QEvent *event)
{
    bool filterOut = false;
    if (object == window()) {
        if (event->type() == QWinCompositionStateChangeEvent::eventType()) {
            emit isCompositionEnabledChanged();
            filterOut = true;
        } else if (event->type() == QWinColorizationColorChangeEvent::eventType()) {
            emit colorizationColorChanged();
            emit realColorizationColorChanged();
            emit colorizationOpaqueBlendChanged();
            filterOut = true;
        }
    }
    if (!filterOut)
        return QQuickItem::eventFilter(object, event);
    else
        return filterOut;
}

QQuickWinDwmFeatures *QQuickWinDwmFeatures::qmlAttachedProperties(QObject *parentObject)
{
    QQuickWinDwmFeatures *featuresObj = new QQuickWinDwmFeatures();
    QQuickItem *parentItem = qobject_cast<QQuickItem *>(parentObject);
    if (parentItem)
        featuresObj->setParentItem(parentItem);
    else
        featuresObj->setParent(parentObject);
    return featuresObj;
}

void QQuickWinDwmFeatures::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    Q_D(QQuickWinDwmFeatures);
    if (change == ItemSceneChange && data.window) {
        d->update();
        data.window->installEventFilter(this);
    }
    QQuickItem::itemChange(change, data);
}



QQuickWinDwmFeaturesPrivate::QQuickWinDwmFeaturesPrivate(QQuickWinDwmFeatures *parent) :
    topMargin(0), rightMargin(0), bottomMargin(0), leftMargin(0),
    peekDisallowed(false), peekExcluded(false), flipPolicy(QQuickWinDwmFeatures::FlipDefault),
    q_ptr(parent), formatSet(false), frameUpdateScheduled(false), attributesUpdateScheduled(false)
{
}

void QQuickWinDwmFeaturesPrivate::update()
{
    Q_Q(QQuickWinDwmFeatures);
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
            QWinExtras::setWindowExcludedFromPeek(w, peekExcluded);
        if (peekDisallowed)
            QWinExtras::setWindowDisallowPeek(w, peekDisallowed);
        if (flipPolicy != QQuickWinDwmFeatures::FlipDefault)
            QWinExtras::setWindowFlip3DPolicy(w, static_cast<QWinExtras::WindowFlip3DPolicy>(flipPolicy));
        if (topMargin || rightMargin || bottomMargin || leftMargin)
            QWinExtras::extendFrameIntoClientArea(w, leftMargin, topMargin, rightMargin, bottomMargin);
    }
}

QT_END_NAMESPACE
