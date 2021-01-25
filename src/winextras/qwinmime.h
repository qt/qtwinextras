/****************************************************************************
**
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

#ifndef QWINMIME_H
#define QWINMIME_H

#include <QtWinExtras/qwinextrasglobal.h>

#include <QtCore/qt_windows.h>
#include <QtCore/qvector.h>
#include <QtCore/qlist.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE

class QMimeData;

#ifdef Q_CLANG_QDOC
typedef struct _FORMATETC {} FORMATETC;
typedef struct _STGMEDIUM {} STGMEDIUM;
typedef void *HBITMAP;
typedef void *HICON;
typedef void *HRGN;
typedef void *IDataObject;
#endif

class Q_WINEXTRAS_EXPORT QWinMime // Keep in sync with QWindowsMime in the Windows platform plugin.
{
    Q_DISABLE_COPY(QWinMime)
public:
    QWinMime();
    virtual ~QWinMime();

    // for converting from Qt
    virtual bool canConvertFromMime(const FORMATETC &formatetc, const QMimeData *mimeData) const = 0;
    virtual bool convertFromMime(const FORMATETC &formatetc, const QMimeData *mimeData, STGMEDIUM * pmedium) const = 0;
    virtual QVector<FORMATETC> formatsForMime(const QString &mimeType, const QMimeData *mimeData) const = 0;

    // for converting to Qt
    virtual bool canConvertToMime(const QString &mimeType, IDataObject *pDataObj) const = 0;
    virtual QVariant convertToMime(const QString &mimeType, IDataObject *pDataObj, QVariant::Type preferredType) const = 0;
    virtual QString mimeForFormat(const FORMATETC &formatetc) const = 0;

    static int registerMimeType(const QString &mime);
};

QT_END_NAMESPACE

#endif // QWINMIME_H
