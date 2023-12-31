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

#ifndef QHORIZONTALSTACKEDBARSERIES_H
#define QHORIZONTALSTACKEDBARSERIES_H

#include <QtCharts/QAbstractBarSeries>

QT_CHARTS_BEGIN_NAMESPACE

class QHorizontalStackedBarSeriesPrivate;

class QT_CHARTS_EXPORT QHorizontalStackedBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QHorizontalStackedBarSeries(QObject *parent = Q_NULLPTR);
    ~QHorizontalStackedBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QHorizontalStackedBarSeries)
    Q_DISABLE_COPY(QHorizontalStackedBarSeries)
};

QT_CHARTS_END_NAMESPACE

#endif // QHORIZONTALSTACKEDBARSERIES_H
