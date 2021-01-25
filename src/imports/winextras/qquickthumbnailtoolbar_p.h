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

#ifndef QQUICKTHUMBNAILTOOLBAR_P_H
#define QQUICKTHUMBNAILTOOLBAR_P_H

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

#include <QQuickItem>
#include <QWinThumbnailToolBar>
#include <QUrl>
#include <QVector>

QT_BEGIN_NAMESPACE

class QVariant;

class QQuickThumbnailToolButton;

class QQuickThumbnailToolBar : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QQmlListProperty<QObject> data READ data)
    Q_PROPERTY(QQmlListProperty<QQuickThumbnailToolButton> buttons READ buttons NOTIFY buttonsChanged)
    Q_PROPERTY(bool iconicNotificationsEnabled READ iconicNotificationsEnabled WRITE setIconicNotificationsEnabled NOTIFY iconicNotificationsEnabledChanged)
    Q_PROPERTY(QUrl iconicThumbnailSource READ iconicThumbnailSource WRITE setIconicThumbnailSource NOTIFY iconicThumbnailSourceChanged)
    Q_PROPERTY(QUrl iconicLivePreviewSource READ iconicLivePreviewSource WRITE setIconicLivePreviewSource NOTIFY iconicLivePreviewSourceChanged)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit QQuickThumbnailToolBar(QQuickItem *parent = nullptr);
    ~QQuickThumbnailToolBar();

    int count() const;

    QQmlListProperty<QObject> data();
    QQmlListProperty<QQuickThumbnailToolButton> buttons();

    Q_INVOKABLE void addButton(QQuickThumbnailToolButton *button);
    Q_INVOKABLE void removeButton(QQuickThumbnailToolButton *button);

    bool iconicNotificationsEnabled() const;
    void setIconicNotificationsEnabled(bool);
    QUrl iconicThumbnailSource() const { return m_iconicThumbnailSource; }
    void setIconicThumbnailSource(const QUrl &);
    QUrl iconicLivePreviewSource() const { return m_iconicLivePreviewSource; }
    void setIconicLivePreviewSource(const QUrl &);

public Q_SLOTS:
    void clear();

Q_SIGNALS:
    void countChanged();
    void buttonsChanged();
    void iconicNotificationsEnabledChanged();
    void iconicThumbnailSourceChanged();
    void iconicThumbnailRequested();
    void iconicLivePreviewSourceChanged();
    void iconicLivePreviewRequested();

private Q_SLOTS:
    void iconicThumbnailLoaded(const QVariant &);
    void iconicLivePreviewLoaded(const QVariant &);

protected:
    void itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data) override;

private:
    static void addData(QQmlListProperty<QObject> *property, QObject *button);
    static int buttonCount(QQmlListProperty<QQuickThumbnailToolButton> *property);
    static QQuickThumbnailToolButton *buttonAt(QQmlListProperty<QQuickThumbnailToolButton> *property, int index);

    QWinThumbnailToolBar m_toolbar;
    QVector<QQuickThumbnailToolButton *> m_buttons;
    QUrl m_iconicThumbnailSource;
    QUrl m_iconicLivePreviewSource;
};

QT_END_NAMESPACE

#endif // QQUICKTHUMBNAILTOOLBAR_P_H
