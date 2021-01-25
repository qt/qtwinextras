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

#include "qquickjumplistitem_p.h"
#include <QVariant>

QT_BEGIN_NAMESPACE

QQuickJumpListItem::QQuickJumpListItem(QObject *parent) :
    QObject(parent)
{
}

QQuickJumpListItem::~QQuickJumpListItem() = default;

int QQuickJumpListItem::type() const
{
    return m_type;
}

void QQuickJumpListItem::setType(int type)
{
    m_type = type;
}

QWinJumpListItem *QQuickJumpListItem::toJumpListItem() const
{
    auto *item = new QWinJumpListItem(QWinJumpListItem::Separator);
    switch (m_type) {
    case ItemTypeDestination:
        item->setType(QWinJumpListItem::Destination);
        item->setFilePath(property("filePath").toString());
        break;
    case ItemTypeLink:
        item->setType(QWinJumpListItem::Link);
        item->setFilePath(property("executablePath").toString());
        item->setArguments(QStringList(property("arguments").toStringList()));
        item->setDescription(property("description").toString());
        item->setTitle(property("title").toString());
        item->setIcon(QIcon(property("iconPath").toString()));
        break;
    }

    return item;
}

QT_END_NAMESPACE
