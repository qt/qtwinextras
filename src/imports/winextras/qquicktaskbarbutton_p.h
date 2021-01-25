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

#ifndef QQUICKTASKBARBUTTON_P_H
#define QQUICKTASKBARBUTTON_P_H

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
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>

QT_BEGIN_NAMESPACE

class QVariant;
class QQuickTaskbarButtonPrivate;

class QQuickTaskbarOverlay : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged)
    Q_PROPERTY(QString accessibleDescription READ accessibleDescription WRITE setAccessibleDescription NOTIFY accessibleDescriptionChanged)

public:
    explicit QQuickTaskbarOverlay(QWinTaskbarButton *button, QObject *parent = nullptr);

    QUrl iconSource() const;
    void setIconSource(const QUrl &iconSource);

    QString accessibleDescription() const;
    void setAccessibleDescription(const QString &description);

Q_SIGNALS:
    void iconSourceChanged();
    void accessibleDescriptionChanged();

private Q_SLOTS:
    void iconLoaded(const QVariant &);

private:
    QUrl m_iconSource;
    QWinTaskbarButton *m_button;
};

class QQuickTaskbarButton : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickTaskbarOverlay *overlay  READ overlay CONSTANT)
    Q_PROPERTY(QWinTaskbarProgress *progress READ progress CONSTANT)

public:
    explicit QQuickTaskbarButton(QQuickItem *parent = nullptr);
    ~QQuickTaskbarButton();

    QQuickTaskbarOverlay *overlay() const;
    QWinTaskbarProgress *progress() const;

protected:
    void itemChange(ItemChange, const ItemChangeData &) Q_DECL_OVERRIDE;

private:
    QWinTaskbarButton *m_button;
    QQuickTaskbarOverlay *m_overlay;
};

QT_END_NAMESPACE

#endif // QQUICKTASKBARBUTTON_P_H
