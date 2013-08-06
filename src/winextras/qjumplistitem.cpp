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

#include "qjumplistitem.h"

QT_BEGIN_NAMESPACE

/*!
    \class QJumpListItem
    \inmodule QtWinExtras
    \since 5.2
    \inheaderfile QJumpList
    \brief The QJumpListItem class represents a Jump List destination or link.

    Objects of this class are returned by QJumpList::removedDestinations()
    and can also be used to add items to a Jump List.
 */

class QJumpListItemPrivate
{
public:
    QString filePath;
    QString workingDirectory;
    QString title;
    QString description;
    QIcon icon;
    QStringList arguments;
    QJumpListItem::Type type;
};

/*!
    Constructs a QJumpListItem with the specified \a type.
 */
QJumpListItem::QJumpListItem(QJumpListItem::Type type) :
    d_ptr(new QJumpListItemPrivate)
{
    d_ptr->type = type;
}

/*!
    Destroys the QJumpListItem.
 */
QJumpListItem::~QJumpListItem()
{
}

/*!
    Sets the item \a type.
 */
void QJumpListItem::setType(QJumpListItem::Type type)
{
    Q_D(QJumpListItem);
    d->type = type;
}

/*!
    Returns the item type.
 */
QJumpListItem::Type QJumpListItem::type() const
{
    Q_D(const QJumpListItem);
    return d->type;
}

/*!
    Sets the item \a filePath, the meaning of which depends on the type of this
    item:

    \list

        \li If the item type is QJumpListItem::Destination, \a filePath is the
            path to a file that can be opened by an application.

        \li If the item type is QJumpListItem::Link, \a filePath is the path to
            an executable that is executed when this item is clicked by the
            user.

    \endlist

    \sa setWorkingDirectory(), setArguments()
 */
void QJumpListItem::setFilePath(const QString &filePath)
{
    Q_D(QJumpListItem);
    d->filePath = filePath;
}

/*!
    Returns the file path set by setFilePath().
 */
QString QJumpListItem::filePath() const
{
    Q_D(const QJumpListItem);
    return d->filePath;
}

/*!
    Sets the path to the working directory of this item to \a workingDirectory.

    This value is used only if the type of this item is QJumpListItem::Link.

    \sa setFilePath()
 */
void QJumpListItem::setWorkingDirectory(const QString &workingDirectory)
{
    Q_D(QJumpListItem);
    d->workingDirectory = workingDirectory;
}

/*!
    Returns the working directory path.
 */
QString QJumpListItem::workingDirectory() const
{
    Q_D(const QJumpListItem);
    return d->workingDirectory;
}

/*!
    Sets the \a icon of this item.

    This value is used only if the type of this item is QJumpListItem::Link.
 */
void QJumpListItem::setIcon(const QIcon &icon)
{
    Q_D(QJumpListItem);
    d->icon = icon;
}

/*!
    Returns the icon set for this item.
 */
QIcon QJumpListItem::icon() const
{
    Q_D(const QJumpListItem);
    return d->icon;
}

/*!
    Sets the \a title of this item.

    This value is used only if the type of this item is QJumpListItem::Link.
 */
void QJumpListItem::setTitle(const QString &title)
{
    Q_D(QJumpListItem);
    d->title = title;
}

/*!
    Returns the title of this item.
 */
QString QJumpListItem::title() const
{
    Q_D(const QJumpListItem);
    return d->title;
}

/*!
    Sets a \a description for this item.

    This value is used only if the type of this item is QJumpListItem::Link.
 */
void QJumpListItem::setDescription(const QString &description)
{
    Q_D(QJumpListItem);
    d->description = description;
}

/*!
    Returns the description of this item.
 */
QString QJumpListItem::description() const
{
    Q_D(const QJumpListItem);
    return d->description;
}

/*!
    Sets command-line \a arguments for this item.

    This value is used only if the type of this item is QJumpListItem::Link.

    \sa setFilePath()
 */
void QJumpListItem::setArguments(const QStringList &arguments)
{
    Q_D(QJumpListItem);
    d->arguments = arguments;
}

/*!
    Returns the command-line arguments of this item.
 */
QStringList QJumpListItem::arguments() const
{
    Q_D(const QJumpListItem);
    return d->arguments;
}

QT_END_NAMESPACE
