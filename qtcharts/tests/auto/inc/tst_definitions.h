/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
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

#ifndef TST_DEFINITIONS_H
#define TST_DEFINITIONS_H

#include <QtCharts/qpolarchart.h>
#include <QtTest/QtTest>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE
namespace QTest
{
    // This was deprecated in Qt5. This is a small hack for the sake of compatibility.
    inline static bool qWaitForWindowShown(QWidget *window)
    {
        return QTest::qWaitForWindowExposed(window);
    }
}
QT_END_NAMESPACE

#define TRY_COMPARE(actual, expected) { \
    do { \
        const int timeout(1000); \
        const int waitStep(30); \
        /* always wait before comparing to catch possible extra signals */ \
        QTest::qWait(waitStep); \
        for (int time(0); (actual != expected) && (time < timeout); time += waitStep) \
            QTest::qWait(waitStep); \
        QCOMPARE(actual, expected); \
    } while (0); \
}

// Some bamboo clients have trouble passing mouse events to the test application.
// This can be used to skip those tests so that they don't show up as a failure
// in the test report.
    #define SKIP_IF_CANNOT_TEST_MOUSE_EVENTS() { \
        do { \
            QPushButton b; \
            b.resize(120, 100); \
            b.show(); \
            QTest::qWaitForWindowShown(&b); \
            QSignalSpy spy(&b, SIGNAL(clicked())); \
            QTest::mouseClick(&b, Qt::LeftButton, 0, b.rect().center()); \
            QApplication::processEvents(); \
            if (spy.count() == 0) \
                QSKIP("Cannot test mouse events in this environment"); \
        } while (0); \
        QApplication::processEvents(); \
    }

    #define SKIP_ON_POLAR() { \
        if (isPolarTest()) \
            QSKIP("Test not supported by polar chart"); \
        }

    #define SKIP_ON_CARTESIAN() { \
        if (!isPolarTest()) \
            QSKIP("Test not supported by cartesian chart"); \
        }

// Synthetic mouse moves do not trigger hover events reliably in many virtual machines,
// so we skip tests involving mouse moves.
    #define SKIP_IF_FLAKY_MOUSE_MOVE() { \
        QSKIP("Skipping test with synthetic mouse moves."); \
    }

static inline bool isPolarTest()
{
    static bool isPolar = false;
    static bool polarEnvChecked = false;
    if (!polarEnvChecked) {
        isPolar = !(qgetenv("TEST_POLAR_CHART").isEmpty());
        polarEnvChecked = true;
        if (isPolar)
            qDebug() << "TEST_POLAR_CHART found -> Testing polar chart!";
    }
    return isPolar;
}

static inline QtCharts::QChart *newQChartOrQPolarChart()
{
    if (isPolarTest())
        return new QtCharts::QPolarChart();
    else
        return new QtCharts::QChart();
}



#endif // TST_DEFINITIONS_H
