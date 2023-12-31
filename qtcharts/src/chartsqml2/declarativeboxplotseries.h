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

#ifndef DECLARATIVEBOXPLOT_H
#define DECLARATIVEBOXPLOT_H

#include <QtCharts/QBoxSet>
#include "declarativeaxes.h"
#include <QtCharts/QBoxPlotSeries>

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlParserStatus>

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativeBoxSet : public QBoxSet
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION 1)
    Q_ENUMS(ValuePositions)

public: // duplicate from QBoxSet
    enum ValuePositions {
        LowerExtreme = 0x0,
        LowerQuartile,
        Median,
        UpperQuartile,
        UpperExtreme
    };

public:
    explicit DeclarativeBoxSet(const QString label = "", QObject *parent = 0);
    QVariantList values();
    void setValues(QVariantList values);
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);

public: // From QBoxSet
    Q_INVOKABLE void append(qreal value) { QBoxSet::append(value); }
    Q_INVOKABLE void clear() {QBoxSet::clear(); }
    Q_INVOKABLE qreal at(int index) { return QBoxSet::at(index); }
    Q_INVOKABLE void setValue(int index, qreal value) { QBoxSet::setValue(index, value); }

Q_SIGNALS:
    void changedValues();
    void changedValue(int index);
    Q_REVISION(1) void brushFilenameChanged(const QString &brushFilename);

private Q_SLOTS:
    void handleBrushChanged();

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

class DeclarativeBoxPlotSeries : public QBoxPlotSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged)
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION 1)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativeBoxPlotSeries(QQuickItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QQmlListProperty<QObject> seriesChildren();
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);

public:
    Q_INVOKABLE DeclarativeBoxSet *at(int index);
    Q_INVOKABLE DeclarativeBoxSet *append(const QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE void append(DeclarativeBoxSet *box) { QBoxPlotSeries::append(box); }
    Q_INVOKABLE DeclarativeBoxSet *insert(int index, const QString label, QVariantList values);
    Q_INVOKABLE bool remove(DeclarativeBoxSet *box) { return QBoxPlotSeries::remove(qobject_cast<QBoxSet *>(box)); }
    Q_INVOKABLE void clear() { return QBoxPlotSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

Q_SIGNALS:
    void axisXChanged(QAbstractAxis *axis);
    void axisYChanged(QAbstractAxis *axis);
    void axisXTopChanged(QAbstractAxis *axis);
    void axisYRightChanged(QAbstractAxis *axis);
    void clicked(DeclarativeBoxSet *boxset);
    void hovered(bool status, DeclarativeBoxSet *boxset);
    void pressed(DeclarativeBoxSet *boxset);
    void released(DeclarativeBoxSet *boxset);
    void doubleClicked(DeclarativeBoxSet *boxset);
    Q_REVISION(1) void brushFilenameChanged(const QString &brushFilename);

public Q_SLOTS:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);
    void onHovered(bool status, QBoxSet *boxset);
    void onClicked(QBoxSet *boxset);
    void onPressed(QBoxSet *boxset);
    void onReleased(QBoxSet *boxset);
    void onDoubleClicked(QBoxSet *boxset);

private Q_SLOTS:
    void handleBrushChanged();

public:
    DeclarativeAxes *m_axes;

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVEBOXPLOT_H
