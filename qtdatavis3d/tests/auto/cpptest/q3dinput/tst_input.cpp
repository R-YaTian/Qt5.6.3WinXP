/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module.
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

#include <QtTest/QtTest>

#include <QtDataVisualization/Q3DInputHandler>

using namespace QtDataVisualization;

class tst_input: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void construct();

    void initialProperties();
    void initializeProperties();

private:
    Q3DInputHandler *m_input;
};

void tst_input::initTestCase()
{
}

void tst_input::cleanupTestCase()
{
}

void tst_input::init()
{
    m_input = new Q3DInputHandler();
}

void tst_input::cleanup()
{
    delete m_input;
}

void tst_input::construct()
{
    Q3DInputHandler *input = new Q3DInputHandler();
    QVERIFY(input);
    delete input;
}

void tst_input::initialProperties()
{
    QVERIFY(m_input);

    QCOMPARE(m_input->isRotationEnabled(), true);
    QCOMPARE(m_input->isSelectionEnabled(), true);
    QCOMPARE(m_input->isZoomAtTargetEnabled(), true);
    QCOMPARE(m_input->isZoomEnabled(), true);

    // Common (from QAbstract3DInputHandler)
    QCOMPARE(m_input->inputPosition(), QPoint(0, 0));
    QCOMPARE(m_input->inputView(), QAbstract3DInputHandler::InputViewNone);
    QVERIFY(!m_input->scene());
}

void tst_input::initializeProperties()
{
    QVERIFY(m_input);

    m_input->setRotationEnabled(false);
    m_input->setSelectionEnabled(false);
    m_input->setZoomAtTargetEnabled(false);
    m_input->setZoomEnabled(false);

    QCOMPARE(m_input->isRotationEnabled(), false);
    QCOMPARE(m_input->isSelectionEnabled(), false);
    QCOMPARE(m_input->isZoomAtTargetEnabled(), false);
    QCOMPARE(m_input->isZoomEnabled(), false);

    // Common (from QAbstract3DInputHandler)
    m_input->setInputPosition(QPoint(100, 100));
    m_input->setInputView(QAbstract3DInputHandler::InputViewOnPrimary);

    QCOMPARE(m_input->inputPosition(), QPoint(100, 100));
    QCOMPARE(m_input->inputView(), QAbstract3DInputHandler::InputViewOnPrimary);
}

// TODO: QTRD-3380 (mouse events)

QTEST_MAIN(tst_input)
#include "tst_input.moc"
