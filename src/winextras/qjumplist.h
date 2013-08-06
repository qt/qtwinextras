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

#ifndef QJUMPLIST_H
#define QJUMPLIST_H

#include <QtCore/qobject.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qscopedpointer.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QIcon;
class QJumpListItem;
class QJumpListPrivate;

class Q_WINEXTRAS_EXPORT QJumpList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int recentCategoryShown READ isRecentCategoryShown WRITE setRecentCategoryShown)
    Q_PROPERTY(int frequentCategoryShown READ isFrequentCategoryShown WRITE setFrequentCategoryShown)

public:
    explicit QJumpList(QObject *parent = 0);
    ~QJumpList();

public Q_SLOTS:
    bool begin();
    bool commit();
    bool abort();
    bool clear();

public:
    bool setApplicationId(const QString &);
    QList<QJumpListItem *> removedDestinations() const;
    int capacity() const;

    void setRecentCategoryShown(bool);
    bool isRecentCategoryShown() const;
    void setFrequentCategoryShown(bool);
    bool isFrequentCategoryShown() const;

    void beginCategory(const QString &title);
    void beginTasks();

    bool addItem(QJumpListItem *item);
    void addDestination(const QString &filePath);
    void addLink(const QString &title, const QString &executablePath, const QStringList &arguments = QStringList());
    void addLink(const QString &title, const QString &description, const QString &executablePath, const QStringList &arguments = QStringList());
    void addLink(const QIcon &icon, const QString &title, const QString &executablePath, const QStringList &arguments = QStringList());
    void addLink(const QIcon &icon, const QString &title, const QString &description, const QString &executablePath, const QStringList &arguments = QStringList());
    void addLink(const QIcon &icon, const QString &title, const QString &description, const QString &workingDirectory, const QString &executablePath, const QStringList &arguments);
    void addSeparator();

private:
    Q_DISABLE_COPY(QJumpList)
    Q_DECLARE_PRIVATE(QJumpList)
    QScopedPointer<QJumpListPrivate> d_ptr;
};

QT_END_NAMESPACE

#endif // QJUMPLIST_H
