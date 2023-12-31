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

#ifndef QLEGENDMARKER_H
#define QLEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCore/QObject>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QFont>

QT_CHARTS_BEGIN_NAMESPACE

class QLegendMarkerPrivate;
class QAbstractSeries;
class QLegend;

class QT_CHARTS_EXPORT QLegendMarker : public QObject
{
    Q_OBJECT

public:
    enum LegendMarkerType {
        LegendMarkerTypeArea,
        LegendMarkerTypeBar,
        LegendMarkerTypePie,
        LegendMarkerTypeXY,
        LegendMarkerTypeBoxPlot
    };

    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QBrush labelBrush READ labelBrush WRITE setLabelBrush NOTIFY labelBrushChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_ENUMS(LegendMarkerType)

public:
    virtual ~QLegendMarker();
    virtual LegendMarkerType type() = 0;

    QString label() const;
    void setLabel(const QString &label);

    QBrush labelBrush() const;
    void setLabelBrush(const QBrush &brush);

    QFont font() const;
    void setFont(const QFont &font);

    QPen pen() const;
    void setPen(const QPen &pen);

    QBrush brush() const;
    void setBrush(const QBrush &brush);

    bool isVisible() const;
    void setVisible(bool visible);

    virtual QAbstractSeries* series() = 0;

Q_SIGNALS:
    void clicked();
    void hovered(bool status);
    void labelChanged();
    void labelBrushChanged();
    void fontChanged();
    void penChanged();
    void brushChanged();
    void visibleChanged();

protected:
    explicit QLegendMarker(QLegendMarkerPrivate &d, QObject *parent = Q_NULLPTR);

    QScopedPointer<QLegendMarkerPrivate> d_ptr;
    friend class QLegendPrivate;
    friend class QLegendMarkerPrivate;
    friend class LegendMarkerItem;
    friend class LegendLayout;
    friend class LegendScroller;

private:
    Q_DISABLE_COPY(QLegendMarker)
};

QT_CHARTS_END_NAMESPACE

#endif // QLEGENDMARKER_H
