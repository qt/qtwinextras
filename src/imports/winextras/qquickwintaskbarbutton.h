/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the QtWinExtras module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Digia.  For licensing terms and
 ** conditions see http://qt.digia.com/licensing.  For further information
 ** use the contact form at http://qt.digia.com/contact-us.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Digia gives you certain additional
 ** rights.  These rights are described in the Digia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#ifndef QQUICKWINTASKBARBUTTON_H
#define QQUICKWINTASKBARBUTTON_H

#include <QQuickItem>
#include <QWinTaskbarButton>

QT_BEGIN_NAMESPACE

class QQuickWinTaskbarButtonPrivate;

class QQuickWinTaskbarButton : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int progressMinimum READ progressMinimum WRITE setProgressMinimum)
    Q_PROPERTY(int progressMaximum READ progressMaximum WRITE setProgressMaximum)
    Q_PROPERTY(int progressValue   READ progressValue   WRITE setProgressValue)
    Q_PROPERTY(QString overlayIcon READ overlayIcon WRITE setOverlayIcon)
    Q_PROPERTY(QString iconDescription READ iconDescription WRITE setIconDescription)
    Q_PROPERTY(QWinTaskbarButton::ProgressState progressState READ progressState WRITE setProgressState)

public:
    Q_ENUMS(QWinTaskbarButton::ProgressState)

    QQuickWinTaskbarButton(QQuickItem *parent = 0);
    ~QQuickWinTaskbarButton();
    int progressMinimum() const;
    void setProgressMinimum(int min);
    int progressMaximum() const;
    void setProgressMaximum(int max);
    int progressValue() const;
    void setProgressValue(int progress);
    QString overlayIcon() const;
    void setOverlayIcon(const QString &path);
    QString iconDescription() const;
    void setIconDescription(const QString &descr);

    QWinTaskbarButton::ProgressState progressState() const;
    void setProgressState(QWinTaskbarButton::ProgressState state);

protected:
    void itemChange(ItemChange, const ItemChangeData &) Q_DECL_OVERRIDE;

private:
    QWinTaskbarButton *button;
    QString m_iconPath;
    QString m_iconDescription;
};

QT_END_NAMESPACE

#endif // QQUICKWINTASKBARBUTTON_H
