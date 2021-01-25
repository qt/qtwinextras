/****************************************************************************
 **
 ** Copyright (C) 2021 Ivan Vizir <define-true-false@yandex.com>
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

#ifndef QWINTASKBARPROGRESS_H
#define QWINTASKBARPROGRESS_H

#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QWinTaskbarProgressPrivate;

class Q_WINEXTRAS_EXPORT QWinTaskbarProgress : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibilityChanged)
    Q_PROPERTY(bool paused READ isPaused WRITE setPaused NOTIFY pausedChanged)
    Q_PROPERTY(bool stopped READ isStopped NOTIFY stoppedChanged)

public:
    explicit QWinTaskbarProgress(QObject *parent = nullptr);
    ~QWinTaskbarProgress();

    int value() const;
    int minimum() const;
    int maximum() const;
    bool isVisible() const;
    bool isPaused() const;
    bool isStopped() const;

public Q_SLOTS:
    void setValue(int value);
    void setMinimum(int minimum);
    void setMaximum(int maximum);
    void setRange(int minimum, int maximum);
    void reset();
    void show();
    void hide();
    void setVisible(bool visible);
    void pause();
    void resume();
    void setPaused(bool paused);
    void stop();

Q_SIGNALS:
    void valueChanged(int value);
    void minimumChanged(int minimum);
    void maximumChanged(int maximum);
    void visibilityChanged(bool visible);
    void pausedChanged(bool paused);
    void stoppedChanged(bool stopped);

private:
    Q_DISABLE_COPY(QWinTaskbarProgress)
    Q_DECLARE_PRIVATE(QWinTaskbarProgress)
    QScopedPointer<QWinTaskbarProgressPrivate> d_ptr;
};

QT_END_NAMESPACE

#endif // QWINTASKBARPROGRESS_H
