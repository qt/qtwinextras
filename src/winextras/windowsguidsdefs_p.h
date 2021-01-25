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

#ifndef WINDOWSGUIDSDEFS_P_H
#define WINDOWSGUIDSDEFS_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of QtWinExtras. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qglobal.h>
#include <QtCore/qt_windows.h>

QT_BEGIN_NAMESPACE

extern const GUID qCLSID_DestinationList;
extern const GUID qCLSID_EnumerableObjectCollection;
extern const GUID qIID_ICustomDestinationList;
extern const GUID qIID_IApplicationDestinations;
extern const GUID qCLSID_ApplicationDestinations;
extern const GUID qIID_IApplicationDocumentLists;
extern const GUID qCLSID_ApplicationDocumentLists;
extern const GUID qIID_IObjectArray;
extern const GUID qIID_IObjectCollection;
extern const GUID qIID_IPropertyStore;
extern const GUID qIID_ITaskbarList3;
extern const GUID qIID_ITaskbarList4;
extern const GUID qIID_IShellItem2;
extern const GUID qIID_IShellLinkW;
extern const GUID qIID_ITaskbarList;
extern const GUID qIID_ITaskbarList2;
extern const GUID qIID_IUnknown;
extern const GUID qGUID_NULL;

QT_END_NAMESPACE

#endif // WINDOWSGUIDSDEFS_P_H
