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

#include <QtCharts/QBoxPlotLegendMarker>
#include <private/qboxplotlegendmarker_p.h>
#include <QtCharts/QBoxPlotSeries>
#include <private/qboxplotseries_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QBoxPlotLegendMarker
    \inmodule Qt Charts
    \brief QLegendMarker subclass for box plot series.

    QBoxPlotLegendMarker is related to QBoxPlotSeries classes.

    \sa QLegend, QBoxPlotSeries
*/

/*!
  \fn virtual LegendMarkerType QBoxPlotLegendMarker::type()
  Returns QLegendMarker::LegendMarkerTypeBoxPlot
*/

/*!
  \internal
*/
QBoxPlotLegendMarker::QBoxPlotLegendMarker(QBoxPlotSeries *series, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QBoxPlotLegendMarkerPrivate(this,series,legend), parent)
{
    d_ptr->updated();
}

/*!
  Destructor
*/
QBoxPlotLegendMarker::~QBoxPlotLegendMarker()
{
}

/*!
    \internal
*/
QBoxPlotLegendMarker::QBoxPlotLegendMarker(QBoxPlotLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

/*!
  Returns the related series
*/
QBoxPlotSeries* QBoxPlotLegendMarker::series()
{
    Q_D(QBoxPlotLegendMarker);
    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBoxPlotLegendMarkerPrivate::QBoxPlotLegendMarkerPrivate(QBoxPlotLegendMarker *q, QBoxPlotSeries *series, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    q_ptr(q),
    m_series(series)
{
    QObject::connect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(updated()));
}

QBoxPlotLegendMarkerPrivate::~QBoxPlotLegendMarkerPrivate()
{
}

QAbstractSeries* QBoxPlotLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QBoxPlotLegendMarkerPrivate::relatedObject()
{
    return m_series;
}

void QBoxPlotLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;

    if (!m_customLabel && (m_item->label() != m_series->name())) {
        m_item->setLabel(m_series->name());
        labelChanged = true;
    }
    if (!m_customBrush && (m_item->brush() != m_series->brush())) {
        m_item->setBrush(m_series->brush());
        brushChanged = true;
    }
    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
}

#include "moc_qboxplotlegendmarker.cpp"
#include "moc_qboxplotlegendmarker_p.cpp"

QT_CHARTS_END_NAMESPACE

