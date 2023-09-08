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

#ifndef T9WRITEINPUTMETHOD_H
#define T9WRITEINPUTMETHOD_H

#include "abstractinputmethod.h"

namespace QtVirtualKeyboard {

class T9WriteInputMethodPrivate;

class T9WriteInputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(T9WriteInputMethod)

public:
    explicit T9WriteInputMethod(QObject *parent = 0);
    ~T9WriteInputMethod();

    QList<InputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, InputEngine::InputMode inputMode);
    bool setTextCase(InputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    void reset();
    void update();

    QList<SelectionListModel::Type> selectionLists();
    int selectionListItemCount(SelectionListModel::Type type);
    QVariant selectionListData(SelectionListModel::Type type, int index, int role);
    void selectionListItemSelected(SelectionListModel::Type type, int index);

    QList<InputEngine::PatternRecognitionMode> patternRecognitionModes() const;
    Trace *traceBegin(int traceId, InputEngine::PatternRecognitionMode patternRecognitionMode,
                      const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo);
    bool traceEnd(Trace *trace);

    bool reselect(int cursorPosition, const InputEngine::ReselectFlags &reselectFlags);

protected:
    void timerEvent(QTimerEvent *timerEvent);

protected slots:
    void dictionaryLoadCompleted(const QString &fileUri, void *dictionary);
    void resultsAvailable(const QVariantList &resultList);
};

}

#endif
