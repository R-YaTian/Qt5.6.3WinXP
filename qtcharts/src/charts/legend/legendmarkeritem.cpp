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

#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QGraphicsTextItem>
#include <QtGui/QTextDocument>

#include <QtCharts/QLegend>
#include <private/qlegend_p.h>
#include <QtCharts/QLegendMarker>
#include <private/qlegendmarker_p.h>
#include <private/legendmarkeritem_p.h>
#include <private/chartpresenter_p.h>

QT_CHARTS_BEGIN_NAMESPACE

LegendMarkerItem::LegendMarkerItem(QLegendMarkerPrivate *marker, QGraphicsObject *parent) :
    QGraphicsObject(parent),
    m_marker(marker),
    m_markerRect(0,0,10.0,10.0),
    m_boundingRect(0,0,0,0),
    m_textItem(new QGraphicsTextItem(this)),
    m_rectItem(new QGraphicsRectItem(this)),
    m_margin(3),
    m_space(4),
    m_hovering(false),
    m_pressPos(0, 0)
{
    m_rectItem->setRect(m_markerRect);
    m_textItem->document()->setDocumentMargin(ChartPresenter::textMargin());
    setAcceptHoverEvents(true);
}

LegendMarkerItem::~LegendMarkerItem()
{
    if (m_hovering) {
        emit m_marker->q_ptr->hovered(false);
    }
}

void LegendMarkerItem::setPen(const QPen &pen)
{
    m_rectItem->setPen(pen);
}

QPen LegendMarkerItem::pen() const
{
    return m_rectItem->pen();
}

void LegendMarkerItem::setBrush(const QBrush &brush)
{
    m_rectItem->setBrush(brush);
}

QBrush LegendMarkerItem::brush() const
{
    return m_rectItem->brush();
}

void LegendMarkerItem::setFont(const QFont &font)
{
    m_textItem->setFont(font);
    QFontMetrics fn(font);
    m_markerRect = QRectF(0,0,fn.height()/2,fn.height()/2);
    updateGeometry();
}

QFont LegendMarkerItem::font() const
{
    return m_textItem->font();
}

void LegendMarkerItem::setLabel(const QString label)
{
    m_label = label;
    updateGeometry();
}

QString LegendMarkerItem::label() const
{
    return m_label;
}

void LegendMarkerItem::setLabelBrush(const QBrush &brush)
{
    m_textItem->setDefaultTextColor(brush.color());
}

QBrush LegendMarkerItem::labelBrush() const
{
    return QBrush(m_textItem->defaultTextColor());
}

void LegendMarkerItem::setGeometry(const QRectF &rect)
{
    qreal width = rect.width();
    qreal x = m_margin + m_markerRect.width() + m_space + m_margin;
    QRectF truncatedRect;

    m_textItem->setHtml(ChartPresenter::truncatedText(m_textItem->font(), m_label, qreal(0.0),
                                                      width - x, rect.height(), truncatedRect));
    m_textItem->setTextWidth(truncatedRect.width());

    qreal y = qMax(m_markerRect.height() + 2 * m_margin, truncatedRect.height() + 2 * m_margin);

    const QRectF &textRect = m_textItem->boundingRect();

    m_textItem->setPos(x - m_margin, y / 2 - textRect.height() / 2);
    m_rectItem->setRect(m_markerRect);
    // The textMargin adjustments to position are done to make default case rects less blurry with anti-aliasing
    m_rectItem->setPos(m_margin - ChartPresenter::textMargin(), y / 2.0  - m_markerRect.height() / 2.0 + ChartPresenter::textMargin());

    prepareGeometryChange();
    m_boundingRect = QRectF(0, 0, x + textRect.width() + m_margin, y);
}

QRectF LegendMarkerItem::boundingRect() const
{
    return m_boundingRect;
}

void LegendMarkerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    Q_UNUSED(painter)
}

QSizeF LegendMarkerItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QSizeF sh;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF labelRect = ChartPresenter::textBoundingRect(m_textItem->font(),
                                                            QStringLiteral("..."));
        sh = QSizeF(labelRect.width() + (2.0 * m_margin) + m_space + m_markerRect.width(),
                    qMax(m_markerRect.height(), labelRect.height()) + (2.0 * m_margin));
        break;
    }
    case Qt::PreferredSize: {
        QRectF labelRect = ChartPresenter::textBoundingRect(m_textItem->font(), m_label);
        sh = QSizeF(labelRect.width() + (2.0 * m_margin) + m_space + m_markerRect.width(),
                    qMax(m_markerRect.height(), labelRect.height()) + (2.0 * m_margin));
        break;
    }
    default:
        break;
    }

    return sh;
}

void LegendMarkerItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_hovering = true;
    emit m_marker->q_ptr->hovered(true);
}

void LegendMarkerItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    m_hovering = false;
    emit m_marker->q_ptr->hovered(false);
}


#include "moc_legendmarkeritem_p.cpp"

QT_CHARTS_END_NAMESPACE
