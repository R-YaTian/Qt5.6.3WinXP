/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

import QtQuick 2.0
import QtQuick.Enterprise.VirtualKeyboard 2.0
import "content"

Rectangle {
    width: 1280
    height: 720
    color: "#F6F6F6"

    Flickable {
        id: flickable

        property real scrollMarginVertical: 20

        anchors.fill: parent
        contentWidth: content.width
        contentHeight: content.height
        interactive: contentHeight > height
        flickableDirection: Flickable.VerticalFlick
        children: ScrollBar {}

        MouseArea  {
            id: content

            width: flickable.width
            height: textEditors.height + 24

            onClicked: focus = true

            Column {
                id: textEditors
                spacing: 15
                x: 12; y: 12
                width: parent.width - 26

                Text {
                    color: "#565758"
                    text: "Tap fields to enter text"
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 22
                }
                TextField {
                    width: parent.width
                    previewText: "One line field"
                    enterKeyAction: EnterKeyAction.Next
                    onEnterKeyClicked: passwordField.focus = true
                }
                TextField {
                    id: passwordField

                    width: parent.width
                    echoMode: TextInput.Password
                    previewText: "Password field"
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhPreferLowercase | Qt.ImhSensitiveData | Qt.ImhNoPredictiveText
                    enterKeyAction: EnterKeyAction.Next
                    onEnterKeyClicked: upperCaseField.focus = true
                }
                TextField {
                    id: upperCaseField

                    width: parent.width
                    previewText: "Upper case field"
                    inputMethodHints: Qt.ImhUppercaseOnly
                    enterKeyAction: EnterKeyAction.Next
                    onEnterKeyClicked: lowerCaseField.focus = true
                }
                TextField {
                    id: lowerCaseField

                    width: parent.width
                    previewText: "Lower case field"
                    inputMethodHints: Qt.ImhLowercaseOnly
                    enterKeyAction: EnterKeyAction.Next
                    onEnterKeyClicked: phoneNumberField.focus = true
                }
                TextField {
                    id: phoneNumberField

                    validator: RegExpValidator { regExp: /^[0-9\+\-\#\*\ ]{6,}$/ }
                    width: parent.width
                    previewText: "Phone number field"
                    inputMethodHints: Qt.ImhDialableCharactersOnly
                    enterKeyAction: EnterKeyAction.Next
                    onEnterKeyClicked: formattedNumberField.focus = true
                }
                TextField {
                    id: formattedNumberField

                    width: parent.width
                    previewText: "Formatted number field"
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    enterKeyAction: EnterKeyAction.Next
                    onEnterKeyClicked: digitsField.focus = true
                }
                TextField {
                    id: digitsField

                    width: parent.width
                    previewText: "Digits only field"
                    inputMethodHints: Qt.ImhDigitsOnly
                    enterKeyAction: EnterKeyAction.Next
                    onEnterKeyClicked: textArea.focus = true
                }
                TextArea {
                    id: textArea

                    width: parent.width
                    previewText: "Multiple lines field"
                    height: Math.max(206, implicitHeight)
                }
            }
        }
    }
}
