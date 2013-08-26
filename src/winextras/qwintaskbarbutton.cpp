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

#include "qwintaskbarbutton.h"
#include "qwintaskbarbutton_p.h"
#include "qwinfunctions.h"
#include "qwineventfilter_p.h"
#include "qwinevent.h"

#include <QWindow>
#include <QIcon>
#include <QPair>
#include <dwmapi.h>
#include <shobjidl.h>

QT_BEGIN_NAMESPACE

/*!
    \class QWinTaskbarButton
    \inmodule QtWinExtras
    \brief The QWinTaskbarButton class represents the Windows taskbar button for
    a window.

    \since 5.2

    The QWinTaskbarButton class enables you to set overlay icons on a taskbar
    button, to display a progress indicator, and to add a small toolbar to the
    window thumbnail popup.
 */

/*!
    \enum QWinTaskbarButton::ProgressState

    This enum type specifies the state of the progress indicator.

    \value  NoProgressState
            No progress indicator is displayed.
    \value  IndeterminateState
            The progress indicator cycles repeatedly.
    \value  NormalState
            The progress indicator is green.
    \value PausedState
            The progress indicator turns yellow. Use this state to show that the
            operation has been paused, but it can be continued.
    \value  ErrorState
            The progress indicator turns red.
 */

/*!
    Constructs a QWinTaskbarButton with the parent object \a parent.
 */
QWinTaskbarButton::QWinTaskbarButton(QObject *parent) :
    QObject(parent), d_ptr(new QWinTaskbarButtonPrivate)
{
    Q_D(QWinTaskbarButton);
    d->q_ptr = this;
    QWinEventFilter::setup();
}

/*!
    Destroys the QWinTaskbarButton.
 */
QWinTaskbarButton::~QWinTaskbarButton()
{
}

/*!
    \property QWinTaskbarButton::window
    \brief the window whose taskbar button is manipulated
 */
void QWinTaskbarButton::setWindow(QWindow *window)
{
    Q_D(QWinTaskbarButton);
    if (d->window)
        d->window->removeEventFilter(this);
    d->window = window;
    if (d->window) {
        d->window->installEventFilter(this);
        if (d->window->isVisible()) {
            d->updateProgressValue();
            d->updateOverlayIcon();
        }
    }
}

QWindow *QWinTaskbarButton::window() const
{
    Q_D(const QWinTaskbarButton);
    return d->window;
}

/*!
    \property QWinTaskbarButton::overlayIcon
    \brief the overlay icon of the button
 */
QIcon QWinTaskbarButton::overlayIcon() const
{
    Q_D(const QWinTaskbarButton);
    return d->overlayIcon;
}

/*!
    \property QWinTaskbarButton::overlayIconAccessibilityDescription
    \brief the overlay icon accessibility description text
 */
QString QWinTaskbarButton::overlayIconAccessibilityDescription() const
{
    Q_D(const QWinTaskbarButton);
    return d->overlayIconDescription;
}

/*!
    \property QWinTaskbarButton::progressState
    \brief the progress state of the progress indicator
 */
QWinTaskbarButton::ProgressState QWinTaskbarButton::progressState() const
{
    Q_D(const QWinTaskbarButton);
    return d->progressState;
}

/*!
    \property QWinTaskbarButton::progressValue
    \brief the current progress value of the progress indicator
 */
int QWinTaskbarButton::progressValue() const
{
    Q_D(const QWinTaskbarButton);
    return d->progressValue;
}

/*!
    \property QWinTaskbarButton::progressMinimum
    \brief the minimum value of the progress indicator
 */
int QWinTaskbarButton::progressMinimum() const
{
    Q_D(const QWinTaskbarButton);
    return d->progressMinimum;
}

/*!
    \property QWinTaskbarButton::progressMaximum
    \brief the maximum value of the progress indicator
 */
int QWinTaskbarButton::progressMaximum() const
{
    Q_D(const QWinTaskbarButton);
    return d->progressMaximum;
}

/*!
    \internal
    Intercepts TaskbarButtonCreated messages.
 */
bool QWinTaskbarButton::eventFilter(QObject *object, QEvent *event)
{
    Q_D(QWinTaskbarButton);
    if (object == d->window && event->type() == QWinEvent::TaskbarButtonCreated) {
        d->pTbList->SetProgressState(d->handle(), QWinTaskbarButtonPrivate::nativeProgressState(d->progressState));
        d->updateProgressValue();
        d->updateOverlayIcon();
    }
    return false;
}

void QWinTaskbarButton::setOverlayIcon(const QIcon &icon)
{
    Q_D(QWinTaskbarButton);

    d->overlayIcon = icon;
    d->updateOverlayIcon();
}

void QWinTaskbarButton::setOverlayIconAccessibilityDescription(const QString &description)
{
    Q_D(QWinTaskbarButton);

    d->overlayIconDescription = description;
    d->updateOverlayIcon();
}

/*!
    Clears the previously set overlay icon.
    \sa QWinTaskbarButton::setOverlayIcon()
 */
void QWinTaskbarButton::clearOverlayIcon()
{
    setOverlayIconAccessibilityDescription(QString());
    setOverlayIcon(QIcon());
}

void QWinTaskbarButton::setProgressState(const QWinTaskbarButton::ProgressState state)
{
    Q_D(QWinTaskbarButton);

    if (state == d->progressState)
        return;

    d->progressState = state;
    emit progressStateChanged(d->progressState);

    if (!d->pTbList || !d->window)
        return;

    d->pTbList->SetProgressState(d->handle(), QWinTaskbarButtonPrivate::nativeProgressState(state));
    d->updateProgressValue();
}

void QWinTaskbarButton::setProgressValue(int value)
{
    Q_D(QWinTaskbarButton);

    if ((value == d->progressValue && !d->updateNeeded) || value < d->progressMinimum || value > d->progressMaximum)
        return;

    d->updateNeeded = false;

    d->progressValue = value;
    emit progressValueChanged(d->progressValue);
    d->updateProgressValue();
}

void QWinTaskbarButton::setProgressMinimum(int min)
{
    Q_D(QWinTaskbarButton);
    setProgressRange(min, qMax(min, d->progressMaximum));
}

void QWinTaskbarButton::setProgressMaximum(int max)
{
    Q_D(QWinTaskbarButton);
    setProgressRange(qMin(d->progressMinimum, max), max);
}

/*!
    Sets both the \a minimum and \a maximum values.
 */
void QWinTaskbarButton::setProgressRange(int minimum, int maximum)
{
    Q_D(QWinTaskbarButton);
    if (minimum != d->progressMinimum || maximum != d->progressMaximum) {
        d->progressMinimum = minimum;
        d->progressMaximum = qMax(minimum, maximum);

        if (d->progressValue < d->progressMinimum || d->progressValue > d->progressMaximum)
            resetProgress();
        else
            d->updateProgressValue();
    }
}

/*!
    Resets the progress indicator of this button.

    This function sets the progress state to \c NoProgressState and rewinds the
    progress value to the minimum value.
 */
void QWinTaskbarButton::resetProgress()
{
    setProgressValue(progressMinimum());
    setProgressState(NoProgressState);
}



QWinTaskbarButtonPrivate::QWinTaskbarButtonPrivate() :
    progressMinimum(0), progressMaximum(100), progressValue(0), progressState(QWinTaskbarButton::NoProgressState),
    updateNeeded(false), pTbList(0), window(0), q_ptr(0)
{
    HRESULT hresult = CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_INPROC_SERVER, IID_ITaskbarList4, reinterpret_cast<void **>(&pTbList));
    if (FAILED(hresult)) {
        pTbList = 0;
        const QString err = QWinExtras::errorStringFromHresult(hresult);
        qWarning("QWinTaskbarButton: IID_ITaskbarList4 was not created: %#010x, %s.", (unsigned)hresult, qPrintable(err));
    } else if (FAILED(pTbList->HrInit())) {
        pTbList->Release();
        pTbList = 0;
        const QString err = QWinExtras::errorStringFromHresult(hresult);
        qWarning("QWinTaskbarButton: IID_ITaskbarList4 was not initialized: %#010x, %s.", (unsigned)hresult, qPrintable(err));
    }
}

QWinTaskbarButtonPrivate::~QWinTaskbarButtonPrivate()
{
    pTbList->Release();
}

HWND QWinTaskbarButtonPrivate::handle()
{
    return reinterpret_cast<HWND>(window->winId());
}

int QWinTaskbarButtonPrivate::iconSize() const
{
    return GetSystemMetrics(SM_CXSMICON);
}

TBPFLAG QWinTaskbarButtonPrivate::nativeProgressState(QWinTaskbarButton::ProgressState state)
{
    TBPFLAG flag;
    switch (state) {
    default :
    case QWinTaskbarButton::NoProgressState :    flag = TBPF_NOPROGRESS; break;
    case QWinTaskbarButton::IndeterminateState : flag = TBPF_INDETERMINATE; break;
    case QWinTaskbarButton::NormalState :        flag = TBPF_NORMAL; break;
    case QWinTaskbarButton::PausedState :        flag = TBPF_PAUSED; break;
    case QWinTaskbarButton::ErrorState :         flag = TBPF_ERROR; break;
    }
    return flag;
}

void QWinTaskbarButtonPrivate::updateOverlayIcon()
{
    if (!pTbList || !window)
        return;

    wchar_t *descrPtr = 0;
    HICON hicon = 0;
    if (!overlayIconDescription.isEmpty()) {
        descrPtr = new wchar_t[overlayIconDescription.length() + 1];
        descrPtr[overlayIconDescription.toWCharArray(descrPtr)] = 0;
    }
    if (!overlayIcon.isNull())
        hicon = QWinExtras::toHICON(overlayIcon.pixmap(iconSize()));

    if (hicon)
        pTbList->SetOverlayIcon(handle(), hicon, descrPtr);
    else if (!hicon && !overlayIcon.isNull())
        pTbList->SetOverlayIcon(handle(), (HICON)LoadImage(0, IDI_APPLICATION, IMAGE_ICON, SM_CXSMICON, SM_CYSMICON, LR_SHARED), descrPtr);

    if (hicon)
        DeleteObject(hicon);
    if (descrPtr)
        delete[] descrPtr;
}

void QWinTaskbarButtonPrivate::updateProgressValue()
{
    if (!pTbList || !window || progressState == QWinTaskbarButton::NoProgressState || progressState == QWinTaskbarButton::IndeterminateState)
        return;

    Q_Q(QWinTaskbarButton);

    const int range = progressMaximum - progressMinimum;
    if (range > 0) {
        int value = 100.0 * (progressValue - progressMinimum)/(progressMaximum - progressMinimum);
        pTbList->SetProgressValue(handle(), value, 100);
        if (progressState == QWinTaskbarButton::IndeterminateState) {
            progressState = QWinTaskbarButton::NormalState;
            emit q->progressStateChanged(progressState);
        }
    }
}

/*!
    \fn void QWinTaskbarButton::progressStateChanged(const ProgressState state)

    This signal is emitted when the \c progressState property changes its value.
    The \a state argument contains the new value.
 */

/*!
    \fn void QWinTaskbarButton::progressValueChanged(int value)

    This signal is emitted when the progress indicator \a value changes.
 */

QT_END_NAMESPACE

#include "moc_qwintaskbarbutton.cpp"
