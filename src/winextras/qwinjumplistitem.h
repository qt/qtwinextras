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

#ifndef QWINJUMPLISTITEM_H
#define QWINJUMPLISTITEM_H

#include <QtGui/qicon.h>
#include <QtCore/qobject.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qscopedpointer.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QWinJumpListItemPrivate;

class Q_WINEXTRAS_EXPORT QWinJumpListItem
{
public:
    enum Type {
        Destination,
        Link,
        Separator
    };

    explicit QWinJumpListItem(Type type);
    ~QWinJumpListItem();

    void setType(Type type);
    Type type() const;
    void setFilePath(const QString &filePath);
    QString filePath() const;
    void setWorkingDirectory(const QString &workingDirectory);
    QString workingDirectory() const;
    void setIcon(const QIcon &icon);
    QIcon icon() const;
    void setTitle(const QString &title);
    QString title() const;
    void setDescription(const QString &description);
    QString description() const;
    void setArguments(const QStringList &arguments);
    QStringList arguments() const;

private:
    Q_DISABLE_COPY(QWinJumpListItem)
    Q_DECLARE_PRIVATE(QWinJumpListItem)
    QScopedPointer<QWinJumpListItemPrivate> d_ptr;
};

#ifndef QT_NO_DEBUG_STREAM
Q_WINEXTRAS_EXPORT QDebug operator<<(QDebug, const QWinJumpListItem *);
#endif

QT_END_NAMESPACE

#endif // QWINJUMPLISTITEM_H
