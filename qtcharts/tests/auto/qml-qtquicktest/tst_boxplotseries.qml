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

import QtQuick 2.0
import QtTest 1.0
import QtCharts 2.1

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest BoxPlotSeries"
        when: windowShown

        function test_properties() {
            compare(boxPlotSeries.boxWidth, 0.5);
            compare(boxPlotSeries.brushFilename, "");
        }

        function test_setproperties() {
            var set = boxPlotSeries.append("boxplot", [1, 2, 5, 6, 8]);
            compare(set.label, "boxplot");
            compare(set.count, 5);
            compare(set.brushFilename, "");
        }

        function test_append() {
            boxPlotSeries.clear();
            addedSpy.clear();
            countChangedSpy.clear();
            var count = 50;
            for (var i = 0; i < count; i++)
                boxPlotSeries.append("boxplot" + i, Math.random());
            compare(addedSpy.count, count);
            compare(countChangedSpy.count, count);
            compare(boxPlotSeries.count, count)
            boxPlotSeries.clear();
        }

        function test_remove() {
            boxPlotSeries.clear();
            removedSpy.clear();
            countChangedSpy.clear();
            var count = 50;
            for (var i = 0; i < count; i++)
                boxPlotSeries.append("boxplot" + i, Math.random());
            for (var j = 0; j < count; j++)
                boxPlotSeries.remove(boxPlotSeries.at(0));
            compare(removedSpy.count, count);
            compare(countChangedSpy.count, 2 * count);
            compare(boxPlotSeries.count, 0)
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent

        BoxPlotSeries {
            id: boxPlotSeries
            name: "boxplot"
            BoxSet { label: "Jan"; values: [3, 4, 5.1, 6.2, 8.5] }

            SignalSpy {
                id: addedSpy
                target: boxPlotSeries
                signalName: "boxsetsAdded"
            }
            SignalSpy {
                id: removedSpy
                target: boxPlotSeries
                signalName: "boxsetsRemoved"
            }
            SignalSpy {
                id: countChangedSpy
                target: boxPlotSeries
                signalName: "countChanged"
            }
        }
    }
}
