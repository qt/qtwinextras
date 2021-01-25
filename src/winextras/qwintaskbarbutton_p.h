/****************************************************************************
 **
 ** Copyright (C) 2016 Ivan Vizir <define-true-false@yandex.com>
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

#ifndef QWINTASKBARBUTTON_P_H
#define QWINTASKBARBUTTON_P_H

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

#include "qwintaskbarbutton.h"

#include <QtGui/qwindow.h>
#include <QtCore/qpointer.h>
#include <QtCore/qt_windows.h>

struct ITaskbarList4;

QT_BEGIN_NAMESPACE

class QWinTaskbarProgress;

class QWinTaskbarButtonPrivate
{
public:
    QWinTaskbarButtonPrivate();
    ~QWinTaskbarButtonPrivate();

    QPointer<QWinTaskbarProgress> progressBar;
    QIcon overlayIcon;
    QString overlayAccessibleDescription;

    HWND handle();
    int iconSize() const;

    void updateOverlayIcon();

    void _q_updateProgress();

    ITaskbarList4 *pTbList = nullptr;
    QWindow *window = nullptr;
};

QT_END_NAMESPACE

#endif // QWINTASKBARBUTTON_P_H
