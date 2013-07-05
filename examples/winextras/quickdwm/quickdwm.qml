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

import QtQuick 2.0
import QtWinExtras 1.0
import QtQuick.Window 2.1

Rectangle {
    width: 300
    height: 130
    color: "transparent"

    WinDwmFeatures {
        id: dwmfeatures
        bottomGlassMargin: isCompositionEnabled ? 30 : 0
        excludedFromPeek: true
        flip3DPolicy: WinDwmFeatures.FlipExcludeAbove
    }

    WinTaskbarButton {
        progressState: WinTaskbarButton.IndeterminateState
        overlayIcon: "icon.png"
    }

    Window {
        height: 128
        width: 256
        maximumHeight: height
        minimumHeight: height
        maximumWidth: width
        minimumWidth: width
        visible: true
        title: "Sheet of glass"

        WinDwmFeatures {
            bottomGlassMargin: isCompositionEnabled ? -1 : 0
        }
    }

    Rectangle {
        id: contentRect
        anchors.fill: parent
        anchors.bottomMargin: dwmfeatures.bottomGlassMargin

        Rectangle {
            id: rectColorization
            color: WinDwmFeatures.colorizationColor
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 32

            Text {
                text: "Colorization color"
                anchors.centerIn: parent
                font.pointSize: 12
            }
        }

        Rectangle {
            id: rectRealColorization
            color: WinDwmFeatures.realColorizationColor
            anchors.top: rectColorization.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: rectColorization.height

            Text {
                text: "Real colorization color"
                anchors.centerIn: parent
                font.pointSize: 12
            }
        }

        Rectangle {
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: rectRealColorization.bottom
            height: rectRealColorization.height
            color: (function () {
                if (!mouseComposition.containsMouse)
                    return "#D7D7D7";
                else if (mouseComposition.containsMouse && !mouseComposition.pressedButtons)
                    return "#D7E0E7";
                else
                    return "#EEEEF7"
            })()

            Text {
                anchors.centerIn: parent
                text: "DWM composition is " + (WinDwmFeatures.isCompositionEnabled ? "enabled" : "disabled")
                font.pointSize: 12
            }

            MouseArea {
                id: mouseComposition
                anchors.fill: parent
                hoverEnabled: true
                onClicked: WinDwmFeatures.isCompositionEnabled = !WinDwmFeatures.isCompositionEnabled
            }
        }
    }

    Rectangle {
        id: transparentBottom
        color: WinDwmFeatures.isCompositionEnabled ? "transparent" : "#EEE"
        height: dwmfeatures.bottomGlassMargin
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            id: textOnGlass
            anchors.centerIn: parent
            text: "Text on glass" + (WinDwmFeatures.isCompositionEnabled ? "" : " (potentially)")
            font.pointSize: 12
        }
    }
}
