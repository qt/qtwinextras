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

#include "qwintaskbarprogress.h"

QT_BEGIN_NAMESPACE

/*!
    \class QWinTaskbarProgress
    \inmodule QtWinExtras
    \brief The QWinTaskbarProgress class represents the Windows taskbar progress indicator.

    \since 5.2

    The QWinTaskbarProgress class enables you to to display a progress indicator
    on a taskbar button.
 */

/*!
    \fn void QWinTaskbarProgress::valueChanged(int value)

    This signal is emitted when the progress indicator \a value changes.
 */

/*!
    \fn void QWinTaskbarProgress::stoppedChanged(bool stopped)
    \internal (for QWinTaskbarButton and QML compatibility)
 */

class QWinTaskbarProgressPrivate
{
public:
    QWinTaskbarProgressPrivate();

    int value;
    int minimum;
    int maximum;
    bool visible;
    bool paused;
    bool stopped;
};

QWinTaskbarProgressPrivate::QWinTaskbarProgressPrivate() :
    value(0), minimum(0), maximum(100), visible(false), paused(false), stopped(false)
{
}

/*!
    Constructs a QWinTaskbarProgress with the parent object \a parent.
 */
QWinTaskbarProgress::QWinTaskbarProgress(QObject *parent) :
    QObject(parent), d_ptr(new QWinTaskbarProgressPrivate)
{
}

/*!
    Destroys the QWinTaskbarProgress.
 */
QWinTaskbarProgress::~QWinTaskbarProgress()
{
}

/*!
    \property QWinTaskbarProgress::value
    \brief the current value of the progress indicator

    The default value is \c 0.
 */
int QWinTaskbarProgress::value() const
{
    Q_D(const QWinTaskbarProgress);
    return d->value;
}

void QWinTaskbarProgress::setValue(int value)
{
    Q_D(QWinTaskbarProgress);
    if ((value == d->value) || value < d->minimum || value > d->maximum)
        return;

    d->value = value;
    emit valueChanged(d->value);
}

/*!
    \property QWinTaskbarProgress::minimum
    \brief the minimum value of the progress indicator

    The default value is \c 0.
 */
int QWinTaskbarProgress::minimum() const
{
    Q_D(const QWinTaskbarProgress);
    return d->minimum;
}

void QWinTaskbarProgress::setMinimum(int minimum)
{
    Q_D(QWinTaskbarProgress);
    setRange(minimum, qMax(minimum, d->maximum));
}

/*!
    \property QWinTaskbarProgress::maximum
    \brief the maximum value of the progress indicator

    The default value is \c 100.
 */
int QWinTaskbarProgress::maximum() const
{
    Q_D(const QWinTaskbarProgress);
    return d->maximum;
}

void QWinTaskbarProgress::setMaximum(int maximum)
{
    Q_D(QWinTaskbarProgress);
    setRange(qMin(d->minimum, maximum), maximum);
}

/*!
    \property QWinTaskbarProgress::visible
    \brief the progress indicator is visible.

    The default value is \c false.
 */
bool QWinTaskbarProgress::isVisible() const
{
    Q_D(const QWinTaskbarProgress);
    return d->visible;
}

void QWinTaskbarProgress::setVisible(bool visible)
{
    Q_D(QWinTaskbarProgress);
    if (visible == d->visible)
        return;

    d->visible = visible;
    emit visibilityChanged(d->visible);
}

/*!
    Shows the progress indicator.
 */
void QWinTaskbarProgress::show()
{
    setVisible(true);
}

/*!
    Hides the progress indicator.
 */
void QWinTaskbarProgress::hide()
{
    setVisible(false);
}

/*!
    Sets both the \a minimum and \a maximum values.
 */
void QWinTaskbarProgress::setRange(int minimum, int maximum)
{
    Q_D(QWinTaskbarProgress);
    const bool minChanged = minimum != d->minimum;
    const bool maxChanged = maximum != d->maximum;
    if (minChanged || maxChanged) {
        d->minimum = minimum;
        d->maximum = qMax(minimum, maximum);

        if (d->value < d->minimum || d->value > d->maximum)
            reset();

        if (minChanged)
            emit minimumChanged(d->minimum);
        if (maxChanged)
            emit maximumChanged(d->maximum);
    }
}

/*!
    Resets the progress indicator.

    This function rewinds the value to the minimum value.
 */
void QWinTaskbarProgress::reset()
{
    setValue(minimum());
}

/*!
    \property QWinTaskbarProgress::paused
    \brief the progress indicator is paused.

    The default value is \c false.
 */
bool QWinTaskbarProgress::isPaused() const
{
    Q_D(const QWinTaskbarProgress);
    return d->paused;
}

void QWinTaskbarProgress::setPaused(bool paused)
{
    Q_D(QWinTaskbarProgress);
    if (paused == d->paused || d->stopped)
        return;

    d->paused = paused;
    emit pausedChanged(d->paused);
}

/*!
    Pause the progress indicator.
 */
void QWinTaskbarProgress::pause()
{
    setPaused(true);
}

/*!
    Resume a paused or stopped progress indicator.
 */
void QWinTaskbarProgress::resume()
{
    Q_D(QWinTaskbarProgress);
    setPaused(false);
    if (d->stopped) {
        d->stopped = false;
        emit stoppedChanged(false);
    }
}

/*!
    \property QWinTaskbarProgress::stopped
    \brief the progress indicator is stopped.

    The default value is \c false.
 */
bool QWinTaskbarProgress::isStopped() const
{
    Q_D(const QWinTaskbarProgress);
    return d->stopped;
}

/*!
    Stop the progress indicator.
 */
void QWinTaskbarProgress::stop()
{
    Q_D(QWinTaskbarProgress);
    setPaused(false);
    if (!d->stopped) {
        d->stopped = true;
        emit stoppedChanged(true);
    }
}

QT_END_NAMESPACE
