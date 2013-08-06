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

#ifndef QQUICKJUMPLIST_H
#define QQUICKJUMPLIST_H

#include <QQuickItem>
#include <QQmlListProperty>
#include <QIcon>
#include <QWinJumpList>
#include <QWinJumpListItem>

QT_BEGIN_NAMESPACE

class QQuickJumpListItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int __jumpListItemType READ type WRITE setType)

public:
    enum JumpListItemType {
        ItemTypeLink = 1,
        ItemTypeDestination = 2,
        ItemTypeSeparator = 3
    };

    Q_ENUMS(JumpListItemType)

    explicit QQuickJumpListItem(QObject *p = 0);
    ~QQuickJumpListItem();
    void setType(int type);
    int type() const;
    QWinJumpListItem *toJumpListItem() const;

private:
    int m_type; // 1 - link, 2 - destination
};

class QQuickJumpListCategory : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QQuickJumpListItem> destinations READ destinations)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_CLASSINFO("DefaultProperty", "destinations")

public:
    explicit QQuickJumpListCategory(QObject *parent = 0);
    ~QQuickJumpListCategory();
    QQmlListProperty<QQuickJumpListItem> destinations();
    void setTitle(const QString &title);
    QString title() const;

    QList<QWinJumpListItem *> toItemList() const;

    static void addItem(QQmlListProperty<QQuickJumpListItem> *property, QQuickJumpListItem *value);

private:
    QString m_groupTitle;
    QList<QQuickJumpListItem *> m_destinations;
};

class QQuickJumpList : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QQuickJumpListItem> tasks READ tasks)
    Q_PROPERTY(QQmlListProperty<QQuickJumpListCategory> destinations READ destinations)
    Q_PROPERTY(bool showFrequentCategory READ showFrequentCategory WRITE setShowFrequentCategory)
    Q_PROPERTY(bool showRecentCategory   READ showRecentCategory   WRITE setShowRecentCategory)

public:
    explicit QQuickJumpList(QQuickItem *parent = 0);
    QQmlListProperty<QQuickJumpListItem> tasks();
    QQmlListProperty<QQuickJumpListCategory> destinations();
    bool showFrequentCategory() const;
    void setShowFrequentCategory(bool);
    bool showRecentCategory() const;
    void setShowRecentCategory(bool);

    virtual void componentComplete();

    static void appendTaskItem(QQmlListProperty<QQuickJumpListItem> *property, QQuickJumpListItem *value);
    static void appendGroup(QQmlListProperty<QQuickJumpListCategory> *property, QQuickJumpListCategory *value);

private:
    QList<QQuickJumpListItem *> taskList;
    QList<QQuickJumpListCategory *> categoryList;
    bool frequentCategoryShown;
    bool recentCategoryShown;
};

QT_END_NAMESPACE

#endif // QQUICKJUMPLIST_H
