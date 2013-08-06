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

#include "qjumplist.h"
#include "qjumplistitem.h"

#include <QDir>
#include <QCoreApplication>
#include <qt_windows.h>
#include <propvarutil.h>

#include "qwinfunctions.h"
#include "qwinfunctions_p.h"
#include "winshobjidl_p.h"
#include "winpropkey_p.h"

QT_BEGIN_NAMESPACE

/*!
    \class QJumpList
    \inmodule QtWinExtras
    \brief The QJumpList class represents a transparent wrapper around Windows
    Jump Lists.

    \since 5.2

    An application can use Jump Lists to provide users with faster access to
    files or to display shortcuts to tasks or commands.
 */

/*!
    \enum QJumpListItem::Type

    This enum specifies QJumpListItem type, changing its meaning for QJumpList.

    \value  Unknown
            Invalid item type.
    \value  Destination
            Item acts as a link to a file that the application can open.
    \value  Link
            Item represents a link to some application.
    \value  Separator
            Item becomes a separator. This value is used only for task lists.
 */

class QJumpListPrivate
{
public:
    QJumpListPrivate() :
        pDestList(0), isListBegan(false), showFrequentCategory(false), showRecentCategory(false),
        categoryBegan(false), tasksBegan(false), listSize(0)
    {
    }

    static void warning(const char *function, HRESULT hresult)
    {
        const QString err = QWinExtras::errorStringFromHresult(hresult);
        qWarning("QJumpList: %s() failed: %#010x, %s.", function, (unsigned)hresult, qPrintable(err));
    }

    static QString iconsDirPath()
    {
        QString iconDirPath = QDir::tempPath() + QLatin1Char('/') + QCoreApplication::instance()->applicationName() + QLatin1String("/qt-jl-icons/");
        QDir().mkpath(iconDirPath);
        return iconDirPath;
    }

    bool appendKnownCategory(KNOWNDESTCATEGORY category)
    {
        if (!pDestList)
            return false;

        HRESULT hresult = pDestList->AppendKnownCategory(category);
        if (FAILED(hresult))
            warning("AppendKnownCategory", hresult);

        return SUCCEEDED(hresult);
    }

    void appendCategory()
    {
        IObjectCollection *collection = toComCollection(jumpListItems);
        if (collection) {
            wchar_t *title = qt_qstringToNullTerminated(currentlyBuiltCategoryTitle);
            pDestList->AppendCategory(title, collection);
            delete[] title;
            collection->Release();
        }
    }

    void appendTasks()
    {
        IObjectCollection *collection = toComCollection(jumpListItems);
        if (collection) {
            pDestList->AddUserTasks(collection);
            collection->Release();
        }
    }

    inline void clearItems()
    {
        isListBegan = false;
        qDeleteAll(jumpListItems);
        jumpListItems.clear();
    }

    static QList<QJumpListItem *> fromComCollection(IObjectArray *array)
    {
        QList<QJumpListItem *> list;
        UINT count = 0;
        array->GetCount(&count);
        for (unsigned i = 0; i < count; i++) {
            IUnknown *collectionItem = 0;
            HRESULT hresult = array->GetAt(i, IID_IUnknown, reinterpret_cast<void **>(collectionItem));
            if (FAILED(hresult))
                continue;
            IShellItem2 *shellItem = 0;
            IShellLinkW *shellLink = 0;
            QJumpListItem *jumplistItem = 0;
            if (SUCCEEDED(collectionItem->QueryInterface(IID_IShellItem2, reinterpret_cast<void **>(shellItem)))) {
                jumplistItem = fromIShellItem(shellItem);
                shellItem->Release();
            } else if (SUCCEEDED(collectionItem->QueryInterface(IID_IShellLinkW, reinterpret_cast<void **>(shellLink)))) {
                jumplistItem = fromIShellLink(shellLink);
                shellLink->Release();
            } else {
                qWarning("QJumpList: object of unexpected class found");
            }
            collectionItem->Release();
            if (jumplistItem)
                list.append(jumplistItem);
        }
        return list;
    }

    static IObjectCollection *toComCollection(const QList<QJumpListItem *> &list)
    {
        if (list.isEmpty())
            return 0;
        IObjectCollection *collection = 0;
        HRESULT hresult = CoCreateInstance(CLSID_EnumerableObjectCollection, 0, CLSCTX_INPROC_SERVER, IID_IObjectCollection, reinterpret_cast<void **>(&collection));
        if (FAILED(hresult)) {
            const QString err = QWinExtras::errorStringFromHresult(hresult);
            qWarning("QJumpList: failed to instantiate IObjectCollection: %#010x, %s.", (unsigned)hresult, qPrintable(err));
            return 0;
        }
        Q_FOREACH (QJumpListItem *item, list) {
            IUnknown *iitem = toICustomDestinationListItem(item);
            if (iitem) {
                collection->AddObject(iitem);
                iitem->Release();
            }
        }
        return collection;
    }

    static QJumpListItem *fromIShellLink(IShellLinkW *link)
    {
        QJumpListItem *item = new QJumpListItem(QJumpListItem::Link);

        IPropertyStore *linkProps;
        link->QueryInterface(IID_IPropertyStore, reinterpret_cast<void **>(&linkProps));
        PROPVARIANT var;
        linkProps->GetValue(PKEY_Link_Arguments, &var);
        item->setArguments(QStringList(QString::fromWCharArray(var.pwszVal)));
        PropVariantClear(&var);
        linkProps->Release();

        const int buffersize = 2048;
        wchar_t buffer[buffersize] = {0};

        link->GetDescription(buffer, INFOTIPSIZE);
        item->setDescription(QString::fromWCharArray(buffer));

        memset(buffer, 0, buffersize);
        int dummyindex;
        link->GetIconLocation(buffer, buffersize-1, &dummyindex);
        item->setIcon(QIcon(QString::fromWCharArray(buffer)));

        memset(buffer, 0, buffersize);
        link->GetPath(buffer, buffersize-1, 0, 0);
        item->setFilePath(QString::fromWCharArray(buffer));

        return item;
    }

    static QJumpListItem *fromIShellItem(IShellItem2 *shellitem)
    {
        QJumpListItem *item = new QJumpListItem(QJumpListItem::Destination);
        wchar_t *strPtr;
        shellitem->GetDisplayName(SIGDN_FILESYSPATH, &strPtr);
        item->setFilePath(QString::fromWCharArray(strPtr));
        CoTaskMemFree(strPtr);
        return item;
    }

    // partial copy of qprocess_win.cpp:qt_create_commandline()
    static QString createArguments(const QStringList &arguments)
    {
        QString args;
        for (int i=0; i<arguments.size(); ++i) {
            QString tmp = arguments.at(i);
            // Quotes are escaped and their preceding backslashes are doubled.
            tmp.replace(QRegExp(QLatin1String("(\\\\*)\"")), QLatin1String("\\1\\1\\\""));
            if (tmp.isEmpty() || tmp.contains(QLatin1Char(' ')) || tmp.contains(QLatin1Char('\t'))) {
                // The argument must not end with a \ since this would be interpreted
                // as escaping the quote -- rather put the \ behind the quote: e.g.
                // rather use "foo"\ than "foo\"
                int i = tmp.length();
                while (i > 0 && tmp.at(i - 1) == QLatin1Char('\\'))
                    --i;
                tmp.insert(i, QLatin1Char('"'));
                tmp.prepend(QLatin1Char('"'));
            }
            args += QLatin1Char(' ') + tmp;
        }
        return args;
    }

    static IUnknown *toICustomDestinationListItem(const QJumpListItem *item)
    {
        switch (item->type()) {
        case QJumpListItem::Destination :
            return toIShellItem(item);
        case QJumpListItem::Link :
            return toIShellLink(item);
        case QJumpListItem::Separator :
            return makeSeparatorShellItem();
        default:
            return 0;
        }
    }

    static IShellLinkW *toIShellLink(const QJumpListItem *item)
    {
        IShellLinkW *link = 0;
        HRESULT hresult = CoCreateInstance(CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER, IID_IShellLinkW, reinterpret_cast<void **>(&link));
        if (FAILED(hresult)) {
            const QString err = QWinExtras::errorStringFromHresult(hresult);
            qWarning("QJumpList: failed to instantiate IShellLinkW: %#010x, %s.", (unsigned)hresult, qPrintable(err));
            return 0;
        }

        const int iconPathSize = QJumpListPrivate::iconsDirPath().size() + sizeof(void *)*2 + 4; // path + ptr-name-in-hex + .ico
        const int bufferSize = qMax(item->workingDirectory().size(), qMax(item->description().size(), qMax(item->title().size(), qMax(item->filePath().size(), iconPathSize)))) + 1;
        wchar_t *buffer = new wchar_t[bufferSize];

        if (!item->description().isEmpty()) {
            qt_qstringToNullTerminated(item->description(), buffer);
            link->SetDescription(buffer);
        }

        qt_qstringToNullTerminated(item->filePath(), buffer);
        link->SetPath(buffer);

        if (!item->workingDirectory().isEmpty()) {
            qt_qstringToNullTerminated(item->workingDirectory(), buffer);
            link->SetWorkingDirectory(buffer);
        }

        QString args = createArguments(item->arguments());

        qt_qstringToNullTerminated(args, buffer);
        link->SetArguments(buffer);

        if (!item->icon().isNull()) {
            QString iconPath = QJumpListPrivate::iconsDirPath() + QString::number(reinterpret_cast<quintptr>(item), 16) + QLatin1String(".ico");
            bool iconSaved = item->icon().pixmap(GetSystemMetrics(SM_CXICON)).save(iconPath, "ico");
            if (iconSaved) {
                qt_qstringToNullTerminated(iconPath, buffer);
                link->SetIconLocation(buffer, 0);
            }
        }

        IPropertyStore *properties;
        PROPVARIANT titlepv;
        hresult = link->QueryInterface(IID_IPropertyStore, reinterpret_cast<void **>(&properties));
        if (FAILED(hresult)) {
            link->Release();
            return 0;
        }

        qt_qstringToNullTerminated(item->title(), buffer);
        InitPropVariantFromString(buffer, &titlepv);
        properties->SetValue(PKEY_Title, titlepv);
        properties->Commit();
        properties->Release();
        PropVariantClear(&titlepv);

        delete[] buffer;
        return link;
    }

    static IShellItem2 *toIShellItem(const QJumpListItem *item)
    {
        IShellItem2 *shellitem = 0;
        wchar_t *buffer = new wchar_t[item->filePath().length() + 1];
        qt_qstringToNullTerminated(item->filePath(), buffer);
        qt_SHCreateItemFromParsingName(buffer, 0, IID_IShellItem2, reinterpret_cast<void **>(&shellitem));
        delete[] buffer;
        return shellitem;
    }

    static IShellLinkW *makeSeparatorShellItem()
    {
        IShellLinkW *separator;
        HRESULT res = CoCreateInstance(CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER, IID_IShellLinkW, reinterpret_cast<void **>(&separator));
        if (FAILED(res))
            return 0;

        IPropertyStore *properties;
        res = separator->QueryInterface(IID_IPropertyStore, reinterpret_cast<void **>(&properties));
        if (FAILED(res)) {
            separator->Release();
            return 0;
        }

        PROPVARIANT isSeparator;
        InitPropVariantFromBoolean(TRUE, &isSeparator);
        properties->SetValue(PKEY_AppUserModel_IsDestListSeparator, isSeparator);
        properties->Commit();
        properties->Release();
        PropVariantClear(&isSeparator);

        return separator;
    }

    ICustomDestinationList *pDestList;
    bool isListBegan;
    bool showFrequentCategory;
    bool showRecentCategory;
    QString currentlyBuiltCategoryTitle;
    bool categoryBegan;
    bool tasksBegan;
    QList<QJumpListItem *> jumpListItems;
    UINT listSize;
};

/*!
    Constructs a QJumpList with the parent object \a parent.
 */
QJumpList::QJumpList(QObject *parent) :
    QObject(parent), d_ptr(new QJumpListPrivate)
{
    HRESULT hresult = CoCreateInstance(CLSID_DestinationList, 0, CLSCTX_INPROC_SERVER, IID_ICustomDestinationList, reinterpret_cast<void **>(&d_ptr->pDestList));
    if (FAILED(hresult))
        QJumpListPrivate::warning("CoCreateInstance", hresult);
}

/*!
    Destroys the QJumpList. If commit() or abort() were not called for the
    corresponding begin() call, building the Jump List is aborted.
 */
QJumpList::~QJumpList()
{
    Q_D(QJumpList);
    if (d->isListBegan)
        abort();
    if (d->pDestList)
        d->pDestList->Release();
}

/*!
    Initiates Jump List building.
    This method must be called before adding Jump List items.
    Returns true if successful; otherwise returns false.
 */
bool QJumpList::begin()
{
    Q_D(QJumpList);
    if (!d->pDestList)
        return false;

    UINT maxSlots;
    IUnknown *array;
    HRESULT hresult = d->pDestList->BeginList(&maxSlots, IID_IUnknown, reinterpret_cast<void **>(&array));
    if (SUCCEEDED(hresult)) {
        array->Release();
        d->isListBegan = true;
    } else {
        QJumpListPrivate::warning("BeginList", hresult);
    }
    return SUCCEEDED(hresult);
}

/*!
    Completes Jump List building, initiated by begin(), and displays it.
    Returns true if successful; otherwise returns false.
 */
bool QJumpList::commit()
{
    Q_D(QJumpList);
    if (!d->pDestList || !d->isListBegan)
        return false;

    if (d->showFrequentCategory)
        d->appendKnownCategory(KDC_FREQUENT);
    if (d->showRecentCategory)
        d->appendKnownCategory(KDC_RECENT);

    if (d->tasksBegan) {
        d->appendTasks();
    } else if (d->categoryBegan) {
        d->appendCategory();
    }

    d->clearItems();
    HRESULT hresult = d->pDestList->CommitList();
    if (FAILED(hresult))
        QJumpListPrivate::warning("CommitList", hresult);
    return SUCCEEDED(hresult);
}

/*!
    Aborts Jump List building initiated by begin() and leaves the currently
    active Jump List unchanged.
    Returns true if successful; otherwise returns false.
 */
bool QJumpList::abort()
{
    Q_D(QJumpList);
    if (!d->pDestList)
        return false;

    d->clearItems();
    HRESULT hresult = d->pDestList->AbortList();
    if (FAILED(hresult))
        QJumpListPrivate::warning("AbortList", hresult);
    return SUCCEEDED(hresult);
}

/*!
    Clears the application Jump List.
    Returns true if successful; otherwise returns false.
 */
bool QJumpList::clear()
{
    Q_D(QJumpList);
    if (!d->pDestList)
        return false;

    bool result;
    if (!d->isListBegan) {
        begin();
        result = commit();
    } else {
        result = abort() && clear() && begin();
    }
    return result;
}
/*!
    Specifies a unique AppUserModelID \a appId for the application whose custom
    Jump List will be built using this object.
    This is optional.
    This method must be called before begin().
    Returns true if successful; otherwise returns false.
*/
bool QJumpList::setApplicationId(const QString &appId)
{
    Q_D(QJumpList);
    if (!d->pDestList)
        return false;

    wchar_t *wcAppId = qt_qstringToNullTerminated(appId);
    HRESULT hresult = d->pDestList->SetAppID(wcAppId);
    delete[] wcAppId;
    if (FAILED(hresult))
        QJumpListPrivate::warning("SetAppID", hresult);
    return SUCCEEDED(hresult);
}

/*!
    Retrieves destinations that were removed by the user and must not be added
    again.
    Adding a group with removed destinations will fail.
 */
QList<QJumpListItem *> QJumpList::removedDestinations() const
{
    Q_D(const QJumpList);
    IObjectArray *array = 0;
    d->pDestList->GetRemovedDestinations(IID_IObjectArray, reinterpret_cast<void **>(&array));
    QList<QJumpListItem *> list = QJumpListPrivate::fromComCollection(array);
    array->Release();
    return list;
}

/*!
    Returns the number of items that the Jump List will display. This is
    configured by the user.
 */
int QJumpList::capacity() const
{
    Q_D(const QJumpList);
    return d->listSize;
}

/*!
    \property QJumpList::isRecentCategoryShown
    \brief whether to show the known Recent category

    The default value of this property is false.
    Changes to this property are applied only after commit() is called.
*/
void QJumpList::setRecentCategoryShown(bool show)
{
    Q_D(QJumpList);
    d->showRecentCategory = show;
}

bool QJumpList::isRecentCategoryShown() const
{
    Q_D(const QJumpList);
    return d->showRecentCategory;
}

/*!
    \property QJumpList::isFrequentCategoryShown
    \brief whether to show the known Frequent category

    The default value of this property is false.
    Changes to this property are applied only after commit() is called.
*/
void QJumpList::setFrequentCategoryShown(bool show)
{
    Q_D(QJumpList);
    d->showFrequentCategory = show;
}

bool QJumpList::isFrequentCategoryShown() const
{
    Q_D(const QJumpList);
    return d->showFrequentCategory;
}

/*!
    Declares the building of a custom category with the specified \a title.

    begin() must be called before calling this method.
 */
void QJumpList::beginCategory(const QString &title)
{
    Q_D(QJumpList);
    if (!d->pDestList)
        return;

    if (d->categoryBegan) {
        d->appendCategory();
    } else if (d->tasksBegan) {
        d->appendTasks();
    }
    d->currentlyBuiltCategoryTitle = title;
}

/*!
    Declares the building of a task list.

    begin() must be called before calling this method.
 */
void QJumpList::beginTasks()
{
    Q_D(QJumpList);
    if (!d->pDestList)
        return;

    if (d->categoryBegan) {
        d->appendCategory();
    }
    d->tasksBegan = true;
}

/*!
    Adds an \a item to the Jump List.

    beginCategory() or beginTasks() should be called before calling this method.
    Returns true if successful; otherwise returns false.
 */
bool QJumpList::addItem(QJumpListItem *item)
{
    Q_D(QJumpList);
    if (!d->pDestList || (!d->categoryBegan && !d->tasksBegan)) {
        return false;
    }

    d->jumpListItems.append(item);
    return true;
}

/*!
    Adds a destination to the Jump List pointing to \a filePath.

    beginCategory() or beginTasks() should be called before calling this method.
 */
void QJumpList::addDestination(const QString &filePath)
{
    Q_D(QJumpList);
    if (!d->pDestList || (!d->categoryBegan && !d->tasksBegan))
        return;

    QJumpListItem *item = new QJumpListItem(QJumpListItem::Destination);
    item->setFilePath(filePath);
    d->jumpListItems.append(item);
}

/*!
    \overload addLink()

    Adds a link to the Jump List using \a title, \a executablePath, and
    optionally \a arguments.

    beginCategory() or beginTasks() should be called before calling this method.
 */
void QJumpList::addLink(const QString &title, const QString &executablePath, const QStringList &arguments)
{
    addLink(QIcon(), title, QString(), QString(), executablePath, arguments);
}

/*!
    \overload addLink()

    Adds a link to the Jump List using \a title, \a description,
    \a executablePath, and optionally \a arguments.

    beginCategory() or beginTasks() should be called before calling this method.
 */
void QJumpList::addLink(const QString &title, const QString &description, const QString &executablePath, const QStringList &arguments)
{
    addLink(QIcon(), title, description, QString(), executablePath, arguments);
}

/*!
    \overload addLink()

    Adds a link to the Jump List using \a icon, \a title, \a executablePath, and
    optionally \a arguments.

    beginCategory() or beginTasks() should be called before calling this method.
 */
void QJumpList::addLink(const QIcon &icon, const QString &title, const QString &executablePath, const QStringList &arguments)
{
    addLink(icon, title, QString(), QString(), executablePath, arguments);
}

/*!
    \overload addLink()

    Adds a link to the Jump List using \a icon, \a title, \a description,
    \a executablePath, and optionally \a arguments.

    beginCategory() or beginTasks() should be called before calling this method.
 */
void QJumpList::addLink(const QIcon &icon, const QString &title, const QString &description, const QString &executablePath, const QStringList &arguments)
{
    addLink(icon, title, description, QString(), executablePath, arguments);
}

/*!
    Adds a link to the Jump List using \a icon, \a title, \a description,
    \a workingDirectory, \a executablePath, and \a arguments.

    beginCategory() or beginTasks() should be called before calling this method.
 */
void QJumpList::addLink(const QIcon &icon, const QString &title, const QString &description, const QString &workingDirectory, const QString &executablePath, const QStringList &arguments)
{
    Q_D(QJumpList);
    if (!d->pDestList || (!d->categoryBegan && !d->tasksBegan))
        return;

    QJumpListItem *item = new QJumpListItem(QJumpListItem::Link);
    item->setFilePath(executablePath);
    item->setTitle(title);
    item->setArguments(arguments);
    item->setDescription(description);
    item->setIcon(icon);
    item->setWorkingDirectory(workingDirectory);
    d->jumpListItems.append(item);
}

/*!
    Adds a separator to the Jump List.

    beginTasks() should be called before calling this method.
 */
void QJumpList::addSeparator()
{
    Q_D(QJumpList);
    if (!d->pDestList || (!d->categoryBegan && !d->tasksBegan))
        return;

    QJumpListItem *item = new QJumpListItem(QJumpListItem::Separator);
    d->jumpListItems.append(item);
}

QT_END_NAMESPACE
