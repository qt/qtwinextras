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

#include "qwinjumplistcategory.h"
#include "qwinjumplistcategory_p.h"
#include "qwinjumplistitem_p.h"
#include "qwinfunctions_p.h"
#include "qwinjumplist_p.h"

#include <shlobj.h>

QT_BEGIN_NAMESPACE

/*!
    \class QWinJumpListCategory
    \inmodule QtWinExtras
    \since 5.2
    \brief The QWinJumpListCategory class represents a jump list category.
 */

/*!
    \enum QWinJumpListCategory::Type

    This enum describes the available QWinJumpListCategory types.

    \value  Custom
            A custom jump list category.
    \value  Recent
            A jump list category of "recent" items.
    \value  Frequent
            A jump list category of "frequent" items.
    \value  Tasks
            A jump list category of tasks.
 */

QWinJumpListCategory *QWinJumpListCategoryPrivate::create(QWinJumpListCategory::Type type, QWinJumpList *jumpList)
{
    QWinJumpListCategory *category = new QWinJumpListCategory;
    category->d_func()->type = type;
    category->d_func()->jumpList = jumpList;
    if (type == QWinJumpListCategory::Recent || type == QWinJumpListCategory::Frequent)
        category->d_func()->loadRecents();
    return category;
}

void QWinJumpListCategoryPrivate::invalidate()
{
    if (jumpList)
        QWinJumpListPrivate::get(jumpList)->invalidate();
}

void QWinJumpListCategoryPrivate::loadRecents()
{
    HRESULT hresult = CoCreateInstance(CLSID_ApplicationDocumentLists, 0, CLSCTX_INPROC_SERVER, IID_IApplicationDocumentLists, reinterpret_cast<void **>(&pDocList));
    if (SUCCEEDED(hresult)) {
        IObjectArray *array = 0;
        hresult = pDocList->GetList(type == QWinJumpListCategory::Recent ? ADLT_RECENT : ADLT_FREQUENT,
                                    0, IID_IObjectArray, reinterpret_cast<void **>(&array));
        if (SUCCEEDED(hresult)) {
            items = QWinJumpListPrivate::fromComCollection(array);
            array->Release();
        }
    }
    if (FAILED(hresult))
        QWinJumpListPrivate::warning("loadRecents", hresult);
}

void QWinJumpListCategoryPrivate::addRecent(QWinJumpListItem *item)
{
    if (item->type() == QWinJumpListItem::Link)
        SHAddToRecentDocs(SHARD_LINK, QWinJumpListPrivate::toIShellLink(item));
    else if (item->type() == QWinJumpListItem::Destination)
        SHAddToRecentDocs(SHARD_SHELLITEM, QWinJumpListPrivate::toIShellItem(item));
}

void QWinJumpListCategoryPrivate::clearRecents()
{
    IApplicationDestinations *pDest = 0;
    HRESULT hresult = CoCreateInstance(CLSID_ApplicationDestinations, 0, CLSCTX_INPROC_SERVER, IID_IApplicationDestinations, reinterpret_cast<void **>(&pDest));
    if (SUCCEEDED(hresult)) {
        hresult = pDest->RemoveAllDestinations();
        pDest->Release();
    }
    if (FAILED(hresult))
        QWinJumpListPrivate::warning("clearRecents", hresult);
}

/*!
    Constructs a custom QWinJumpListCategory with the specified \a title.
 */
QWinJumpListCategory::QWinJumpListCategory(const QString &title) :
    d_ptr(new QWinJumpListCategoryPrivate)
{
    d_ptr->pDocList = 0;
    d_ptr->type = Custom;
    d_ptr->visible = false;
    d_ptr->title = title;
}

/*!
    Destroys the QWinJumpListCategory.
 */
QWinJumpListCategory::~QWinJumpListCategory()
{
    Q_D(QWinJumpListCategory);
    if (d->pDocList) {
        d->pDocList->Release();
        d->pDocList = 0;
    }
    qDeleteAll(d->items);
    d->items.clear();
}

/*!
    Returns the category type.
 */
QWinJumpListCategory::Type QWinJumpListCategory::type() const
{
    Q_D(const QWinJumpListCategory);
    return d->type;
}

/*!
    Returns whether the category is visible.
 */
bool QWinJumpListCategory::isVisible() const
{
    Q_D(const QWinJumpListCategory);
    return d->visible;
}

/*!
    Sets the category \a visible.
 */
void QWinJumpListCategory::setVisible(bool visible)
{
    Q_D(QWinJumpListCategory);
    if (d->visible != visible) {
        d->visible = visible;
        d->invalidate();
    }
}

/*!
    Returns the category title.
 */
QString QWinJumpListCategory::title() const
{
    Q_D(const QWinJumpListCategory);
    return d->title;
}

/*!
    Sets the category \a title.
 */
void QWinJumpListCategory::setTitle(const QString &title)
{
    Q_D(QWinJumpListCategory);
    if (d->title != title) {
        d->title = title;
        d->invalidate();
    }
}

/*!
    Returns the amount of items in the category.
 */
int QWinJumpListCategory::count() const
{
    Q_D(const QWinJumpListCategory);
    return d->items.count();
}

/*!
    Returns whether the category is empty.
 */
bool QWinJumpListCategory::isEmpty() const
{
    Q_D(const QWinJumpListCategory);
    return d->items.isEmpty();
}

/*!
    Returns the list of items in the category.
 */
QList<QWinJumpListItem *> QWinJumpListCategory::items() const
{
    Q_D(const QWinJumpListCategory);
    return d->items;
}

/*!
    Adds an \a item to the category.
 */
void QWinJumpListCategory::addItem(QWinJumpListItem *item)
{
    Q_D(QWinJumpListCategory);
    if (!item)
        return;

    QWinJumpListItemPrivate *p = QWinJumpListItemPrivate::get(item);
    if (p->category != this) {
        p->category = this;
        d->items.append(item);
        if (d->type == QWinJumpListCategory::Recent || d->type == QWinJumpListCategory::Frequent)
            d->addRecent(item);
        d->invalidate();
    }
}

/*!
    Adds a destination to the category pointing to \a filePath.
 */
QWinJumpListItem *QWinJumpListCategory::addDestination(const QString &filePath)
{
    QWinJumpListItem *item = new QWinJumpListItem(QWinJumpListItem::Destination);
    item->setFilePath(filePath);
    addItem(item);
    return item;
}

/*!
    Adds a link to the category using \a title, \a executablePath, and
    optionally \a arguments.
 */
QWinJumpListItem *QWinJumpListCategory::addLink(const QString &title, const QString &executablePath, const QStringList &arguments)
{
    return addLink(QIcon(), title, executablePath, arguments);
}

/*!
    \overload addLink()

    Adds a link to the category using \a icon, \a title, \a executablePath,
    and optionally \a arguments.
 */
QWinJumpListItem *QWinJumpListCategory::addLink(const QIcon &icon, const QString &title, const QString &executablePath, const QStringList &arguments)
{
    QWinJumpListItem *item = new QWinJumpListItem(QWinJumpListItem::Link);
    item->setFilePath(executablePath);
    item->setTitle(title);
    item->setArguments(arguments);
    item->setIcon(icon);
    addItem(item);
    return item;
}

/*!
    Adds a separator to the category.

    \note Only tasks category supports separators.
 */
QWinJumpListItem *QWinJumpListCategory::addSeparator()
{
    Q_D(QWinJumpListCategory);
    if (d->type != Tasks) {
        qWarning("QWinJumpListCategory::addSeparator(): only tasks category supports separators.");
        return 0;
    }
    QWinJumpListItem *item = new QWinJumpListItem(QWinJumpListItem::Separator);
    addItem(item);
    return item;
}

/*!
    Clears the category.
 */
void QWinJumpListCategory::clear()
{
    Q_D(QWinJumpListCategory);
    if (!d->items.isEmpty()) {
        qDeleteAll(d->items);
        d->items.clear();
        if (d->type == QWinJumpListCategory::Recent || d->type == QWinJumpListCategory::Frequent)
            d->clearRecents();
        d->invalidate();
    }
}

QT_END_NAMESPACE
