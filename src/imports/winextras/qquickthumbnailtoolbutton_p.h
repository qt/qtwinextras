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

#ifndef QQUICKTHUMBNAILTOOLBUTTON_P_H
#define QQUICKTHUMBNAILTOOLBUTTON_P_H

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

QT_BEGIN_NAMESPACE

class QQuickThumbnailToolButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged)
    Q_PROPERTY(QString tooltip READ tooltip WRITE setTooltip NOTIFY tooltipChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool interactive READ isInteractive WRITE setInteractive NOTIFY interactiveChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool dismissOnClick READ dismissOnClick WRITE setDismissOnClick NOTIFY dismissOnClickChanged)
    Q_PROPERTY(bool flat READ isFlat WRITE setFlat NOTIFY flatChanged)

public:
    explicit QQuickThumbnailToolButton(QObject *parent = nullptr);
    ~QQuickThumbnailToolButton();

    void setIconSource(const QUrl &iconSource);
    QUrl iconSource();
    void setTooltip(const QString &tooltip);
    QString tooltip() const;
    void setEnabled(bool isEnabled);
    bool isEnabled() const;
    void setInteractive(bool isInteractive);
    bool isInteractive() const;
    void setVisible(bool isVisible);
    bool isVisible() const;
    void setDismissOnClick(bool dismiss);
    bool dismissOnClick() const;
    void setFlat(bool flat);
    bool isFlat() const;

Q_SIGNALS:
    void clicked();
    void iconSourceChanged();
    void tooltipChanged();
    void enabledChanged();
    void interactiveChanged();
    void visibleChanged();
    void dismissOnClickChanged();
    void flatChanged();

private Q_SLOTS:
    void iconLoaded(const QVariant &);

private:
    QUrl m_iconSource;
    QWinThumbnailToolButton *m_button;

    friend class QQuickThumbnailToolBar;
};

QT_END_NAMESPACE

#endif // QQUICKTHUMBNAILTOOLBUTTON_P_H
