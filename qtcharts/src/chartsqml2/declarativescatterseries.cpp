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

#include "declarativescatterseries.h"

QT_CHARTS_BEGIN_NAMESPACE

DeclarativeScatterSeries::DeclarativeScatterSeries(QObject *parent) :
    QScatterSeries(parent),
    m_axes(new DeclarativeAxes(this))
{
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisAngularChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisRadialChanged(QAbstractAxis*)));
    connect(this, SIGNAL(pointAdded(int)), this, SLOT(handleCountChanged(int)));
    connect(this, SIGNAL(pointRemoved(int)), this, SLOT(handleCountChanged(int)));
    connect(this, SIGNAL(pointsRemoved(int, int)), this, SLOT(handleCountChanged(int)));
    connect(this, SIGNAL(brushChanged()), this, SLOT(handleBrushChanged()));
}

void DeclarativeScatterSeries::handleCountChanged(int index)
{
    Q_UNUSED(index)
    emit countChanged(QScatterSeries::count());
}

qreal DeclarativeScatterSeries::borderWidth() const
{
    return pen().widthF();
}

void DeclarativeScatterSeries::setBorderWidth(qreal width)
{
    if (width != pen().widthF()) {
        QPen p = pen();
        p.setWidthF(width);
        setPen(p);
        emit borderWidthChanged(width);
    }
}

QQmlListProperty<QObject> DeclarativeScatterSeries::declarativeChildren()
{
    return QQmlListProperty<QObject>(this, 0, &appendDeclarativeChildren ,0,0,0);
}

void DeclarativeScatterSeries::appendDeclarativeChildren(QQmlListProperty<QObject> *list, QObject *element)
{
    Q_UNUSED(list)
    Q_UNUSED(element)
    // Empty implementation, children are parsed in componentComplete
}

QString DeclarativeScatterSeries::brushFilename() const
{
    return m_brushFilename;
}

void DeclarativeScatterSeries::setBrushFilename(const QString &brushFilename)
{
    QImage brushImage(brushFilename);
    if (QScatterSeries::brush().textureImage() != brushImage) {
        QBrush brush = QScatterSeries::brush();
        brush.setTextureImage(brushImage);
        QScatterSeries::setBrush(brush);
        m_brushFilename = brushFilename;
        m_brushImage = brushImage;
        emit brushFilenameChanged(brushFilename);
    }
}

void DeclarativeScatterSeries::setBrush(const QBrush &brush)
{
    QScatterSeries::setBrush(brush);
    emit brushChanged();
}

QBrush DeclarativeScatterSeries::brush() const
{
    return QScatterSeries::brush();
}

void DeclarativeScatterSeries::handleBrushChanged()
{
    // If the texture image of the brush has changed along the brush
    // the brush file name needs to be cleared.
    if (!m_brushFilename.isEmpty() && QScatterSeries::brush().textureImage() != m_brushImage) {
        m_brushFilename.clear();
        emit brushFilenameChanged(QString(""));
    }
}

#include "moc_declarativescatterseries.cpp"

QT_CHARTS_END_NAMESPACE
