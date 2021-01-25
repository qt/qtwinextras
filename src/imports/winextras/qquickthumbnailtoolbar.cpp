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

#include "qquickthumbnailtoolbar_p.h"
#include "qquickthumbnailtoolbutton_p.h"
#include "qquickiconloader_p.h"

#include <QQuickWindow>
#include <QQmlEngine>

QT_BEGIN_NAMESPACE

/*!
    \qmltype ThumbnailToolBar
    \instantiates QQuickThumbnailToolBar
    \inqmlmodule QtWinExtras

    \brief Allows manipulating the window's thumbnail toolbar.

    This class allows an application to embed a toolbar in the thumbnail of a window,
    which is shown when hovering over its taskbar icon. It provides quick access to
    the window's commands without requiring the user to restore or activate the window.

    \image thumbbar.png Media player thumbnail toolbar

    \section3 Example
    \snippet code/thumbbar.qml thumbbar_qml
    \since QtWinExtras 1.0
 */

QQuickThumbnailToolBar::QQuickThumbnailToolBar(QQuickItem *parent) :
    QQuickItem(parent)
{
    connect(&m_toolbar, &QWinThumbnailToolBar::iconicThumbnailPixmapRequested,
            this, &QQuickThumbnailToolBar::iconicThumbnailRequested);
    connect(&m_toolbar, &QWinThumbnailToolBar::iconicLivePreviewPixmapRequested,
            this, &QQuickThumbnailToolBar::iconicLivePreviewRequested);
}

QQuickThumbnailToolBar::~QQuickThumbnailToolBar() = default;

int QQuickThumbnailToolBar::count() const
{
    return m_toolbar.count();
}

QQmlListProperty<QObject> QQuickThumbnailToolBar::data()
{
    return QQmlListProperty<QObject>(this, nullptr, &QQuickThumbnailToolBar::addData, nullptr, nullptr, nullptr);
}

QQmlListProperty<QQuickThumbnailToolButton> QQuickThumbnailToolBar::buttons()
{
    return QQmlListProperty<QQuickThumbnailToolButton>(this, nullptr, &QQuickThumbnailToolBar::buttonCount, &QQuickThumbnailToolBar::buttonAt);
}

void QQuickThumbnailToolBar::addButton(QQuickThumbnailToolButton *button)
{
    if (!m_buttons.contains(button)) {
        m_toolbar.addButton(button->m_button);
        m_buttons.append(button);
        emit countChanged();
        emit buttonsChanged();
    }
}

void QQuickThumbnailToolBar::removeButton(QQuickThumbnailToolButton *button)
{
    if (m_buttons.removeOne(button)) {
        m_toolbar.removeButton(button->m_button);
        emit countChanged();
        emit buttonsChanged();
    }
}

void QQuickThumbnailToolBar::clear()
{
    m_toolbar.clear();
    for (QQuickThumbnailToolButton *button : qAsConst(m_buttons))
        button->deleteLater();
    m_buttons.clear();
    emit countChanged();
    emit buttonsChanged();
}

/*!
    \qmlsignal ThumbnailToolBar::iconicThumbnailRequested()

    This signal is emitted when the operating system requests a new iconic thumbnail pixmap,
    typically when the thumbnail is shown.

    \since 5.4
*/

/*!
    \qmlsignal ThumbnailToolBar::iconicLivePreviewRequested()

    This signal is emitted when the operating system requests a new iconic live preview pixmap,
    typically when the user ALT-tabs to the application.
    \since 5.4
*/

/*!
    \qmlproperty bool ThumbnailToolBar::iconicNotificationsEnabled

    This property holds whether the signals iconicThumbnailRequested()
    or iconicLivePreviewRequested() will be emitted.
    \since 5.4
 */
bool QQuickThumbnailToolBar::iconicNotificationsEnabled() const
{
    return m_toolbar.iconicPixmapNotificationsEnabled();
}

void QQuickThumbnailToolBar::setIconicNotificationsEnabled(bool enabled)
{
    if (enabled != m_toolbar.iconicPixmapNotificationsEnabled()) {
        m_toolbar.setIconicPixmapNotificationsEnabled(enabled);
        emit iconicNotificationsEnabledChanged();
    }
}

void QQuickThumbnailToolBar::iconicThumbnailLoaded(const QVariant &value)
{
    m_toolbar.setIconicThumbnailPixmap(value.value<QPixmap>());
}

/*!
    \qmlproperty url ThumbnailToolBar::iconicThumbnailSource

    The pixmap for use as a thumbnail representation
    \since 5.4
 */
void QQuickThumbnailToolBar::setIconicThumbnailSource(const QUrl &source)
{
    if (source == m_iconicThumbnailSource)
        return;

    if (source.isEmpty()) {
         m_toolbar.setIconicThumbnailPixmap(QPixmap());
         m_iconicThumbnailSource = source;
         emit iconicThumbnailSourceChanged();
    }

    if (QQuickIconLoader::load(source, qmlEngine(this), QVariant::Pixmap, QSize(),
                               this, &QQuickThumbnailToolBar::iconicThumbnailLoaded) != QQuickIconLoader::LoadError) {
        m_iconicThumbnailSource = source;
        emit iconicThumbnailSourceChanged();
    }
}

void QQuickThumbnailToolBar::iconicLivePreviewLoaded(const QVariant &value)
{
    m_toolbar.setIconicLivePreviewPixmap(value.value<QPixmap>());
}

/*!
    \qmlproperty url ThumbnailToolBar::iconicLivePreviewSource

    The pixmap for use as a live (peek) preview when tabbing into the application.
    \since 5.4
 */
void QQuickThumbnailToolBar::setIconicLivePreviewSource(const QUrl &source)
{
    if (source == m_iconicLivePreviewSource)
        return;

    if (source.isEmpty()) {
         m_toolbar.setIconicLivePreviewPixmap(QPixmap());
         m_iconicLivePreviewSource = source;
         emit iconicLivePreviewSourceChanged();
    }

    if (QQuickIconLoader::load(source, qmlEngine(this), QVariant::Pixmap, QSize(),
                               this, &QQuickThumbnailToolBar::iconicLivePreviewLoaded) != QQuickIconLoader::LoadError) {
        m_iconicLivePreviewSource = source;
        emit iconicLivePreviewSourceChanged();
    }
}

void QQuickThumbnailToolBar::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    if (change == ItemSceneChange)
        m_toolbar.setWindow(data.window);
    QQuickItem::itemChange(change, data);
}

void QQuickThumbnailToolBar::addData(QQmlListProperty<QObject> *property, QObject *object)
{
    if (auto *button = qobject_cast<QQuickThumbnailToolButton *>(object)) {
        auto *quickThumbbar = static_cast<QQuickThumbnailToolBar *>(property->object);
        quickThumbbar->m_toolbar.addButton(button->m_button);
        quickThumbbar->m_buttons.append(button);
        emit quickThumbbar->countChanged();
        emit quickThumbbar->buttonsChanged();
    }
}

int QQuickThumbnailToolBar::buttonCount(QQmlListProperty<QQuickThumbnailToolButton> *property)
{
    return static_cast<QQuickThumbnailToolBar *>(property->object)->count();
}

QQuickThumbnailToolButton *QQuickThumbnailToolBar::buttonAt(QQmlListProperty<QQuickThumbnailToolButton> *property, int index)
{
    return static_cast<QQuickThumbnailToolBar *>(property->object)->m_buttons.value(index);
}

QT_END_NAMESPACE
