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

#ifndef QWINTASKBARBUTTON_H
#define QWINTASKBARBUTTON_H

#include <QtCore/qobject.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QWindow;
class QWinTaskbarButtonPrivate;

class Q_WINEXTRAS_EXPORT QWinTaskbarButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QIcon overlayIcon READ overlayIcon WRITE setOverlayIcon)
    Q_PROPERTY(QString overlayIconAccessibilityDescription READ overlayIconAccessibilityDescription WRITE setOverlayIconAccessibilityDescription)
    Q_PROPERTY(int progressValue READ progressValue WRITE setProgressValue)
    Q_PROPERTY(int progressMaximum READ progressMaximum WRITE setProgressMaximum)
    Q_PROPERTY(int progressMinimum READ progressMinimum WRITE setProgressMinimum)
    Q_PROPERTY(ProgressState progressState READ progressState WRITE setProgressState)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow)

public:
    enum ProgressState {
        NoProgressState,
        IndeterminateState,
        NormalState,
        PausedState,
        ErrorState
    };

    Q_ENUMS(ProgressState)

    explicit QWinTaskbarButton(QObject *parent = 0);
    ~QWinTaskbarButton();

    void setWindow(QWindow *window);
    QWindow *window() const;

    QIcon overlayIcon() const;
    QString overlayIconAccessibilityDescription() const;

    ProgressState progressState() const;
    int progressValue() const;
    int progressMinimum() const;
    int progressMaximum() const;

    bool eventFilter(QObject *, QEvent *);

public Q_SLOTS:
    void setOverlayIcon(const QIcon &icon);
    void setOverlayIconAccessibilityDescription(const QString &description);

    void clearOverlayIcon();

    void setProgressState(ProgressState state);
    void setProgressValue(int progress);
    void setProgressMinimum(int min);
    void setProgressMaximum(int max);
    void setProgressRange(int mininum, int progressMaximum);
    void resetProgress();

Q_SIGNALS:
    void progressStateChanged(const ProgressState state);
    void progressValueChanged(int value);

private:
    QScopedPointer<QWinTaskbarButtonPrivate> d_ptr;

    friend class QQuickWinTaskbarButton;

    Q_DECLARE_PRIVATE(QWinTaskbarButton)
};

QT_END_NAMESPACE

#endif // QWINTASKBARBUTTON_H
