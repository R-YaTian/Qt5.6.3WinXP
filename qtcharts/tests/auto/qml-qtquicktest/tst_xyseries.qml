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
        name: "tst_qml-qtquicktest XY Series"
        when: windowShown

        function test_properties() {
            verify(lineSeries.color != undefined);
            compare(lineSeries.pointsVisible, false);
            compare(lineSeries.capStyle, Qt.SquareCap);
            compare(lineSeries.style, Qt.SolidLine);
            compare(lineSeries.width, 2.0);

            verify(splineSeries.color != undefined);
            compare(splineSeries.pointsVisible, false);
            compare(splineSeries.capStyle, Qt.SquareCap);
            compare(splineSeries.style, Qt.SolidLine);
            compare(splineSeries.width, 2.0);

            verify(scatterSeries.color != undefined);
            verify(scatterSeries.borderColor != undefined);
            compare(scatterSeries.borderWidth, 2.0);
            compare(scatterSeries.markerShape, ScatterSeries.MarkerShapeCircle);
            compare(scatterSeries.markerSize, 15.0);
            compare(scatterSeries.brushFilename, "");

            verify(areaSeries.color != undefined);
            verify(areaSeries.borderColor != undefined);
            compare(areaSeries.borderWidth, 2.0);
            compare(areaSeries.brushFilename, "");
        }

        function test_axes() {
            // Axis initialization
            compare(chartView.axisX(), lineSeries.axisX);
            compare(chartView.axisY(), lineSeries.axisY);
            compare(lineSeries.axisX, splineSeries.axisX);
            compare(lineSeries.axisY, splineSeries.axisY);
            compare(lineSeries.axisX, areaSeries.axisX);
            compare(lineSeries.axisY, areaSeries.axisY);
        }

        function test_append() {
            lineSeriesPointAddedSpy.clear();
            splineSeriesPointAddedSpy.clear();
            scatterSeriesPointAddedSpy.clear();
            var count = append();
            compare(lineSeries.count, count);
            compare(splineSeries.count, count);
            compare(scatterSeries.count, count);
            compare(lineSeriesPointAddedSpy.count, count);
            compare(splineSeriesPointAddedSpy.count, count);
            compare(scatterSeriesPointAddedSpy.count, count);
            clear();
            compare(lineSeries.count, 0);
            compare(splineSeries.count, 0);
            compare(scatterSeries.count, 0);
        }

        function test_replace() {
            var count = append();
            for (var i = 0; i < count; i++) {
                lineSeries.replace(lineSeries.at(i).x, lineSeries.at(i).y, i, Math.random());
                splineSeries.replace(splineSeries.at(i).x, splineSeries.at(i).y, i, Math.random());
                scatterSeries.replace(scatterSeries.at(i).x, scatterSeries.at(i).y, i, Math.random());
            }
            compare(lineSeries.count, count);
            compare(splineSeries.count, count);
            compare(scatterSeries.count, count);
            compare(lineSeriesPointReplacedSpy.count, count);
            compare(splineSeriesPointReplacedSpy.count, count);
            compare(scatterSeriesPointReplacedSpy.count, count);
            clear();
        }

        function test_insert() {
            var count = append();
            lineSeriesPointAddedSpy.clear();
            splineSeriesPointAddedSpy.clear();
            scatterSeriesPointAddedSpy.clear();
            for (var i = 0; i < count; i++) {
                lineSeries.insert(i * 2, i, Math.random());
                splineSeries.insert(i * 2, i, Math.random());
                scatterSeries.insert(i * 2, i, Math.random());
            }
            compare(lineSeries.count, count * 2);
            compare(splineSeries.count, count * 2);
            compare(scatterSeries.count, count * 2);
            compare(lineSeriesPointAddedSpy.count, count);
            compare(splineSeriesPointAddedSpy.count, count);
            compare(scatterSeriesPointAddedSpy.count, count);
            clear();
        }

        function test_remove() {
            lineSeriesPointRemovedSpy.clear();
            splineSeriesPointRemovedSpy.clear();
            scatterSeriesPointRemovedSpy.clear();
            var count = append();
            for (var i = 0; i < count; i++) {
                lineSeries.remove(lineSeries.at(0).x, lineSeries.at(0).y);
                splineSeries.remove(splineSeries.at(0).x, splineSeries.at(0).y);
                scatterSeries.remove(scatterSeries.at(0).x, scatterSeries.at(0).y);
            }
            compare(lineSeries.count, 0);
            compare(splineSeries.count, 0);
            compare(scatterSeries.count, 0);
            compare(lineSeriesPointRemovedSpy.count, count);
            compare(splineSeriesPointRemovedSpy.count, count);
            compare(scatterSeriesPointRemovedSpy.count, count);

            lineSeriesPointRemovedSpy.clear();
            splineSeriesPointRemovedSpy.clear();
            scatterSeriesPointRemovedSpy.clear();
            lineSeriesPointsRemovedSpy.clear();
            splineSeriesPointsRemovedSpy.clear();
            scatterSeriesPointsRemovedSpy.clear();

            count = append();
            lineSeries.removePoints(2, count - 2);
            splineSeries.removePoints(2, count - 2);
            scatterSeries.removePoints(2, count - 2);

            compare(lineSeries.count, 2);
            compare(splineSeries.count, 2);
            compare(scatterSeries.count, 2);

            lineSeries.removePoints(0, 2);
            splineSeries.removePoints(0, 2);
            scatterSeries.removePoints(0, 2);

            compare(lineSeries.count, 0);
            compare(splineSeries.count, 0);
            compare(scatterSeries.count, 0);
            compare(lineSeriesPointRemovedSpy.count, 0);
            compare(splineSeriesPointRemovedSpy.count, 0);
            compare(scatterSeriesPointRemovedSpy.count, 0);
            compare(lineSeriesPointsRemovedSpy.count, 2);
            compare(splineSeriesPointsRemovedSpy.count, 2);
            compare(scatterSeriesPointsRemovedSpy.count, 2);
        }

        // Not a test function, called from test functions
        function append() {
            var count = 100;
            chartView.axisX().min = 0;
            chartView.axisX().max = 100;
            chartView.axisY().min = 0;
            chartView.axisY().max = 1;

            for (var i = 0; i < count; i++) {
                lineSeries.append(i, Math.random());
                splineSeries.append(i, Math.random());
                scatterSeries.append(i, Math.random());
            }

            return count;
        }

        // Not a test function, called from test functions
        function clear() {
            lineSeries.clear();
            splineSeries.clear();
            scatterSeries.clear();
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent

        LineSeries {
            id: lineSeries
            name: "line"

            SignalSpy {
                id: lineSeriesPointAddedSpy
                target: lineSeries
                signalName: "pointAdded"
            }

            SignalSpy {
                id: lineSeriesPointReplacedSpy
                target: lineSeries
                signalName: "pointReplaced"
            }

            SignalSpy {
                id: lineSeriesPointsReplacedSpy
                target: lineSeries
                signalName: "pointsReplaced"
            }

            SignalSpy {
                id: lineSeriesPointRemovedSpy
                target: lineSeries
                signalName: "pointRemoved"
            }

            SignalSpy {
                id: lineSeriesPointsRemovedSpy
                target: lineSeries
                signalName: "pointsRemoved"
            }
        }

        AreaSeries {
            id: areaSeries
            name: "area"
            upperSeries: lineSeries
        }

        SplineSeries {
            id: splineSeries
            name: "spline"

            SignalSpy {
                id: splineSeriesPointAddedSpy
                target: splineSeries
                signalName: "pointAdded"
            }

            SignalSpy {
                id: splineSeriesPointReplacedSpy
                target: splineSeries
                signalName: "pointReplaced"
            }

            SignalSpy {
                id: splineSeriesPointsReplacedSpy
                target: splineSeries
                signalName: "pointsReplaced"
            }

            SignalSpy {
                id: splineSeriesPointRemovedSpy
                target: splineSeries
                signalName: "pointRemoved"
            }

            SignalSpy {
                id: splineSeriesPointsRemovedSpy
                target: splineSeries
                signalName: "pointsRemoved"
            }
        }

        ScatterSeries {
            id: scatterSeries
            name: "scatter"

            SignalSpy {
                id: scatterSeriesPointAddedSpy
                target: scatterSeries
                signalName: "pointAdded"
            }

            SignalSpy {
                id: scatterSeriesPointReplacedSpy
                target: scatterSeries
                signalName: "pointReplaced"
            }

            SignalSpy {
                id: scatterSeriesPointsReplacedSpy
                target: scatterSeries
                signalName: "pointsReplaced"
            }

            SignalSpy {
                id: scatterSeriesPointRemovedSpy
                target: scatterSeries
                signalName: "pointRemoved"
            }

            SignalSpy {
                id: scatterSeriesPointsRemovedSpy
                target: scatterSeries
                signalName: "pointsRemoved"
            }
        }
    }
}
