/****************************************************************************
 **
 ** Copyright (C) 2016 Ivan Vizir <define-true-false@yandex.com>
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

import QtWinExtras 1.0

/*!
    \qmltype JumpListSeparator
    \inherits JumpListItem
    \inqmlmodule QtWinExtras

    \brief Represents a task list separator.

    \since QtWinExtras 1.0

    The JumpListSeparator type represents a separator in a Jump List. This value
    is used only for task lists.
 */

JumpListItem {
    __jumpListItemType: JumpListItem.ItemTypeSeparator
}
