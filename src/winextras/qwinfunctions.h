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

#ifndef QWINFUNCTIONS_H
#define QWINFUNCTIONS_H

#if 0
#pragma qt_class(QWinFunctions)
#endif

#include <QtCore/qobject.h>
#include <QtCore/qt_windows.h>
#include <QtWinExtras/qwinextrasglobal.h>
#ifdef QT_WIDGETS_LIB
#include <QtWidgets/qwidget.h>
#endif

QT_BEGIN_NAMESPACE

class QPixmap;
class QImage;
class QBitmap;
class QColor;
class QWindow;
class QString;
class QMargins;

class Q_WINEXTRAS_EXPORT QtWin
{
    Q_GADGET
    Q_ENUMS(HBitmapFormat WindowFlip3DPolicy)

public:
    enum HBitmapFormat
    {
        HBitmapNoAlpha,
        HBitmapPremultipliedAlpha,
        HBitmapAlpha
    };

    enum WindowFlip3DPolicy
    {
        FlipDefault,
        FlipExcludeBelow,
        FlipExcludeAbove
    };

    static HBITMAP createMask(const QBitmap &bitmap);
    static HBITMAP toHBITMAP(const QPixmap &p, HBitmapFormat format = HBitmapNoAlpha);
    static QPixmap fromHBITMAP(HBITMAP bitmap, HBitmapFormat format = HBitmapNoAlpha);
    static HICON toHICON(const QPixmap &p);
    static QImage imageFromHBITMAP(HDC hdc, HBITMAP bitmap, int width, int height);
    static QPixmap fromHICON(HICON icon);
    static HRGN toHRGN(const QRegion &region);
    static QRegion fromHRGN(HRGN hrgn);

    static QString stringFromHresult(HRESULT hresult);
    static QString errorStringFromHresult(HRESULT hresult);

    static QColor colorizationColor(bool *opaqueBlend = 0);
    static QColor realColorizationColor();

    static void setWindowExcludedFromPeek(QWindow *window, bool exclude);
    static bool isWindowExcludedFromPeek(QWindow *window);
    static void setWindowDisallowPeek(QWindow *window, bool disallow);
    static bool isWindowPeekDisallowed(QWindow *window);
    static void setWindowFlip3DPolicy(QWindow *window, WindowFlip3DPolicy policy);
    static WindowFlip3DPolicy windowFlip3DPolicy(QWindow *);

    static void extendFrameIntoClientArea(QWindow *window, int left, int top, int right, int bottom);
    static void extendFrameIntoClientArea(QWindow *window, const QMargins &margins);
    static void resetExtendedFrame(QWindow *window);

    static void enableBlurBehindWindow(QWindow *window, const QRegion &region);
    static void enableBlurBehindWindow(QWindow *window);
    static void disableBlurBehindWindow(QWindow *window);

    static bool isCompositionEnabled();
    static void setCompositionEnabled(bool enabled);
    static bool isCompositionOpaque();

    static void setCurrentProcessExplicitAppUserModelID(const QString &id);

    static void markFullscreenWindow(QWindow *, bool fullscreen = true);

    static void taskbarActivateTab(QWindow *);
    static void taskbarActivateTabAlt(QWindow *);
    static void taskbarAddTab(QWindow *);
    static void taskbarDeleteTab(QWindow *);

#ifdef QT_WIDGETS_LIB
    static inline void setWindowExcludedFromPeek(QWidget *window, bool exclude)
    {
        window->createWinId();
        setWindowExcludedFromPeek(window->windowHandle(), exclude);
    }

    static inline bool isWindowExcludedFromPeek(QWidget *window)
    {
        if (!window->windowHandle())
            return false;
        else
            return isWindowExcludedFromPeek(window->windowHandle());
    }

    static inline void setWindowDisallowPeek(QWidget *window, bool disallow)
    {
        window->createWinId();
        setWindowDisallowPeek(window->windowHandle(), disallow);
    }

    static inline bool isWindowPeekDisallowed(QWidget *window)
    {
        if (!window->windowHandle())
            return false;
        else
            return isWindowPeekDisallowed(window->windowHandle());
    }

    static inline void setWindowFlip3DPolicy(QWidget *window, WindowFlip3DPolicy policy)
    {
        window->createWinId();
        setWindowFlip3DPolicy(window->windowHandle(), policy);
    }

    static inline WindowFlip3DPolicy windowFlip3DPolicy(QWidget *window)
    {
        if (!window->windowHandle())
            return FlipDefault;
        else
            return windowFlip3DPolicy(window->windowHandle());
    }

    static inline void extendFrameIntoClientArea(QWidget *window, const QMargins &margins)
    {
        window->createWinId();
        extendFrameIntoClientArea(window->windowHandle(), margins);
    }

    static inline void extendFrameIntoClientArea(QWidget *window, int left, int top, int right, int bottom)
    {
        window->createWinId();
        extendFrameIntoClientArea(window->windowHandle(), left, top, right, bottom);
    }

    static inline void resetExtendedFrame(QWidget *window)
    {
        if (window->windowHandle())
            resetExtendedFrame(window->windowHandle());
    }

    static inline void enableBlurBehindWindow(QWidget *window, const QRegion &region)
    {
        window->createWinId();
        enableBlurBehindWindow(window->windowHandle(), region);
    }

    static inline void enableBlurBehindWindow(QWidget *window)
    {
        window->createWinId();
        enableBlurBehindWindow(window->windowHandle());
    }

    static inline void disableBlurBehindWindow(QWidget *window)
    {
        if (window->windowHandle())
            enableBlurBehindWindow(window->windowHandle());
    }

    static inline void markFullscreenWindow(QWidget *window, bool fullscreen = true)
    {
        window->createWinId();
        markFullscreenWindow(window->windowHandle(), fullscreen);
    }

    static inline void taskbarActivateTab(QWidget *window)
    {
        window->createWinId();
        taskbarActivateTab(window->windowHandle());
    }

    static inline void taskbarActivateTabAlt(QWidget *window)
    {
        window->createWinId();
        taskbarActivateTabAlt(window->windowHandle());
    }

    static inline void taskbarAddTab(QWidget *window)
    {
        window->createWinId();
        taskbarAddTab(window->windowHandle());
    }

    static inline void taskbarDeleteTab(QWidget *window)
    {
        window->createWinId();
        taskbarDeleteTab(window->windowHandle());
    }
#endif // QT_WIDGETS_LIB
};

#ifdef Q_QDOC

namespace QtWin
{

HBITMAP createMask(const QBitmap &bitmap);
HBITMAP toHBITMAP(const QPixmap &p, HBitmapFormat format = HBitmapNoAlpha);
QPixmap fromHBITMAP(HBITMAP bitmap, HBitmapFormat format = HBitmapNoAlpha);
HICON toHICON(const QPixmap &p);
QImage imageFromHBITMAP(HDC hdc, HBITMAP bitmap, int w, int h);
QPixmap fromHICON(HICON icon);
HRGN toHRGN(const QRegion &region);
QRegion fromHRGN(HRGN hrgn);
QString stringFromHresult(HRESULT hresult);
QString errorStringFromHresult(HRESULT hresult);
QColor colorizationColor(bool *opaqueBlend = 0);
QColor realColorizationColor();
void setWindowExcludedFromPeek(QWindow *window, bool exclude);
bool isWindowExcludedFromPeek(QWindow *window);
void setWindowDisallowPeek(QWindow *window, bool disallow);
bool isWindowPeekDisallowed(QWindow *window);
void setWindowFlip3DPolicy(QWindow *window, WindowFlip3DPolicy policy);
WindowFlip3DPolicy windowFlip3DPolicy(QWindow *);
void extendFrameIntoClientArea(QWindow *window, int left, int top, int right, int bottom);
void extendFrameIntoClientArea(QWindow *window, const QMargins &margins);
void resetExtendedFrame(QWindow *window);
void enableBlurBehindWindow(QWindow *window, const QRegion &region);
void enableBlurBehindWindow(QWindow *window);
void disableBlurBehindWindow(QWindow *window);

bool isCompositionEnabled();
void setCompositionEnabled(bool enabled);
bool isCompositionOpaque();
void setCurrentProcessExplicitAppUserModelID(const QString &id);
void markFullscreenWindow(QWindow *, bool fullscreen = true);
void taskbarActivateTab(QWindow *);
void taskbarActivateTabAlt(QWindow *);
void taskbarAddTab(QWindow *);
void taskbarDeleteTab(QWindow *);

}

#endif // #ifdef Q_DOC

QT_END_NAMESPACE

#endif // QWINFUNCTIONS_H
