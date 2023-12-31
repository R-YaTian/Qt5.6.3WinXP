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

#ifndef QHBARMODELMAPPER_H
#define QHBARMODELMAPPER_H

#include <QtCharts/QBarModelMapper>

QT_CHARTS_BEGIN_NAMESPACE
/* Comment line for syncqt to generate the fwd-include correctly, due to QTBUG-22432 */
class QT_CHARTS_EXPORT QHBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(QAbstractBarSeries *series READ series WRITE setSeries NOTIFY seriesReplaced)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelReplaced)
    Q_PROPERTY(int firstBarSetRow READ firstBarSetRow WRITE setFirstBarSetRow NOTIFY firstBarSetRowChanged)
    Q_PROPERTY(int lastBarSetRow READ lastBarSetRow WRITE setLastBarSetRow NOTIFY lastBarSetRowChanged)
    Q_PROPERTY(int firstColumn READ firstColumn WRITE setFirstColumn NOTIFY firstColumnChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)

public:
    explicit QHBarModelMapper(QObject *parent = Q_NULLPTR);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    QAbstractBarSeries *series() const;
    void setSeries(QAbstractBarSeries *series);

    int firstBarSetRow() const;
    void setFirstBarSetRow(int firstBarSetRow);

    int lastBarSetRow() const;
    void setLastBarSetRow(int lastBarSetRow);

    int firstColumn() const;
    void setFirstColumn(int firstColumn);

    int columnCount() const;
    void setColumnCount(int columnCount);

Q_SIGNALS:
    void seriesReplaced();
    void modelReplaced();
    void firstBarSetRowChanged();
    void lastBarSetRowChanged();
    void firstColumnChanged();
    void columnCountChanged();
};

QT_CHARTS_END_NAMESPACE

#endif // QHBARMODELMAPPER_H
