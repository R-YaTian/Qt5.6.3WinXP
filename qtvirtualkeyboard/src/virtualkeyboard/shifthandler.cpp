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

#include "shifthandler.h"
#include "inputcontext.h"
#include "inputengine.h"
#include <QtCore/private/qobject_p.h>
#include <QSet>
#include <QGuiApplication>

namespace QtVirtualKeyboard {

class ShiftHandlerPrivate : public QObjectPrivate
{
public:
    ShiftHandlerPrivate() :
        QObjectPrivate(),
        inputContext(0),
        sentenceEndingCharacters(QString(".!?") + QChar(Qt::Key_exclamdown) + QChar(Qt::Key_questiondown)),
        autoCapitalizationEnabled(false),
        toggleShiftEnabled(false),
        shiftChanged(false),
        resetWhenVisible(false),
        manualShiftLanguageFilter(QSet<QLocale::Language>() << QLocale::Arabic << QLocale::Persian << QLocale::Hindi << QLocale::Korean),
        manualCapsInputModeFilter(QSet<InputEngine::InputMode>() << InputEngine::Cangjie << InputEngine::Zhuyin),
        noAutoUppercaseInputModeFilter(QSet<InputEngine::InputMode>() << InputEngine::FullwidthLatin << InputEngine::Pinyin << InputEngine::Cangjie << InputEngine::Zhuyin),
        allCapsInputModeFilter(QSet<InputEngine::InputMode>() << InputEngine::Hiragana << InputEngine::Katakana)
    {
    }

    InputContext *inputContext;
    QString sentenceEndingCharacters;
    bool autoCapitalizationEnabled;
    bool toggleShiftEnabled;
    bool shiftChanged;
    bool resetWhenVisible;
    QLocale locale;
    const QSet<QLocale::Language> manualShiftLanguageFilter;
    const QSet<InputEngine::InputMode> manualCapsInputModeFilter;
    const QSet<InputEngine::InputMode> noAutoUppercaseInputModeFilter;
    const QSet<InputEngine::InputMode> allCapsInputModeFilter;
};

/*!
    \qmltype ShiftHandler
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard
    \ingroup qtvirtualkeyboard-qml
    \instantiates QtVirtualKeyboard::ShiftHandler
    \brief Manages the shift state.
*/

/*!
    \class QtVirtualKeyboard::ShiftHandler
    \inmodule InputFramework
    \brief Manages the shift state.
*/

ShiftHandler::ShiftHandler(InputContext *parent) :
    QObject(*new ShiftHandlerPrivate(), parent)
{
    Q_D(ShiftHandler);
    d->inputContext = parent;
    if (d->inputContext) {
        connect(d->inputContext, SIGNAL(inputMethodHintsChanged()), SLOT(restart()));
        connect(d->inputContext, SIGNAL(inputItemChanged()), SLOT(restart()));
        connect(d->inputContext->inputEngine(), SIGNAL(inputModeChanged()), SLOT(restart()));
        connect(d->inputContext, SIGNAL(preeditTextChanged()), SLOT(autoCapitalize()));
        connect(d->inputContext, SIGNAL(surroundingTextChanged()), SLOT(autoCapitalize()));
        connect(d->inputContext, SIGNAL(cursorPositionChanged()), SLOT(autoCapitalize()));
        connect(d->inputContext, SIGNAL(shiftChanged()), SLOT(shiftChanged()));
        connect(d->inputContext, SIGNAL(capsLockChanged()), SLOT(shiftChanged()));
        connect(d->inputContext, SIGNAL(localeChanged()), SLOT(localeChanged()));
        connect(qGuiApp->inputMethod(), SIGNAL(visibleChanged()), SLOT(inputMethodVisibleChanged()));
        d->locale = QLocale(d->inputContext->locale());
    }
}

/*!
    \internal
*/
ShiftHandler::~ShiftHandler()
{

}

QString ShiftHandler::sentenceEndingCharacters() const
{
    Q_D(const ShiftHandler);
    return d->sentenceEndingCharacters;
}

void ShiftHandler::setSentenceEndingCharacters(const QString &value)
{
    Q_D(ShiftHandler);
    if (d->sentenceEndingCharacters != value) {
        d->sentenceEndingCharacters = value;
        autoCapitalize();
        emit sentenceEndingCharactersChanged();
    }
}

bool ShiftHandler::autoCapitalizationEnabled() const
{
    Q_D(const ShiftHandler);
    return d->autoCapitalizationEnabled;
}

bool ShiftHandler::toggleShiftEnabled() const
{
    Q_D(const ShiftHandler);
    return d->toggleShiftEnabled;
}

/*!
    \since 1.2

    \qmlmethod void ShiftHandler::toggleShift()

    Toggles the current shift state.

    This method provides the functionality of the shift key.

    \sa toggleShiftEnabled
*/
/*!
    \since 1.2

    \fn void QtVirtualKeyboard::ShiftHandler::toggleShift()

    Toggles the current shift state.

    This method provides the functionality of the shift key.

    \sa toggleShiftEnabled
*/
void ShiftHandler::toggleShift()
{
    Q_D(ShiftHandler);
    if (!d->toggleShiftEnabled)
        return;
    if (d->manualShiftLanguageFilter.contains(d->locale.language())) {
        d->inputContext->setCapsLock(false);
        d->inputContext->setShift(!d->inputContext->shift());
    } else if (d->inputContext->inputMethodHints() & Qt::ImhNoAutoUppercase ||
               d->manualCapsInputModeFilter.contains(d->inputContext->inputEngine()->inputMode())) {
        bool capsLock = d->inputContext->capsLock();
        d->inputContext->setCapsLock(!capsLock);
        d->inputContext->setShift(!capsLock);
    } else {
        d->inputContext->setCapsLock(!d->inputContext->capsLock() && d->inputContext->shift() && !d->shiftChanged);
        d->inputContext->setShift(d->inputContext->capsLock() || !d->inputContext->shift());
        d->shiftChanged = false;
    }
}

void ShiftHandler::reset()
{
    Q_D(ShiftHandler);
    if (d->inputContext->inputItem()) {
        Qt::InputMethodHints inputMethodHints = d->inputContext->inputMethodHints();
        InputEngine::InputMode inputMode = d->inputContext->inputEngine()->inputMode();
        bool preferUpperCase = (inputMethodHints & (Qt::ImhPreferUppercase | Qt::ImhUppercaseOnly));
        bool autoCapitalizationEnabled = !(d->inputContext->inputMethodHints() & (Qt::ImhNoAutoUppercase |
              Qt::ImhUppercaseOnly | Qt::ImhLowercaseOnly | Qt::ImhEmailCharactersOnly |
              Qt::ImhUrlCharactersOnly | Qt::ImhDialableCharactersOnly | Qt::ImhFormattedNumbersOnly |
              Qt::ImhDigitsOnly)) && !d->noAutoUppercaseInputModeFilter.contains(inputMode);
        bool toggleShiftEnabled = !(inputMethodHints & (Qt::ImhUppercaseOnly | Qt::ImhLowercaseOnly));
        // For filtered languages reset the initial shift status to lower case
        // and allow manual shift change
        if (d->manualShiftLanguageFilter.contains(d->locale.language()) ||
                d->manualCapsInputModeFilter.contains(inputMode)) {
            preferUpperCase = false;
            autoCapitalizationEnabled = false;
            toggleShiftEnabled = true;
        } else if (d->allCapsInputModeFilter.contains(inputMode)) {
            preferUpperCase = true;
            autoCapitalizationEnabled = false;
            toggleShiftEnabled = false;
        }
        setToggleShiftEnabled(toggleShiftEnabled);
        setAutoCapitalizationEnabled(autoCapitalizationEnabled);
        d->inputContext->setCapsLock(preferUpperCase);
        if (preferUpperCase)
            d->inputContext->setShift(preferUpperCase);
        else
            autoCapitalize();
    }
}

void ShiftHandler::autoCapitalize()
{
    Q_D(ShiftHandler);
    if (d->inputContext->capsLock())
        return;
    if (!d->autoCapitalizationEnabled || !d->inputContext->preeditText().isEmpty()) {
        d->inputContext->setShift(false);
    } else {
        int cursorPosition = d->inputContext->cursorPosition();
        bool preferLowerCase = d->inputContext->inputMethodHints() & Qt::ImhPreferLowercase;
        if (cursorPosition == 0) {
            d->inputContext->setShift(!preferLowerCase);
        } else {
            QString text = d->inputContext->surroundingText();
            text.truncate(cursorPosition);
            text = text.trimmed();
            if (text.length() == 0)
                d->inputContext->setShift(!preferLowerCase);
            else if (text.length() > 0 && d->sentenceEndingCharacters.indexOf(text[text.length() - 1]) >= 0)
                d->inputContext->setShift(!preferLowerCase);
            else
                d->inputContext->setShift(false);
        }
    }
}

void ShiftHandler::restart()
{
    Q_D(ShiftHandler);
    if (!qGuiApp->inputMethod()->isVisible()) {
        d->resetWhenVisible = true;
        return;
    }
    reset();
}

void ShiftHandler::shiftChanged()
{
    Q_D(ShiftHandler);
    d->shiftChanged = true;
}

void ShiftHandler::localeChanged()
{
    Q_D(ShiftHandler);
    d->locale = QLocale(d->inputContext->locale());
    restart();
}

void ShiftHandler::inputMethodVisibleChanged()
{
    Q_D(ShiftHandler);
    if (d->resetWhenVisible && qGuiApp->inputMethod()->isVisible()) {
        d->resetWhenVisible = false;
        reset();
    }
}

void ShiftHandler::setAutoCapitalizationEnabled(bool enabled)
{
    Q_D(ShiftHandler);
    if (d->autoCapitalizationEnabled != enabled) {
        d->autoCapitalizationEnabled = enabled;
        emit autoCapitalizationEnabledChanged();
    }
}

void ShiftHandler::setToggleShiftEnabled(bool enabled)
{
    Q_D(ShiftHandler);
    if (d->toggleShiftEnabled != enabled) {
        d->toggleShiftEnabled = enabled;
        emit toggleShiftEnabledChanged();
    }
}

/*!
    \property QtVirtualKeyboard::ShiftHandler::sentenceEndingCharacters

    This property specifies the sentence ending characters which
    will cause shift state change.

    By default, the property is initialized to sentence
    ending characters found in the ASCII range (i.e. ".!?").
*/

/*!
    \qmlproperty string ShiftHandler::sentenceEndingCharacters

    This property specifies the sentence ending characters which
    will cause shift state change.

    By default, the property is initialized to sentence
    ending characters found in the ASCII range (i.e. ".!?").
*/

/*!
    \since 1.2

    \property QtVirtualKeyboard::ShiftHandler::autoCapitalizationEnabled

    This property provides the current state of the automatic
    capitalization feature.
*/

/*!
    \since 1.2

    \qmlproperty bool ShiftHandler::autoCapitalizationEnabled

    This property provides the current state of the automatic
    capitalization feature.
*/

/*!
    \since 1.2

    \property QtVirtualKeyboard::ShiftHandler::toggleShiftEnabled

    This property provides the current state of the toggleShift()
    method. When true, the current shift state can be changed by
    calling the toggleShift() method.
*/

/*!
    \since 1.2

    \qmlproperty bool ShiftHandler::toggleShiftEnabled

    This property provides the current state of the toggleShift()
    method. When true, the current shift state can be changed by
    calling the toggleShift() method.
*/

} // namespace QtVirtualKeyboard
