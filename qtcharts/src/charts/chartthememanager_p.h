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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef CHARTTHEMEMANAGER_H
#define CHARTTHEMEMANAGER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtGui/QColor>
#include <QtGui/QGradientStops>

QT_CHARTS_BEGIN_NAMESPACE
class ChartTheme;

class ChartThemeManager: public QObject
{
    Q_OBJECT
public:
    enum BackgroundShadesMode {
        BackgroundShadesNone = 0,
        BackgroundShadesVertical,
        BackgroundShadesHorizontal,
        BackgroundShadesBoth
    };

public:
    explicit ChartThemeManager(QChart* chart);
    void setTheme(QChart::ChartTheme theme);
    ChartTheme* theme() const { return m_theme.data(); }
    void decorateChart(QChart *chart, ChartTheme* theme) const;
    void decorateLegend(QLegend *legend, ChartTheme* theme) const;
    void updateSeries(QAbstractSeries *series);

public:
    static QList<QGradient> generateSeriesGradients(const QList<QColor>& colors);
    static QColor colorAt(const QColor &start, const QColor &end, qreal pos);
    static QColor colorAt(const QGradient &gradient, qreal pos);

private:
    int createIndexKey(QList<int> keys) const;
    int seriesCount(QAbstractSeries::SeriesType type) const;

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries *series);
    void handleSeriesRemoved(QAbstractSeries *series);
    void handleAxisAdded(QAbstractAxis *axis);
    void handleAxisRemoved(QAbstractAxis *axis);

protected:
    QScopedPointer<ChartTheme> m_theme;
    QMap<QAbstractSeries *,int> m_seriesMap;
    QList<QAbstractAxis *> m_axisList;
    QChart* m_chart;
};

QT_CHARTS_END_NAMESPACE

#endif // CHARTTHEME_H
