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
    \qmltype JumpListLink
    \inherits JumpListItem
    \inqmlmodule QtWinExtras

    \brief Represents a command to execute an application.

    \since QtWinExtras 1.0

    The JumpListLink type represents a command to execute an application.

 */

JumpListItem {
    __jumpListItemType: JumpListItem.ItemTypeLink

    /*!
        \qmlproperty string JumpListLink::iconPath

        The path to a link icon.
     */
    property string iconPath

    /*!
        \qmlproperty string JumpListLink::executablePath

        The path to an executable file.
     */
    property string executablePath

    /*!
        \qmlproperty string JumpListLink::arguments

        Command-line arguments.
     */
    property string arguments

    /*!
        \qmlproperty string JumpListLink::description

        The description of the link.
     */
    property string description

    /*!
        \qmlproperty string JumpListLink::title

        The title of the link.
     */
    property string title
}
