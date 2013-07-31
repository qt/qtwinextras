/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of QtWinExtras in the Qt Toolkit.
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

#include "qquickjumplist.h"
#include <QIcon>

QT_BEGIN_NAMESPACE

/*!
    \qmltype JumpList
    \instantiates QQuickJumpList
    \inqmlmodule QtWinExtras

    \brief Enables you to modify the application Jump List.

    \since 5.2

    The JumpList type enables you to modify Windows Jump Lists.

    An application can use Jump Lists to provide users with faster access to
    files or to display shortcuts to tasks or commands.
 */

/*!
    \class QQuickJumpList
    \internal
 */

QQuickJumpList::QQuickJumpList(QQuickItem *parent) :
    QQuickItem(parent), frequentCategoryShown(false), recentCategoryShown(false)
{
}

/*!
    \qmlproperty object JumpList::tasks

    Application tasks.
 */
QQmlListProperty<QQuickJumpListItem> QQuickJumpList::tasks()
{
    return QQmlListProperty<QQuickJumpListItem>(this, this, &QQuickJumpList::appendTaskItem, 0, 0, 0);
}

/*!
    \qmlproperty object JumpList::destinations

    Categories of custom destinations.
 */
QQmlListProperty<QQuickJumpListCategory> QQuickJumpList::destinations()
{
    return QQmlListProperty<QQuickJumpListCategory>(this, this, &QQuickJumpList::appendGroup, 0, 0, 0);
}

/*!
    \qmlproperty bool JumpList::showFrequentCategory

    Contains true if the \e Frequent category is shown; otherwise false.
 */
bool QQuickJumpList::showFrequentCategory() const
{
    return frequentCategoryShown;
}

void QQuickJumpList::setShowFrequentCategory(bool show)
{
    frequentCategoryShown = show;
}

/*!
    \qmlproperty bool JumpList::showRecentCategory

    Contains true if the \e Recent category is shown; otherwise false.
 */
bool QQuickJumpList::showRecentCategory() const
{
    return recentCategoryShown;
}

void QQuickJumpList::setShowRecentCategory(bool show)
{
    recentCategoryShown = show;
}

void QQuickJumpList::componentComplete()
{
    QQuickItem::componentComplete();
    QJumpList jumplist;
    jumplist.begin();
    jumplist.setFrequentCategoryShown(frequentCategoryShown);
    jumplist.setRecentCategoryShown(recentCategoryShown);
    if (!taskList.isEmpty()) {
        jumplist.beginTasks();
        Q_FOREACH (QQuickJumpListItem *item, taskList)
            jumplist.addItem(item->toJumpListItem());
        taskList.clear();
    }
    if (!categoryList.isEmpty()) {
        Q_FOREACH (QQuickJumpListCategory *category, categoryList) {
            jumplist.beginCategory(category->title());
            QList<QJumpListItem *> items = category->toItemList();
            Q_FOREACH (QJumpListItem *item, items)
                jumplist.addItem(item);
        }
    }
    jumplist.commit();
}

void QQuickJumpList::appendTaskItem(QQmlListProperty<QQuickJumpListItem> *property, QQuickJumpListItem *value)
{
    static_cast<QQuickJumpList *>(property->data)->taskList.append(value);
}

void QQuickJumpList::appendGroup(QQmlListProperty<QQuickJumpListCategory> *property, QQuickJumpListCategory *value)
{
    static_cast<QQuickJumpList *>(property->data)->categoryList.append(value);
}


/*!
    \qmltype JumpCategory
    \instantiates QQuickJumpListCategory
    \inqmlmodule QtWinExtras

    \brief Represents a category of custom destinations.

    \since 5.2

    The JumpCategory type represents a category that consists of several
    Jump List destinations and has a title.
 */

/*!
    \class QQuickJumpListCategory
    \internal
 */

QQuickJumpListCategory::QQuickJumpListCategory(QObject *parent) :
    QObject(parent)
{
}

QQuickJumpListCategory::~QQuickJumpListCategory()
{
}

/*!
    \qmlproperty object JumpCategory::destinations

    The destinations in this category.
 */
QQmlListProperty<QQuickJumpListItem> QQuickJumpListCategory::destinations()
{
    return QQmlListProperty<QQuickJumpListItem>(this, this, &QQuickJumpListCategory::addItem, 0, 0, 0);
}

void QQuickJumpListCategory::setTitle(const QString &title)
{
    m_groupTitle = title;
}

/*!
    \qmlproperty string JumpCategory::title

    The title of the category.
 */
QString QQuickJumpListCategory::title() const
{
    return m_groupTitle;
}

QList<QJumpListItem *> QQuickJumpListCategory::toItemList() const
{
    QList<QJumpListItem *> destinations;
    foreach (QQuickJumpListItem *item, m_destinations)
        destinations.append(item->toJumpListItem());
    return destinations;
}

void QQuickJumpListCategory::addItem(QQmlListProperty<QQuickJumpListItem> *property, QQuickJumpListItem *value)
{
    static_cast<QQuickJumpListCategory *>(property->data)->m_destinations.append(value);
}


QQuickJumpListItem::QQuickJumpListItem(QObject *p) :
    QObject(p)
{
}

QQuickJumpListItem::~QQuickJumpListItem()
{
}

void QQuickJumpListItem::setType(int type)
{
    m_type = type;
}

int QQuickJumpListItem::type() const
{
    return m_type;
}

QJumpListItem *QQuickJumpListItem::toJumpListItem() const
{
    QJumpListItem *item = new QJumpListItem();
    switch (m_type) {
    case ItemTypeSeparator :
        item->setType(QJumpListItem::Separator);
        break;
    case ItemTypeDestination :
        item->setType(QJumpListItem::Destination);
        item->setFilePath(property("filePath").toString());
        break;
    case ItemTypeLink :
        item->setType(QJumpListItem::Link);
        item->setFilePath(property("executablePath").toString());
        item->setArguments(QStringList(property("arguments").toStringList()));
        item->setDescription(property("description").toString());
        item->setTitle(property("title").toString());
        item->setIcon(QIcon(property("iconPath").toString()));
        break;
    }

    return item;
}

QT_END_NAMESPACE
