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

KeyboardLayout {
    inputMode: InputEngine.Latin
    keyWeight: 160
    KeyboardRow {
        Key {
            key: 0x0419
            text: "й"
        }
        Key {
            key: 0x0426
            text: "ц"
        }
        Key {
            key: 0x0423
            text: "у"
        }
        Key {
            key: 0x041A
            text: "к"
        }
        Key {
            key: 0x0415
            text: "е"
            alternativeKeys: "её"
        }
        Key {
            key: 0x041D
            text: "н"
        }
        Key {
            key: 0x0413
            text: "г"
        }
        Key {
            key: 0x0428
            text: "ш"
        }
        Key {
            key: 0x0429
            text: "щ"
        }
        Key {
            key: 0x0417
            text: "з"
        }
        Key {
            key: 0x0425
            text: "х"
        }
        BackspaceKey {
            weight: 180
        }
    }
    KeyboardRow {
        FillerKey {
            weight: 40
        }
        Key {
            key: 0x0424
            text: "ф"
        }
        Key {
            key: 0x042B
            text: "ы"
        }
        Key {
            key: 0x0412
            text: "в"
        }
        Key {
            key: 0x0410
            text: "а"
        }
        Key {
            key: 0x041F
            text: "п"
        }
        Key {
            key: 0x0420
            text: "р"
        }
        Key {
            key: 0x041E
            text: "о"
        }
        Key {
            key: 0x041B
            text: "л"
        }
        Key {
            key: 0x0414
            text: "д"
        }
        Key {
            key: 0x0416
            text: "ж"
        }
        Key {
            key: 0x042D
            text: "э"
        }
        EnterKey {
            weight: 280
        }
    }
    KeyboardRow {
        ShiftKey { }
        Key {
            key: 0x042F
            text: "я"
        }
        Key {
            key: 0x0427
            text: "ч"
        }
        Key {
            key: 0x0421
            text: "с"
        }
        Key {
            key: 0x041C
            text: "м"
        }
        Key {
            key: 0x0418
            text: "и"
        }
        Key {
            key: 0x0422
            text: "т"
        }
        Key {
            key: 0x042C
            text: "ь"
            alternativeKeys: "ьъ"
        }
        Key {
            key: 0x0411
            text: "б"
        }
        Key {
            key: 0x042E
            text: "ю"
        }
        Key {
            key: Qt.Key_Minus
            text: "-"
            alternativeKeys: "—"
        }
        ShiftKey {
            weight: 272
        }
    }
    KeyboardRow {
        keyWeight: 154
        SymbolModeKey {
            weight: 217
        }
        ChangeLanguageKey {
            weight: 154
        }
        HandwritingModeKey {
            weight: 154
        }
        SpaceKey {
            weight: 864
        }
        Key {
            key: Qt.Key_Period
            text: "."
            alternativeKeys: ";:!?,."
        }
        Key {
            key: 0xE000
            text: ":-)"
            alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
        }
        HideKeyboardKey {
            weight: 204
        }
    }
}
