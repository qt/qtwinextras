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

#ifndef QQUICKDWMFEATURES_P_P_H
#define QQUICKDWMFEATURES_P_P_H

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

#include "qquickdwmfeatures_p.h"

QT_BEGIN_NAMESPACE

class QQuickDwmFeaturesPrivate
{
public:
    QQuickDwmFeaturesPrivate(QQuickDwmFeatures *parent);

    int topMargin = 0;
    int rightMargin = 0;
    int bottomMargin = 0;
    int leftMargin = 0;
    bool blurBehindEnabled = false;

    bool peekDisallowed = false;
    bool peekExcluded = false;
    QQuickWin::WindowFlip3DPolicy flipPolicy = QQuickWin::FlipDefault;
    QColor originalSurfaceColor;

    void updateAll();
    void updateSurfaceFormat();

private:
    QQuickDwmFeatures *q_ptr;

    Q_DECLARE_PUBLIC(QQuickDwmFeatures)
};

QT_END_NAMESPACE

#endif // QQUICKDWMFEATURES_P_P_H
