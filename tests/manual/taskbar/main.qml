/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
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
import QtQuick 2.1
import QtWinExtras 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

ApplicationWindow {
    id: window

    title: "TaskbarButton"

    width: column.implicitWidth + 240
    height: column.implicitHeight + 160
    minimumWidth: column.implicitWidth + 40
    minimumHeight: column.implicitHeight + 40

    TaskbarButton {
        id: taskbar

        progress.visible: progressBox.checked
        progress.minimum: minSpinBox.value
        progress.maximum: maxSpinBox.value
        progress.value: valueSlider.value

        overlayIcon: overlayBox.checked && overlayCombo.currentIndex >= 0 ? overlayModel.get(overlayCombo.currentIndex).source : ""
    }

    ColumnLayout {
        id: column

        spacing: 20
        anchors.centerIn: parent
        Layout.preferredWidth: window.width / 2

        GroupBox {
            id: overlayBox

            checked: false
            checkable: true
            title: "Overlay icon"
            Layout.fillWidth: true

            ComboBox {
                id: overlayCombo

                anchors.fill: parent
                anchors.margins: 10

                textRole: "name"
                model: ListModel {
                    id: overlayModel
                    ListElement { name: "Qt logo (64)"; source: ":/qt-project.org/qmessagebox/images/qtlogo-64.png" }
                    ListElement { name: "Up (16)"; source: ":/qt-project.org/styles/commonstyle/images/up-16.png" }
                    ListElement { name: "Left (32)"; source: ":/qt-project.org/styles/commonstyle/images/left-32.png" }
                    ListElement { name: "Right (32)"; source: ":/qt-project.org/styles/commonstyle/images/right-32.png" }
                    ListElement { name: "Down (128)"; source: ":/qt-project.org/styles/commonstyle/images/down-128.png" }
                    ListElement { name: "Non-existing"; source: "do not crash explorer" }
                }
            }
        }

        GroupBox {
            id: progressBox

            checked: false
            checkable: true
            title: qsTr("Progress (%1)").arg(taskbar.progress.value)
            Layout.fillWidth: true

            GridLayout {
                columns: 5
                rowSpacing: 10
                columnSpacing: 20
                anchors.fill: parent
                anchors.margins: 10

                Label { text: "Value:" }
                Slider {
                    id: valueSlider

                    value: 50
                    stepSize: 1
                    minimumValue: minSpinBox.value
                    maximumValue: maxSpinBox.value
                    Layout.columnSpan: 3
                }

                Button {
                    readonly property string playText: "\u25BA" // BLACK RIGHT-POINTING POINTER
                    readonly property string pauseText: "\u25AE\u25AE" // BLACK VERTICAL RECTANGLE

                    text: taskbar.progress.paused ? playText : pauseText
                    onClicked: taskbar.progress.paused ? taskbar.progress.resume() : taskbar.progress.pause()
                    Layout.fillHeight: true
                    Layout.rowSpan: 2
                }

                Label { text: "Minimum:" }
                SpinBox {
                    id: minSpinBox

                    value: 0
                    stepSize: 1
                    minimumValue: -1000
                    maximumValue: 1000
                    Layout.fillWidth: true
                }

                Label { text: "Maximum:" }
                SpinBox {
                    id: maxSpinBox

                    value: 100
                    stepSize: 1
                    minimumValue: -1000
                    maximumValue: 1000
                    Layout.fillWidth: true
                }
            }
        }
    }
}
