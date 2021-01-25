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

#ifndef QQUICKJUMPLISTITEM_P_H
#define QQUICKJUMPLISTITEM_P_H

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

#include <QObject>
#include <QWinJumpListItem>

QT_BEGIN_NAMESPACE

class QQuickJumpListItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int __jumpListItemType READ type WRITE setType)
public:
    enum JumpListItemType {
        ItemTypeLink = 1,
        ItemTypeDestination = 2,
        ItemTypeSeparator = 3
    };
    Q_ENUM(JumpListItemType)

    explicit QQuickJumpListItem(QObject *p = nullptr);
    ~QQuickJumpListItem();

    int type() const;
    void setType(int type);

    QWinJumpListItem *toJumpListItem() const;

private:
    int m_type; // 1 - link, 2 - destination
};

QT_END_NAMESPACE

#endif // QQUICKJUMPLISTITEM_P_H
