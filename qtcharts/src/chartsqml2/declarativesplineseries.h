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

#ifndef DECLARATIVESPLINESERIES_H
#define DECLARATIVESPLINESERIES_H

#include <QtCharts/QSplineSeries>
#include "declarativexyseries.h"
#include "declarativeaxes.h"

#include <QtQml/QQmlListProperty>
#include <QtQml/QQmlParserStatus>

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativeSplineSeries : public QSplineSeries, public DeclarativeXySeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION 1)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION 1)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION 2)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION 2)
    Q_PROPERTY(QAbstractAxis *axisAngular READ axisAngular WRITE setAxisAngular NOTIFY axisAngularChanged REVISION 3)
    Q_PROPERTY(QAbstractAxis *axisRadial READ axisRadial WRITE setAxisRadial NOTIFY axisRadialChanged REVISION 3)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged REVISION 1)
    Q_PROPERTY(Qt::PenStyle style READ style WRITE setStyle NOTIFY styleChanged REVISION 1)
    Q_PROPERTY(Qt::PenCapStyle capStyle READ capStyle WRITE setCapStyle NOTIFY capStyleChanged REVISION 1)
    Q_PROPERTY(QQmlListProperty<QObject> declarativeChildren READ declarativeChildren)
    Q_CLASSINFO("DefaultProperty", "declarativeChildren")

public:
    explicit DeclarativeSplineSeries(QObject *parent = 0);
    QXYSeries *xySeries() { return this; }
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QAbstractAxis *axisAngular() { return m_axes->axisX(); }
    void setAxisAngular(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisRadial() { return m_axes->axisY(); }
    void setAxisRadial(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    qreal width() const;
    void setWidth(qreal width);
    Qt::PenStyle style() const;
    void setStyle(Qt::PenStyle style);
    Qt::PenCapStyle capStyle() const;
    void setCapStyle(Qt::PenCapStyle capStyle);
    QQmlListProperty<QObject> declarativeChildren();

public: // from QDeclarativeParserStatus
    void classBegin() { DeclarativeXySeries::classBegin(); }
    void componentComplete() { DeclarativeXySeries::componentComplete(); }

public:
    Q_INVOKABLE void append(qreal x, qreal y) { DeclarativeXySeries::append(x, y); }
    Q_INVOKABLE void replace(qreal oldX, qreal oldY, qreal newX, qreal newY) { DeclarativeXySeries::replace(oldX, oldY, newX, newY); }
    Q_REVISION(3) Q_INVOKABLE void replace(int index, qreal newX, qreal newY) { DeclarativeXySeries::replace(index, newX, newY); }
    Q_INVOKABLE void remove(qreal x, qreal y) { DeclarativeXySeries::remove(x, y); }
    Q_REVISION(3) Q_INVOKABLE void remove(int index) { DeclarativeXySeries::remove(index); }
    Q_REVISION(4) Q_INVOKABLE void removePoints(int index, int count) { DeclarativeXySeries::removePoints(index, count); }
    Q_INVOKABLE void insert(int index, qreal x, qreal y) { DeclarativeXySeries::insert(index, x, y); }
    Q_INVOKABLE void clear() { DeclarativeXySeries::clear(); }
    Q_INVOKABLE QPointF at(int index) { return DeclarativeXySeries::at(index); }

Q_SIGNALS:
    void countChanged(int count);
    Q_REVISION(1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(2) void axisYRightChanged(QAbstractAxis *axis);
    Q_REVISION(3) void axisAngularChanged(QAbstractAxis *axis);
    Q_REVISION(3) void axisRadialChanged(QAbstractAxis *axis);
    Q_REVISION(1) void widthChanged(qreal width);
    Q_REVISION(1) void styleChanged(Qt::PenStyle style);
    Q_REVISION(1) void capStyleChanged(Qt::PenCapStyle capStyle);

public Q_SLOTS:
    static void appendDeclarativeChildren(QQmlListProperty<QObject> *list, QObject *element);
    void handleCountChanged(int index);

public:
    DeclarativeAxes *m_axes;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVESPLINESERIES_H
