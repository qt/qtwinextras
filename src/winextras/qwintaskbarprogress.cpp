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
    \fn void QWinTaskbarProgress::stateChanged(ProgressState state)

    This signal is emitted when the \c state property changes its value.
    The \a state argument contains the new value.
 */

/*!
    \fn void QWinTaskbarProgress::valueChanged(int value)

    This signal is emitted when the progress indicator \a value changes.
 */

/*!
    \enum QWinTaskbarProgress::ProgressState

    This enum type specifies the state of the progress indicator.

    \value  NoProgressState
            No progress indicator is displayed.
    \value  NormalState
            The progress indicator is green.
    \value  PausedState
            The progress indicator turns yellow. Use this state to show that the
            operation has been paused, but it can be continued.
    \value  ErrorState
            The progress indicator turns red.
 */

class QWinTaskbarProgressPrivate
{
public:
    QWinTaskbarProgressPrivate();

    int value;
    int minimum;
    int maximum;
    QWinTaskbarProgress::ProgressState state;
};

QWinTaskbarProgressPrivate::QWinTaskbarProgressPrivate() :
    value(0), minimum(0), maximum(100), state(QWinTaskbarProgress::NoProgressState)
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
    \property QWinTaskbarProgress::state
    \brief the state of the progress indicator

    The default value is \c NoProgressState.
 */
QWinTaskbarProgress::ProgressState QWinTaskbarProgress::state() const
{
    Q_D(const QWinTaskbarProgress);
    return d->state;
}

void QWinTaskbarProgress::setState(QWinTaskbarProgress::ProgressState state)
{
    Q_D(QWinTaskbarProgress);
    if (state == d->state)
        return;

    d->state = state;
    emit stateChanged(d->state);
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
    Sets both the \a minimum and \a maximum values.
 */
void QWinTaskbarProgress::setRange(int minimum, int maximum)
{
    Q_D(QWinTaskbarProgress);
    if (minimum != d->minimum || maximum != d->maximum) {
        d->minimum = minimum;
        d->maximum = qMax(minimum, maximum);

        if (d->value < d->minimum || d->value > d->maximum)
            reset();
    }
}

/*!
    Resets the progress indicator.

    This function sets the state to \c NoProgressState and rewinds the
    value to the minimum value.
 */
void QWinTaskbarProgress::reset()
{
    setValue(minimum());
    setState(NoProgressState);
}

QT_END_NAMESPACE
