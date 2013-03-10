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

#include <QObject>
#include <QtWinExtras/qwinextrasglobal.h>
#include <QtCore/qt_windows.h>

QT_BEGIN_NAMESPACE

class QPixmap;
class QImage;
class QBitmap;
class QColor;
class QWindow;
class QString;
class QMargins;

namespace QWinExtras
{

enum HBitmapFormat
{
    HBitmapNoAlpha,
    HBitmapPremultipliedAlpha,
    HBitmapAlpha
};

HBITMAP Q_WINEXTRAS_EXPORT createMask(const QBitmap &bitmap);
HBITMAP Q_WINEXTRAS_EXPORT toHBITMAP(const QPixmap &p, HBitmapFormat format = HBitmapNoAlpha);
QPixmap Q_WINEXTRAS_EXPORT fromHBITMAP(HBITMAP bitmap, HBitmapFormat format = HBitmapNoAlpha);
HICON Q_WINEXTRAS_EXPORT toHICON(const QPixmap &p);
QImage Q_WINEXTRAS_EXPORT imageFromHBITMAP(HDC hdc, HBITMAP bitmap, int width, int height);
QPixmap Q_WINEXTRAS_EXPORT fromHICON(HICON icon);
HRGN Q_WINEXTRAS_EXPORT toHRGN(const QRegion &region);

QString Q_WINEXTRAS_EXPORT stringFromHresult(HRESULT hresult);
QString Q_WINEXTRAS_EXPORT errorStringFromHresult(HRESULT hresult);

enum WindowFlip3DPolicy
{
    FlipDefault,
    FlipExcludeBelow,
    FlipExcludeAbove
};

QColor Q_WINEXTRAS_EXPORT colorizationColor(bool *opaqueBlend = 0);
QColor Q_WINEXTRAS_EXPORT realColorizationColor();

void Q_WINEXTRAS_EXPORT setWindowExcludedFromPeek(QWindow *window, bool exclude);
bool Q_WINEXTRAS_EXPORT isWindowExcludedFromPeek(QWindow *window);
void Q_WINEXTRAS_EXPORT setWindowDisallowPeek(QWindow *window, bool disallow);
bool Q_WINEXTRAS_EXPORT isWindowPeekDisallowed(QWindow *window);
void Q_WINEXTRAS_EXPORT setWindowFlip3DPolicy(QWindow *window, WindowFlip3DPolicy policy);
WindowFlip3DPolicy Q_WINEXTRAS_EXPORT windowFlip3DPolicy(QWindow *);

void Q_WINEXTRAS_EXPORT extendFrameIntoClientArea(QWindow *window, int left, int top, int right, int bottom);
void Q_WINEXTRAS_EXPORT extendFrameIntoClientArea(QWindow *window, const QMargins &margins);
void Q_WINEXTRAS_EXPORT resetExtendedFrame(QWindow *window);

void Q_WINEXTRAS_EXPORT enableBlurBehindWindow(QWindow *window, const QRegion &region);
void Q_WINEXTRAS_EXPORT enableBlurBehindWindow(QWindow *window);
void Q_WINEXTRAS_EXPORT disableBlurBehindWindow(QWindow *window);

bool Q_WINEXTRAS_EXPORT isCompositionEnabled();
void Q_WINEXTRAS_EXPORT setCompositionEnabled(bool enabled);

void Q_WINEXTRAS_EXPORT setCurrentProcessExplicitAppUserModelID(const QString &id);

void Q_WINEXTRAS_EXPORT markFullscreenWindow(QWindow *, bool fullscreen = true);

void Q_WINEXTRAS_EXPORT taskbarActivateTab(QWindow *);
void Q_WINEXTRAS_EXPORT taskbarActivateTabAlt(QWindow *);
void Q_WINEXTRAS_EXPORT taskbarAddTab(QWindow *);
void Q_WINEXTRAS_EXPORT taskbarDeleteTab(QWindow *);

}

#ifdef QT_WIDGETS_LIB

#include <QWidget>

namespace QWinExtras
{

inline void setWindowExcludedFromPeek(QWidget *window, bool exclude)
{
    window->createWinId();
    setWindowExcludedFromPeek(window->windowHandle(), exclude);
}

inline bool isWindowExcludedFromPeek(QWidget *window)
{
    if (!window->windowHandle())
        return false;
    else
        return isWindowExcludedFromPeek(window->windowHandle());
}

inline void setWindowDisallowPeek(QWidget *window, bool disallow)
{
    window->createWinId();
    setWindowDisallowPeek(window->windowHandle(), disallow);
}

inline bool isWindowPeekDisallowed(QWidget *window)
{
    if (!window->windowHandle())
        return false;
    else
        return isWindowPeekDisallowed(window->windowHandle());
}

inline void setWindowFlip3DPolicy(QWidget *window, WindowFlip3DPolicy policy)
{
    window->createWinId();
    setWindowFlip3DPolicy(window->windowHandle(), policy);
}

inline WindowFlip3DPolicy windowFlip3DPolicy(QWidget *window)
{
    if (!window->windowHandle())
        return FlipDefault;
    else
        return windowFlip3DPolicy(window->windowHandle());
}

inline void extendFrameIntoClientArea(QWidget *window, const QMargins &margins)
{
    window->createWinId();
    extendFrameIntoClientArea(window->windowHandle(), margins);
}

inline void extendFrameIntoClientArea(QWidget *window, int left, int top, int right, int bottom)
{
    window->createWinId();
    extendFrameIntoClientArea(window->windowHandle(), left, top, right, bottom);
}

inline void resetExtendedFrame(QWidget *window)
{
    if (window->windowHandle())
        resetExtendedFrame(window->windowHandle());
}

inline void enableBlurBehindWindow(QWidget *window, const QRegion &region)
{
    window->createWinId();
    enableBlurBehindWindow(window->windowHandle(), region);
}

inline void enableBlurBehindWindow(QWidget *window)
{
    window->createWinId();
    enableBlurBehindWindow(window->windowHandle());
}

inline void disableBlurBehindWindow(QWidget *window)
{
    if (window->windowHandle())
        enableBlurBehindWindow(window->windowHandle());
}

inline void markFullscreenWindow(QWidget *window, bool fullscreen = true)
{
    window->createWinId();
    markFullscreenWindow(window->windowHandle(), fullscreen);
}

inline void taskbarActivateTab(QWidget *window)
{
    window->createWinId();
    taskbarActivateTab(window->windowHandle());
}

inline void taskbarActivateTabAlt(QWidget *window)
{
    window->createWinId();
    taskbarActivateTabAlt(window->windowHandle());
}

inline void taskbarAddTab(QWidget *window)
{
    window->createWinId();
    taskbarAddTab(window->windowHandle());
}

inline void taskbarDeleteTab(QWidget *window)
{
    window->createWinId();
    taskbarDeleteTab(window->windowHandle());
}

}

#endif // QT_WIDGETS_LIB

#ifdef Q_QDOC

namespace QWinExtras
{

HBITMAP createMask(const QBitmap &bitmap);
HBITMAP toHBITMAP(const QPixmap &p, HBitmapFormat format = HBitmapNoAlpha);
QPixmap fromHBITMAP(HBITMAP bitmap, HBitmapFormat format = HBitmapNoAlpha);
HICON toHICON(const QPixmap &p);
QImage imageFromHBITMAP(HDC hdc, HBITMAP bitmap, int w, int h);
QPixmap fromHICON(HICON icon);
HRGN toHRGN(const QRegion &region);
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
