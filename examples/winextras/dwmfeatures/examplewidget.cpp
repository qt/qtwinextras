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

#include "examplewidget.h"
#include "ui_examplewidget.h"

#include <QWinFunctions>
#include <QWinEvent>
#include <QDebug>
#include <qt_windows.h>

ExampleWidget::ExampleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExampleWidget)
{
    ui->setupUi(this);

    connect(ui->btnPeekDisallow, SIGNAL(clicked()), SLOT(onDisallowPeekClicked()));
    connect(ui->btnPeekExclude,  SIGNAL(clicked()), SLOT(onExcludeFromPeekClicked()));
    connect(ui->radioFlipDefault, SIGNAL(clicked()), SLOT(onFlip3DPolicyChanged()));
    connect(ui->radioFlipAbove,   SIGNAL(clicked()), SLOT(onFlip3DPolicyChanged()));
    connect(ui->radioFlipBelow,   SIGNAL(clicked()), SLOT(onFlip3DPolicyChanged()));
    connect(ui->btnFrameReset, SIGNAL(clicked()), SLOT(onResetGlassFrameClicked()));
    connect(ui->frameTop,    SIGNAL(valueChanged(int)), SLOT(onGlassMarginsChanged()));
    connect(ui->frameRight,  SIGNAL(valueChanged(int)), SLOT(onGlassMarginsChanged()));
    connect(ui->frameBottom, SIGNAL(valueChanged(int)), SLOT(onGlassMarginsChanged()));
    connect(ui->frameLeft,   SIGNAL(valueChanged(int)), SLOT(onGlassMarginsChanged()));
}

ExampleWidget::~ExampleWidget()
{
    delete ui;
}

void ExampleWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool ExampleWidget::event(QEvent *e)
{
    if (e->type() == QWinEvent::CompositionChange) {
        QWinCompositionChangeEvent *event = static_cast<QWinCompositionChangeEvent *>(e);
        qDebug() << "Composition state change: " << event->isCompositionEnabled();
    } else if (e->type() == QWinEvent::ThemeChange) {
        qDebug() << "Theme change.";
    }
    return QWidget::event(e);
}

void ExampleWidget::onDisallowPeekClicked()
{
    QtWinExtras::setWindowDisallowPeek(this, ui->btnPeekDisallow->isChecked());
}

void ExampleWidget::onExcludeFromPeekClicked()
{
    QtWinExtras::setWindowExcludedFromPeek(this, ui->btnPeekExclude->isChecked());
}

void ExampleWidget::onFlip3DPolicyChanged()
{
    QtWinExtras::WindowFlip3DPolicy policy;
    if (ui->radioFlipAbove->isChecked())
        policy = QtWinExtras::FlipExcludeAbove;
    else if (ui->radioFlipBelow->isChecked())
        policy = QtWinExtras::FlipExcludeBelow;
    else
        policy = QtWinExtras::FlipDefault;
    QtWinExtras::setWindowFlip3DPolicy(this, policy);
}

void ExampleWidget::onGlassMarginsChanged()
{
    if (!QtWinExtras::isCompositionEnabled())
        return;

    // what you see here is the only way to force widget to redraw itself
    // so it actually redraws itself without caching and without any glitch
    // but causes flickering :(
    // and yes, update() and redraw() do nothing

    if (!testAttribute(Qt::WA_NoSystemBackground)) {

        QSize original = size();
        QSize modified = original;
        modified.setWidth(original.height() + 1);
        resize(modified);

        setAttribute(Qt::WA_NoSystemBackground);
        QtWinExtras::extendFrameIntoClientArea(this,
                                         ui->frameTop->value(),
                                         ui->frameRight->value(),
                                         ui->frameBottom->value(),
                                         ui->frameLeft->value());

        resize(original);

        ui->groupBox_2->setAutoFillBackground(true);
        ui->groupBox_3->setAutoFillBackground(true);
        ui->groupBox_4->setAutoFillBackground(true);
    } else {
        QtWinExtras::extendFrameIntoClientArea(this,
                                         ui->frameLeft->value(),
                                         ui->frameTop->value(),
                                         ui->frameRight->value(),
                                         ui->frameBottom->value());
    }
}

void ExampleWidget::onResetGlassFrameClicked()
{
    if (!testAttribute(Qt::WA_NoSystemBackground))
        return;

    ui->frameTop->setValue(0);
    ui->frameRight->setValue(0);
    ui->frameBottom->setValue(0);
    ui->frameLeft->setValue(0);

    QtWinExtras::resetExtendedFrame(this);
    setAttribute(Qt::WA_NoSystemBackground, false);

    QSize original = size();
    QSize modified = original;
    modified.setHeight(original.height() + 1);
    resize(modified);

    ui->groupBox_2->setAutoFillBackground(false);
    ui->groupBox_3->setAutoFillBackground(false);
    ui->groupBox_4->setAutoFillBackground(false);

    resize(original);
}
