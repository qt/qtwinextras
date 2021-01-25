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
    \qmltype JumpListDestination
    \inherits JumpListItem
    \inqmlmodule QtWinExtras

    \brief Represents a file that can be edited or viewed by an application.

    \since QtWinExtras 1.0

    The JumpListDestination type contains a path to a file that users can select
    from a Jump List to view or edit it with an application.

 */

JumpListItem {
    __jumpListItemType: JumpListItem.ItemTypeDestination

    /*!
        \qmlproperty string JumpListDestination::filePath

        The path to the file.
     */
    property string filePath
}
