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

#include "qwinevent.h"

const int QWinEvent::ColorizationChange = QEvent::registerEventType();
const int QWinEvent::CompositionChange = QEvent::registerEventType();
const int QWinEvent::TaskbarButtonCreated = QEvent::registerEventType();
const int QWinEvent::ThemeChange = QEvent::registerEventType();

QWinEvent::QWinEvent(int type) : QEvent(static_cast<QEvent::Type>(type))
{
}

QWinEvent::~QWinEvent() = default;

QWinColorizationChangeEvent::QWinColorizationChangeEvent(QRgb color, bool opaque)
    : QWinEvent(ColorizationChange), rgb(color), opaque(opaque)
{
}

QWinColorizationChangeEvent::~QWinColorizationChangeEvent() = default;

QWinCompositionChangeEvent::QWinCompositionChangeEvent(bool enabled)
    : QWinEvent(CompositionChange), enabled(enabled)
{
}

QWinCompositionChangeEvent::~QWinCompositionChangeEvent() = default;
