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

#ifndef QWINTHUMBNAILTOOLBUTTON_H
#define QWINTHUMBNAILTOOLBUTTON_H

#include <QtGui/qicon.h>
#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QWinThumbnailToolButtonPrivate;

class Q_WINEXTRAS_EXPORT QWinThumbnailToolButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString toolTip READ toolTip WRITE setToolTip)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
    Q_PROPERTY(bool interactive READ isInteractive WRITE setInteractive)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
    Q_PROPERTY(bool dismissOnClick READ dismissOnClick WRITE setDismissOnClick)
    Q_PROPERTY(bool flat READ isFlat WRITE setFlat)

public:
    explicit QWinThumbnailToolButton(QObject *parent = nullptr);
    ~QWinThumbnailToolButton();

    void setToolTip(const QString &toolTip);
    QString toolTip() const;
    void setIcon(const QIcon &icon);
    QIcon icon() const;
    void setEnabled(bool enabled);
    bool isEnabled() const;
    void setInteractive(bool interactive);
    bool isInteractive() const;
    void setVisible(bool visible);
    bool isVisible() const;
    void setDismissOnClick(bool dismiss);
    bool dismissOnClick() const;
    void setFlat(bool flat);
    bool isFlat() const;

public Q_SLOTS:
    void click();

Q_SIGNALS:
    void clicked();
    void changed();

private:
    Q_DISABLE_COPY(QWinThumbnailToolButton)
    Q_DECLARE_PRIVATE(QWinThumbnailToolButton)
    QScopedPointer<QWinThumbnailToolButtonPrivate> d_ptr;
    friend class QWinThumbnailToolBar;
};

QT_END_NAMESPACE

#endif // QWINTHUMBNAILTOOLBUTTON_H
