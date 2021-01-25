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

#ifndef QWINTHUMBNAILTOOLBAR_H
#define QWINTHUMBNAILTOOLBAR_H

#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QPixmap;
class QWindow;
class QWinThumbnailToolButton;
class QWinThumbnailToolBarPrivate;

class Q_WINEXTRAS_EXPORT QWinThumbnailToolBar : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count STORED false)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow)
    Q_PROPERTY(bool iconicPixmapNotificationsEnabled READ iconicPixmapNotificationsEnabled WRITE setIconicPixmapNotificationsEnabled)
    Q_PROPERTY(QPixmap iconicThumbnailPixmap READ iconicThumbnailPixmap WRITE setIconicThumbnailPixmap)
    Q_PROPERTY(QPixmap iconicLivePreviewPixmap READ iconicLivePreviewPixmap WRITE setIconicLivePreviewPixmap)

public:
    explicit QWinThumbnailToolBar(QObject *parent = nullptr);
    ~QWinThumbnailToolBar();

    void setWindow(QWindow *window);
    QWindow *window() const;

    void addButton(QWinThumbnailToolButton *button);
    void removeButton(QWinThumbnailToolButton *button);
    void setButtons(const QList<QWinThumbnailToolButton *> &buttons);
    QList<QWinThumbnailToolButton *> buttons() const;
    int count() const;

    bool iconicPixmapNotificationsEnabled() const;
    void setIconicPixmapNotificationsEnabled(bool enabled);

    QPixmap iconicThumbnailPixmap() const;
    QPixmap iconicLivePreviewPixmap() const;

public Q_SLOTS:
    void clear();
    void setIconicThumbnailPixmap(const QPixmap &);
    void setIconicLivePreviewPixmap(const QPixmap &);

Q_SIGNALS:
    void iconicThumbnailPixmapRequested();
    void iconicLivePreviewPixmapRequested();

private:
    Q_DISABLE_COPY(QWinThumbnailToolBar)
    Q_DECLARE_PRIVATE(QWinThumbnailToolBar)
    QScopedPointer<QWinThumbnailToolBarPrivate> d_ptr;
    friend class QWinThumbnailToolButton;
};

QT_END_NAMESPACE

#endif // QWINTHUMBNAILTOOLBAR_H
