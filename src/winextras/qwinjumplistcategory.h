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

#ifndef QWINJUMPLISTCATEGORY_H
#define QWINJUMPLISTCATEGORY_H

#include <QtGui/qicon.h>
#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qscopedpointer.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QWinJumpListItem;
class QWinJumpListCategoryPrivate;

class Q_WINEXTRAS_EXPORT QWinJumpListCategory
{
public:
    enum Type {
        Custom,
        Recent,
        Frequent,
        Tasks
    };
    explicit QWinJumpListCategory(const QString &title = QString());
    ~QWinJumpListCategory();

    Type type() const;

    bool isVisible() const;
    void setVisible(bool visible);

    QString title() const;
    void setTitle(const QString &title);

    int count() const;
    bool isEmpty() const;
    QList<QWinJumpListItem *> items() const;

    void addItem(QWinJumpListItem *item);
    QWinJumpListItem *addDestination(const QString &filePath);
    QWinJumpListItem *addLink(const QString &title, const QString &executablePath, const QStringList &arguments = QStringList());
    QWinJumpListItem *addLink(const QIcon &icon, const QString &title, const QString &executablePath, const QStringList &arguments = QStringList());
    QWinJumpListItem *addSeparator();

    void clear();

private:
    Q_DISABLE_COPY(QWinJumpListCategory)
    Q_DECLARE_PRIVATE(QWinJumpListCategory)
    QScopedPointer<QWinJumpListCategoryPrivate> d_ptr;
};

#ifndef QT_NO_DEBUG_STREAM
Q_WINEXTRAS_EXPORT QDebug operator<<(QDebug d, const QWinJumpListCategory *);
#endif

QT_END_NAMESPACE

#endif // QWINJUMPLISTCATEGORY_H
