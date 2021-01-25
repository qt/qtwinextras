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

#ifndef QWINJUMPLIST_P_H
#define QWINJUMPLIST_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qwinjumplist.h"
#include "winshobjidl_p.h"

QT_BEGIN_NAMESPACE

class QWinJumpListPrivate
{
    Q_DECLARE_PUBLIC(QWinJumpList)

public:
    static QWinJumpListPrivate *get(QWinJumpList *list)
    {
        return list->d_func();
    }

    static void warning(const char *function, HRESULT hresult);
    static QString iconsDirPath();

    void invalidate();
    void _q_rebuild();
    void destroy();

    bool beginList();
    bool commitList();

    void appendKnownCategory(KNOWNDESTCATEGORY category);
    void appendCustomCategory(QWinJumpListCategory *category);
    void appendTasks(const QList<QWinJumpListItem *> &items);

    static QList<QWinJumpListItem *> fromComCollection(IObjectArray *array);
    static IObjectCollection *toComCollection(const QList<QWinJumpListItem *> &list);
    static QWinJumpListItem *fromIShellLink(IShellLinkW *link);
    static QWinJumpListItem *fromIShellItem(IShellItem2 *shellitem);
    static IUnknown *toICustomDestinationListItem(const QWinJumpListItem *item);
    static IShellLinkW *toIShellLink(const QWinJumpListItem *item);
    static IShellItem2 *toIShellItem(const QWinJumpListItem *item);
    static IShellLinkW *makeSeparatorShellItem();

    QWinJumpList *q_ptr = nullptr;
    ICustomDestinationList *pDestList = nullptr;
    QWinJumpListCategory *recent = nullptr;
    QWinJumpListCategory *frequent = nullptr;
    QWinJumpListCategory *tasks = nullptr;
    QList<QWinJumpListCategory *> categories;
    QString identifier;
    bool dirty = false;
};

QT_END_NAMESPACE

#endif // QWINJUMPLIST_P_H
