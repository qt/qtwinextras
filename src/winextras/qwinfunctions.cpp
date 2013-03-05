/****************************************************************************
**
** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
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

#include "qwinfunctions.h"
#include <QPixmap>
#include <QBitmap>
#include <QImage>

QT_BEGIN_NAMESPACE

Q_GUI_EXPORT HBITMAP qt_createIconMask(const QBitmap &bitmap);
Q_GUI_EXPORT HBITMAP qt_pixmapToWinHBITMAP(const QPixmap &p, int hbitmapFormat = 0);
Q_GUI_EXPORT QPixmap qt_pixmapFromWinHBITMAP(HBITMAP bitmap, int hbitmapFormat = 0);
Q_GUI_EXPORT HICON   qt_pixmapToWinHICON(const QPixmap &p);
Q_GUI_EXPORT QImage  qt_imageFromWinHBITMAP(HDC hdc, HBITMAP bitmap, int w, int h);
Q_GUI_EXPORT QPixmap qt_pixmapFromWinHICON(HICON icon);

namespace Qt
{

/*!
    \since 5.1

    Creates a \c HBITMAP equivalent of the QBitmap.

    It is the caller's responsibility to free the \c HBITMAP data after use.

    \sa toWinHBITMAP()
*/
HBITMAP createWinIconMask(const QBitmap &bitmap)
{
    return qt_createIconMask(bitmap);
}

/*!
    \since 5.1

    Creates a \c HBITMAP equivalent to the QPixmap,
    based on the given \a format. Returns the \c HBITMAP handle.

    It is the caller's responsibility to free the \c HBITMAP data
    after use.

    \sa fromWinHBITMAP()
*/
HBITMAP toWinHBITMAP(const QPixmap &p, HBitmapFormat format)
{
    return qt_pixmapToWinHBITMAP(p, format);
}

/*!
    \since 5.1

    Returns a QPixmap that is equivalent to the
    given \a bitmap. The conversion is based on the specified \a format.

    \sa toWinHBITMAP()
*/
QPixmap fromWinHBITMAP(HBITMAP bitmap, HBitmapFormat format)
{
    return qt_pixmapFromWinHBITMAP(bitmap, format);
}

/*!
    \since 5.1

    Creates a \c HICON equivalent to the QPixmap.
    Returns the \c HICON handle.

    It is the caller's responsibility to free the \c HICON data after use.

    \sa fromWinHICON()
*/
HICON toWinHICON(const QPixmap &p)
{
    return qt_pixmapToWinHICON(p);
}

/*!
    \since 5.1

    Returns a QImage that is equivalent to the
    given \a bitmap. The conversion is based on the specified \c HDC context.

    \sa toWinHBITMAP()
*/
QImage imageFromWinHBITMAP(HDC hdc, HBITMAP bitmap, int w, int h)
{
    return qt_imageFromWinHBITMAP(hdc, bitmap, w, h);
}

/*!
    \since 5.1

    Returns a QPixmap that is equivalent to the given \a icon.

    \sa toWinHICON()
*/
QPixmap fromWinHICON(HICON icon)
{
    return qt_pixmapFromWinHICON(icon);
}

} // namespace Qt

/*!
    \enum Qt::HBitmapFormat

    \since 5.1

    This enum defines how the conversion between \c
    HBITMAP and QPixmap is performed.

    \warning This enum is only available on Windows.

    \value HBitmapNoAlpha The alpha channel is ignored and always treated as
    being set to fully opaque. This is preferred if the \c HBITMAP is
    used with standard GDI calls, such as \c BitBlt().

    \value HBitmapPremultipliedAlpha The \c HBITMAP is treated as having an
    alpha channel and premultiplied colors. This is preferred if the
    \c HBITMAP is accessed through the \c AlphaBlend() GDI function.

    \value HBitmapAlpha The \c HBITMAP is treated as having a plain alpha
    channel. This is the preferred format if the \c HBITMAP is going
    to be used as an application icon or systray icon.

    \sa fromWinHBITMAP(), toWinHBITMAP()
*/

QT_END_NAMESPACE
