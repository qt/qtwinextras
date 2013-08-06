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

#ifndef QQUICKWINDWMFEATURES_H
#define QQUICKWINDWMFEATURES_H

#include <QQuickItem>
#include <QWinFunctions>

QT_BEGIN_NAMESPACE

class QQuickWinDwmFeaturesPrivate;

class QQuickWinDwmFeatures : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool isCompositionEnabled READ isCompositionEnabled WRITE setCompositionEnabled NOTIFY isCompositionEnabledChanged)
    Q_PROPERTY(QColor colorizationColor READ colorizationColor NOTIFY colorizationColorChanged)
    Q_PROPERTY(QColor realColorizationColor READ realColorizationColor NOTIFY realColorizationColorChanged)
    Q_PROPERTY(bool colorizationOpaqueBlend READ colorizationOpaqueBlend NOTIFY colorizationOpaqueBlendChanged)
    Q_PROPERTY(int topGlassMargin    READ topGlassMargin    WRITE setTopGlassMargin)
    Q_PROPERTY(int rightGlassMargin  READ rightGlassMargin  WRITE setRightGlassMargin)
    Q_PROPERTY(int bottomGlassMargin READ bottomGlassMargin WRITE setBottomGlassMargin)
    Q_PROPERTY(int leftGlassMargin   READ leftGlassMargin   WRITE setLeftGlassMargin)
    Q_PROPERTY(bool excludedFromPeek READ excludedFromPeek WRITE setExcludedFromPeek)
    Q_PROPERTY(bool peekDisallowed   READ peekDisallowed   WRITE setPeekDisallowed)
    Q_PROPERTY(Flip3DPolicy flip3DPolicy READ flip3DPolicy WRITE setFlip3DPolicy)

public:
    enum Flip3DPolicy // keep sync with Qt::WindowFlip3DPolicy
    {
        FlipDefault,
        FlipExcludeBelow,
        FlipExcludeAbove
    };

    Q_ENUMS(Flip3DPolicy)

    explicit QQuickWinDwmFeatures(QQuickItem *parent = 0);
    ~QQuickWinDwmFeatures();

    void setCompositionEnabled(bool enabled);
    bool isCompositionEnabled() const;
    QColor colorizationColor() const;
    QColor realColorizationColor() const;
    bool colorizationOpaqueBlend() const;

    void setTopGlassMargin(int margin);
    void setRightGlassMargin(int margin);
    void setBottomGlassMargin(int margin);
    void setLeftGlassMargin(int margin);
    int topGlassMargin() const;
    int rightGlassMargin() const;
    int bottomGlassMargin() const;
    int leftGlassMargin() const;

    bool excludedFromPeek() const;
    void setExcludedFromPeek(bool exclude);
    bool peekDisallowed() const;
    void setPeekDisallowed(bool disallow);
    Flip3DPolicy flip3DPolicy() const;
    void setFlip3DPolicy(Flip3DPolicy policy);

    bool eventFilter(QObject *, QEvent *) Q_DECL_OVERRIDE;

    static QQuickWinDwmFeatures *qmlAttachedProperties(QObject *object);

Q_SIGNALS:
    void colorizationColorChanged();
    void realColorizationColorChanged();
    void isCompositionEnabledChanged();
    void colorizationOpaqueBlendChanged();

protected:
    void itemChange(ItemChange, const ItemChangeData &) Q_DECL_OVERRIDE;

private:
    QScopedPointer<QQuickWinDwmFeaturesPrivate> d_ptr;

    Q_DECLARE_PRIVATE(QQuickWinDwmFeatures)
};

QML_DECLARE_TYPEINFO(QQuickWinDwmFeatures, QML_HAS_ATTACHED_PROPERTIES)

QT_END_NAMESPACE

#endif // QQUICKWINDWMFEATURES_H
