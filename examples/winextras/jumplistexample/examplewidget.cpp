/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of QtWinExtras in the Qt Toolkit.
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

#include <QApplication>
#include <QStyle>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QJumpList>
#include <QJumpListItem>
#include <QDebug>

ExampleWidget::ExampleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExampleWidget)
{
    ui->setupUi(this);

    if (QCoreApplication::arguments().contains("-text"))
        ui->text->setPlainText("Hello, world!");
    if (!QCoreApplication::arguments().contains("-fullscreen"))
        ui->btnClose->hide();

    for (int i = 1; i < QCoreApplication::arguments().size(); i++) {
        const QString arg = QCoreApplication::arguments().at(i);
        if (!arg.isEmpty() && arg.at(0) != '-' && QFile(arg).exists()) {
            showFile(arg);
            break;
        }
    }

    connect(ui->btnUpdate,   SIGNAL(clicked()), SLOT(updateJumpList()));
    connect(ui->btnOpenFile, SIGNAL(clicked()), SLOT(openFile()));
    connect(ui->btnClose, SIGNAL(clicked()), qApp, SLOT(quit()));
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

void ExampleWidget::showFile(const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        ui->text->setPlainText(QString::fromUtf8(file.readAll()));
    else
        QMessageBox::warning(this, "Error", "Failed to open file");
}

void ExampleWidget::updateJumpList()
{
    QJumpList jumplist;
    jumplist.begin();
    if (ui->cbShowFrequent->isChecked())
        jumplist.setFrequentCategoryShown(true);
    if (ui->cbShowRecent->isChecked())
        jumplist.setRecentCategoryShown(true);
    jumplist.beginTasks();
    if (ui->cbRunFullscreen->isChecked()) {
        QJumpListItem *item = new QJumpListItem(QJumpListItem::Link);
        item->setTitle(ui->cbRunFullscreen->text());
        item->setFilePath(QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
        item->setArguments(QStringList("-fullscreen"));
        item->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
        jumplist.addItem(item);
    }
    if (ui->cbRunFusion->isChecked()) {
        jumplist.addLink(style()->standardIcon(QStyle::SP_DesktopIcon), ui->cbRunFusion->text(), QDir::toNativeSeparators(QCoreApplication::applicationFilePath()), (QStringList() << "-style" << "fusion"));
    }
    if (ui->cbRunText->isChecked()) {
        jumplist.addSeparator();
        jumplist.addLink(ui->cbRunText->text(), QDir::toNativeSeparators(QCoreApplication::applicationFilePath()), QStringList("-text"));
    }
    jumplist.commit();
}

void ExampleWidget::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open a text file", QString(), "Text files (*.txt)");
    if (filePath.isEmpty())
        return;
    else
        showFile(filePath);
}
