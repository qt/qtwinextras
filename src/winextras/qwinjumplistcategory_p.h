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

#ifndef QWINJUMPLISTCATEGORY_P_H
#define QWINJUMPLISTCATEGORY_P_H

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

#include "qwinjumplistcategory.h"

QT_BEGIN_NAMESPACE

class QWinJumpList;

class QWinJumpListCategoryPrivate
{
public:
    static QWinJumpListCategoryPrivate *get(QWinJumpListCategory *category)
    {
        return category->d_func();
    }

    static QWinJumpListCategory *create(QWinJumpListCategory::Type type, QWinJumpList *jumpList);

    void invalidate();
    void loadRecents();
    void addRecent(QWinJumpListItem *item);
    void clearRecents();

    bool visible = false;
    QString title;
    QWinJumpList *jumpList = nullptr;
    QWinJumpListCategory::Type type = QWinJumpListCategory::Custom;
    QList<QWinJumpListItem *> items;
};

QT_END_NAMESPACE

#endif // QWINJUMPLISTCATEGORY_P_H
