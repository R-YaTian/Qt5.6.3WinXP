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

#ifndef QABSTRACTBARSERIES_H
#define QABSTRACTBARSERIES_H

#include <QtCharts/QAbstractSeries>
#include <QtCore/QStringList>

QT_CHARTS_BEGIN_NAMESPACE

class QBarSet;
class QAbstractBarSeriesPrivate;

// Container for series
class QT_CHARTS_EXPORT QAbstractBarSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(qreal barWidth READ barWidth WRITE setBarWidth)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool labelsVisible READ isLabelsVisible WRITE setLabelsVisible NOTIFY labelsVisibleChanged)
    Q_PROPERTY(QString labelsFormat READ labelsFormat WRITE setLabelsFormat NOTIFY labelsFormatChanged)
    Q_PROPERTY(LabelsPosition labelsPosition READ labelsPosition WRITE setLabelsPosition NOTIFY labelsPositionChanged)
    Q_PROPERTY(qreal labelsAngle READ labelsAngle WRITE setLabelsAngle NOTIFY labelsAngleChanged)
    Q_ENUMS(LabelsPosition)

public:
    enum LabelsPosition {
        LabelsCenter = 0,
        LabelsInsideEnd,
        LabelsInsideBase,
        LabelsOutsideEnd
    };

public:
    virtual ~QAbstractBarSeries();

    void setBarWidth(qreal width);
    qreal barWidth() const;

    bool append(QBarSet *set);
    bool remove(QBarSet *set);
    bool take(QBarSet *set);
    bool append(QList<QBarSet *> sets);
    bool insert(int index, QBarSet *set);
    int count() const;
    QList<QBarSet *> barSets() const;
    void clear();

    void setLabelsVisible(bool visible = true);
    bool isLabelsVisible() const;

    void setLabelsFormat(const QString &format);
    QString labelsFormat() const;

    void setLabelsAngle(qreal angle);
    qreal labelsAngle() const;

    void setLabelsPosition(QAbstractBarSeries::LabelsPosition position);
    QAbstractBarSeries::LabelsPosition labelsPosition() const;

protected:
    explicit QAbstractBarSeries(QAbstractBarSeriesPrivate &d, QObject *parent = Q_NULLPTR);

Q_SIGNALS:
    void clicked(int index, QBarSet *barset);
    void hovered(bool status, int index, QBarSet *barset);
    void pressed(int index, QBarSet *barset);
    void released(int index, QBarSet *barset);
    void doubleClicked(int index, QBarSet *barset);
    void countChanged();
    void labelsVisibleChanged();
    void labelsFormatChanged(const QString &format);
    void labelsPositionChanged(QAbstractBarSeries::LabelsPosition position);
    void labelsAngleChanged(qreal angle);

    void barsetsAdded(QList<QBarSet *> sets);
    void barsetsRemoved(QList<QBarSet *> sets);

protected:
    Q_DECLARE_PRIVATE(QAbstractBarSeries)
    friend class AbstractBarChartItem;
    friend class PercentBarChartItem;
    friend class StackedBarChartItem;
    friend class BoxPlotChartItem;
    friend class BarChartItem;
    friend class HorizontalBarChartItem;
    friend class HorizontalStackedBarChartItem;
    friend class HorizontalPercentBarChartItem;
    friend class BarSet;
};

QT_CHARTS_END_NAMESPACE

#endif // QABSTRACTBARSERIES_H
