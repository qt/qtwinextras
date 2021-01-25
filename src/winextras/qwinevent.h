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

#ifndef QWINEVENT_H
#define QWINEVENT_H

#include <QtGui/qrgb.h>
#include <QtCore/qcoreevent.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class Q_WINEXTRAS_EXPORT QWinEvent : public QEvent
{
public:
    static const int ColorizationChange;
    static const int CompositionChange;
    static const int TaskbarButtonCreated;
    static const int ThemeChange;

    explicit QWinEvent(int type);
    ~QWinEvent();
};

class Q_WINEXTRAS_EXPORT QWinColorizationChangeEvent : public QWinEvent
{
public:
    QWinColorizationChangeEvent(QRgb color, bool opaque);
    ~QWinColorizationChangeEvent();

    inline QRgb color() const { return rgb; }
    inline bool opaqueBlend() const { return opaque; }

private:
    QRgb rgb;
    bool opaque;
};

class Q_WINEXTRAS_EXPORT QWinCompositionChangeEvent : public QWinEvent
{
public:
    explicit QWinCompositionChangeEvent(bool enabled);
    ~QWinCompositionChangeEvent();

    inline bool isCompositionEnabled() const { return enabled; }

private:
    bool enabled;
};

QT_END_NAMESPACE

#endif // QWINEVENT_H
