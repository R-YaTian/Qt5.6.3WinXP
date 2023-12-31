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

#ifndef QCATEGORYAXIS_H
#define QCATEGORYAXIS_H

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_BEGIN_NAMESPACE

class QCategoryAxisPrivate;

class QT_CHARTS_EXPORT QCategoryAxis : public QValueAxis
{
    Q_OBJECT
    Q_PROPERTY(qreal startValue READ startValue WRITE setStartValue)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QStringList categoriesLabels READ categoriesLabels)
    Q_PROPERTY(AxisLabelsPosition labelsPosition READ labelsPosition WRITE setLabelsPosition NOTIFY labelsPositionChanged)
    Q_ENUMS(AxisLabelsPosition)

public:

    enum AxisLabelsPosition {
        AxisLabelsPositionCenter = 0x0,
        AxisLabelsPositionOnValue = 0x1
    };

    explicit QCategoryAxis(QObject *parent = Q_NULLPTR);
    ~QCategoryAxis();

protected:
    QCategoryAxis(QCategoryAxisPrivate &d, QObject *parent = Q_NULLPTR);

public:
    AxisType type() const;

    void append(const QString &label, qreal categoryEndValue);
    void remove(const QString &label);
    void replaceLabel(const QString &oldLabel, const QString &newLabel);

    qreal startValue(const QString &categoryLabel = QString()) const;
    void setStartValue(qreal min);

    qreal endValue(const QString &categoryLabel) const;

    QStringList categoriesLabels();
    int count() const;

    QCategoryAxis::AxisLabelsPosition labelsPosition() const;
    void setLabelsPosition(QCategoryAxis::AxisLabelsPosition position);

Q_SIGNALS:
    void categoriesChanged();
    void labelsPositionChanged(QCategoryAxis::AxisLabelsPosition position);

private:
    Q_DECLARE_PRIVATE(QCategoryAxis)
    Q_DISABLE_COPY(QCategoryAxis)
};

QT_CHARTS_END_NAMESPACE

#endif // QCATEGORYAXIS_H
