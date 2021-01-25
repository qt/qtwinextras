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

#ifndef QQUICKWIN_P_H
#define QQUICKWIN_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QObject>
#include <QtWin>

QT_BEGIN_NAMESPACE

class QQuickWin : public QObject
{
    Q_OBJECT

public:
    enum HBitmapFormat
    {
        HBitmapNoAlpha = QtWin::HBitmapNoAlpha,
        HBitmapPremultipliedAlpha = QtWin::HBitmapPremultipliedAlpha,
        HBitmapAlpha = QtWin::HBitmapAlpha
    };
    Q_ENUM(HBitmapFormat)

    enum WindowFlip3DPolicy
    {
        FlipDefault = QtWin::FlipDefault,
        FlipExcludeBelow = QtWin::FlipExcludeBelow,
        FlipExcludeAbove = QtWin::FlipExcludeAbove
    };
    Q_ENUM(WindowFlip3DPolicy)
};

QT_END_NAMESPACE

#endif // QQUICKWIN_P_H
