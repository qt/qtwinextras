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

#ifndef QWINJUMPLIST_H
#define QWINJUMPLIST_H

#include <QtCore/qobject.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qscopedpointer.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QWinJumpListItem;
class QWinJumpListPrivate;
class QWinJumpListCategory;

class Q_WINEXTRAS_EXPORT QWinJumpList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier)

public:
    explicit QWinJumpList(QObject *parent = nullptr);
    ~QWinJumpList();

    QString identifier() const;
    void setIdentifier(const QString &identifier);

    QWinJumpListCategory *recent() const;
    QWinJumpListCategory *frequent() const;
    QWinJumpListCategory *tasks() const;

    QList<QWinJumpListCategory *> categories() const;
    void addCategory(QWinJumpListCategory *category);
    QWinJumpListCategory *addCategory(const QString &title, const QList<QWinJumpListItem *> items = QList<QWinJumpListItem *>());

public Q_SLOTS:
    void clear();

private:
    Q_DISABLE_COPY(QWinJumpList)
    Q_DECLARE_PRIVATE(QWinJumpList)
    QScopedPointer<QWinJumpListPrivate> d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_rebuild())
};

#ifndef QT_NO_DEBUG_STREAM
Q_WINEXTRAS_EXPORT QDebug operator<<(QDebug, const QWinJumpList *);
#endif

QT_END_NAMESPACE

#endif // QWINJUMPLIST_H
