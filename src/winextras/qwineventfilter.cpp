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

#include "qwineventfilter_p.h"
#include "qwinfunctions.h"
#include "qwinevent.h"
#include <QtGui/qguiapplication.h>
#include <QtGui/qwindow.h>

#ifndef WM_DWMCOLORIZATIONCOLORCHANGED
#   define WM_DWMCOLORIZATIONCOLORCHANGED 0x0320
#endif

#ifndef WM_DWMCOMPOSITIONCHANGED
#   define WM_DWMCOMPOSITIONCHANGED       0x031E
#endif

QWinEventFilter *QWinEventFilter::instance = nullptr;

QWinEventFilter::QWinEventFilter() :
    tbButtonCreatedMsgId(RegisterWindowMessageW(L"TaskbarButtonCreated"))
{
}

QWinEventFilter::~QWinEventFilter()
{
    instance = nullptr;
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool QWinEventFilter::nativeEventFilter(const QByteArray &, void *message, qintptr *result)
#else
bool QWinEventFilter::nativeEventFilter(const QByteArray &, void *message, long *result)
#endif
{
    MSG *msg = static_cast<MSG *>(message);
    bool filterOut = false;

    QEvent *event = nullptr;
    QWindow *window = nullptr;
    switch (msg->message) {
    case WM_DWMCOLORIZATIONCOLORCHANGED :
        event = new QWinColorizationChangeEvent(QRgb(msg->wParam), msg->lParam);
        break;
    case WM_DWMCOMPOSITIONCHANGED :
        event = new QWinCompositionChangeEvent(QtWin::isCompositionEnabled());
        break;
    case WM_THEMECHANGED :
        event = new QWinEvent(QWinEvent::ThemeChange);
        break;
    default :
        if (tbButtonCreatedMsgId == msg->message) {
            event = new QWinEvent(QWinEvent::TaskbarButtonCreated);
            filterOut = true;
        }
        break;
    }

    if (event) {
        window = findWindow(msg->hwnd);
        if (window)
            QCoreApplication::sendEvent(window, event);
        delete event;
    }

    if (filterOut && result) {
        *result = 0;
    }

    return filterOut;
}

void QWinEventFilter::setup()
{
    if (!instance) {
        instance = new QWinEventFilter;
        qApp->installNativeEventFilter(instance);
    }
}

QWindow *QWinEventFilter::findWindow(HWND handle)
{
    const WId wid = reinterpret_cast<WId>(handle);
    const auto topLevels = QGuiApplication::topLevelWindows();
    for (QWindow *topLevel : topLevels) {
        if (topLevel->handle() && topLevel->winId() == wid)
            return topLevel;
    }
    return nullptr;
}
