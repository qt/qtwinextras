/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWinExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWin>

#include <QGuiApplication>
#include <QScopedArrayPointer>
#include <QStringList>
#include <QPixmap>
#include <QImage>
#include <QFileInfo>
#include <QDir>
#include <iostream>

/* This example demonstrates the Windows-specific image conversion
 * functions. */

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QStringList arguments = QCoreApplication::arguments();
    arguments.pop_front();
    const bool large = !arguments.isEmpty() && arguments.front() == "-l";
    if (large)
        arguments.pop_front();
    if (arguments.size() < 1) {
        std::cout << "Usage: iconextractor [OPTIONS] FILE [IMAGE_FILE_FOLDER]\n\n"
                     "Extracts Windows icons from executables, DLL or icon files\n"
                     "and writes them out as numbered .png-files.\n\n"
                     "Options: -l    Extract large icons.\n\n"
                     "Based on Qt " << QT_VERSION_STR << "\n";
        return 1;
    }
    const QString sourceFile = arguments.at(0);
    QString imageFileRoot = arguments.size() > 1 ? arguments.at(1) : QDir::currentPath();
    const QFileInfo imageFileRootInfo(imageFileRoot);
    if (!imageFileRootInfo.isDir()) {
        std::cerr << imageFileRoot.toStdString() << " is not a directory.\n";
        return 1;
    }

    const UINT iconCount = ExtractIconEx((wchar_t *)sourceFile.utf16(), -1, 0, 0, 0);
    if (!iconCount) {
        std::cerr << sourceFile.toStdString() << " does not appear to contain icons.\n";
        return 1;
    }

    QScopedArrayPointer<HICON> icons(new HICON[iconCount]);
    const UINT extractedIconCount = large ?
        ExtractIconEx((wchar_t *)sourceFile.utf16(), 0, icons.data(), 0, iconCount) :
        ExtractIconEx((wchar_t *)sourceFile.utf16(), 0, 0, icons.data(), iconCount);
    if (!extractedIconCount) {
        qErrnoWarning("Failed to extract icons from %s", qPrintable(sourceFile));
        return 1;
    }

    std::cout << sourceFile.toStdString() << " contains " << extractedIconCount << " icon(s).\n";

    imageFileRoot = imageFileRootInfo.absoluteFilePath() + QLatin1Char('/') + QFileInfo(sourceFile).baseName();
    for (UINT i = 0; i < extractedIconCount; ++i) {
        const QPixmap pixmap = QtWin::fromHICON(icons[i]);
        if (pixmap.isNull()) {
            std::cerr << "Error converting icons.\n";
            return 1;
        }
        const QString fileName = QString::fromLatin1("%1%2.png").arg(imageFileRoot)
            .arg(i, 3, 10, QLatin1Char('0'));
        if (!pixmap.save(fileName)) {
            std::cerr << "Error writing image file " << fileName.toStdString() << ".\n";
            return 1;
        }
        std::cout << "Wrote image file "
                  << QDir::toNativeSeparators(fileName).toStdString() << ".\n";
    }
    return 0;
}
