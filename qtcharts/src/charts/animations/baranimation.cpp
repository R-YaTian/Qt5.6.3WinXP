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

#include <private/baranimation_p.h>
#include <private/abstractbarchartitem_p.h>

Q_DECLARE_METATYPE(QVector<QRectF>)

QT_CHARTS_BEGIN_NAMESPACE

BarAnimation::BarAnimation(AbstractBarChartItem *item, int duration, QEasingCurve &curve)
    : ChartAnimation(item),
      m_item(item)
{
    setDuration(duration);
    setEasingCurve(curve);
}

BarAnimation::~BarAnimation()
{
}

QVariant BarAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    QVector<QRectF> startVector = qvariant_cast<QVector<QRectF> >(from);
    QVector<QRectF> endVector = qvariant_cast<QVector<QRectF> >(to);
    QVector<QRectF> result;

    Q_ASSERT(startVector.count() == endVector.count());

    for (int i = 0; i < startVector.count(); i++) {
        QRectF start = startVector[i].normalized();
        QRectF end = endVector[i].normalized();
        qreal x1 = start.left() + progress * (end.left() - start.left());
        qreal x2 = start.right() + progress * (end.right() - start.right());
        qreal y1 = start.top() + progress * (end.top() - start.top());
        qreal y2 = start.bottom() + progress * (end.bottom() - start.bottom());

        QRectF value(QPointF(x1, y1), QPointF(x2, y2));
        result << value.normalized();
    }
    return qVariantFromValue(result);
}

void BarAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped) { //workaround

        QVector<QRectF> layout = qvariant_cast<QVector<QRectF> >(value);
        m_item->setLayout(layout);
    }
}

void BarAnimation::setup(const QVector<QRectF> &oldLayout, const QVector<QRectF> &newLayout)
{
    QVariantAnimation::KeyValues value;
    setKeyValues(value); //workaround for wrong interpolation call
    setKeyValueAt(0.0, qVariantFromValue(oldLayout));
    setKeyValueAt(1.0, qVariantFromValue(newLayout));
}

#include "moc_baranimation_p.cpp"

QT_CHARTS_END_NAMESPACE

