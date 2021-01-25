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

#ifndef QWINTHUMBNAILTOOLBAR_P_H
#define QWINTHUMBNAILTOOLBAR_P_H

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

#include "qwinthumbnailtoolbar.h"

#include <QtCore/qhash.h>
#include <QtCore/qlist.h>
#include <QtGui/qicon.h>
#include <QtGui/qpixmap.h>
#include <QtCore/qabstractnativeeventfilter.h>

#include "winshobjidl_p.h"

QT_BEGIN_NAMESPACE

class QWinThumbnailToolBarPrivate : public QObject, QAbstractNativeEventFilter
{
public:
    class IconicPixmapCache
    {
    public:
        IconicPixmapCache() = default;
        ~IconicPixmapCache() { deleteBitmap(); }

        operator bool() const { return !m_pixmap.isNull(); }

        QPixmap pixmap() const { return m_pixmap; }
        bool setPixmap(const QPixmap &p);

        HBITMAP bitmap(const QSize &maxSize);

    private:
        void deleteBitmap();

        QPixmap m_pixmap;
        QSize m_size;
        HBITMAP m_bitmap = nullptr;
    };

    QWinThumbnailToolBarPrivate();
    ~QWinThumbnailToolBarPrivate();
    void initToolbar();
    void clearToolbar();
    void _q_updateToolbar();
    void _q_scheduleUpdate();
    bool eventFilter(QObject *, QEvent *) Q_DECL_OVERRIDE;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;
#else
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;
#endif

    static void initButtons(THUMBBUTTON *buttons);
    static int makeNativeButtonFlags(const QWinThumbnailToolButton *button);
    static int makeButtonMask(const QWinThumbnailToolButton *button);
    static QString msgComFailed(const char *function, HRESULT hresult);

    bool updateScheduled = false;
    QList<QWinThumbnailToolButton *> buttonList;
    QWindow *window = nullptr;
    ITaskbarList4 * const pTbList;

    IconicPixmapCache iconicThumbnail;
    IconicPixmapCache iconicLivePreview;

private:
    bool hasHandle() const;
    HWND handle() const;
    void updateIconicPixmapsEnabled(bool invalidate);
    void updateIconicThumbnail(const MSG *message);
    void updateIconicLivePreview(const MSG *message);

    QWinThumbnailToolBar *q_ptr = nullptr;
    Q_DECLARE_PUBLIC(QWinThumbnailToolBar)
    bool withinIconicThumbnailRequest = false;
    bool withinIconicLivePreviewRequest = false;
};

QT_END_NAMESPACE

#endif // QWINTHUMBNAILTOOLBAR_P_H
