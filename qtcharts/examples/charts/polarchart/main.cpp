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

#include "chartview.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCore/QDebug>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const qreal angularMin = -100;
    const qreal angularMax = 100;

    const qreal radialMin = -100;
    const qreal radialMax = 100;

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter");
    for (int i = angularMin; i <= angularMax; i += 10)
        series1->append(i, (i / radialMax) * radialMax + 8.0);

    QSplineSeries *series2 = new QSplineSeries();
    series2->setName("spline");
    for (int i = angularMin; i <= angularMax; i += 10)
        series2->append(i, (i / radialMax) * radialMax);

    QLineSeries *series3 = new QLineSeries();
    series3->setName("star outer");
    qreal ad = (angularMax - angularMin) / 8;
    qreal rd = (radialMax - radialMin) / 3 * 1.3;
    series3->append(angularMin, radialMax);
    series3->append(angularMin + ad*1, radialMin + rd);
    series3->append(angularMin + ad*2, radialMax);
    series3->append(angularMin + ad*3, radialMin + rd);
    series3->append(angularMin + ad*4, radialMax);
    series3->append(angularMin + ad*5, radialMin + rd);
    series3->append(angularMin + ad*6, radialMax);
    series3->append(angularMin + ad*7, radialMin + rd);
    series3->append(angularMin + ad*8, radialMax);

    QLineSeries *series4 = new QLineSeries();
    series4->setName("star inner");
    ad = (angularMax - angularMin) / 8;
    rd = (radialMax - radialMin) / 3;
    series4->append(angularMin, radialMax);
    series4->append(angularMin + ad*1, radialMin + rd);
    series4->append(angularMin + ad*2, radialMax);
    series4->append(angularMin + ad*3, radialMin + rd);
    series4->append(angularMin + ad*4, radialMax);
    series4->append(angularMin + ad*5, radialMin + rd);
    series4->append(angularMin + ad*6, radialMax);
    series4->append(angularMin + ad*7, radialMin + rd);
    series4->append(angularMin + ad*8, radialMax);

    QAreaSeries *series5 = new QAreaSeries();
    series5->setName("star area");
    series5->setUpperSeries(series3);
    series5->setLowerSeries(series4);
    series5->setOpacity(0.5);

    //![1]
    QPolarChart *chart = new QPolarChart();
    //![1]
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->addSeries(series4);
    chart->addSeries(series5);

    chart->setTitle("Use arrow keys to scroll, +/- to zoom, and space to switch chart type.");

    //![2]
    QValueAxis *angularAxis = new QValueAxis();
    angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%.1f");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis *radialAxis = new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%d");
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    //![2]

    series1->attachAxis(radialAxis);
    series1->attachAxis(angularAxis);
    series2->attachAxis(radialAxis);
    series2->attachAxis(angularAxis);
    series3->attachAxis(radialAxis);
    series3->attachAxis(angularAxis);
    series4->attachAxis(radialAxis);
    series4->attachAxis(angularAxis);
    series5->attachAxis(radialAxis);
    series5->attachAxis(angularAxis);

    radialAxis->setRange(radialMin, radialMax);
    angularAxis->setRange(angularMin, angularMax);

    ChartView *chartView = new ChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    return a.exec();
}
