/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module.
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

#ifndef QVALUE3DAXISFORMATTER_H
#define QVALUE3DAXISFORMATTER_H

#include <QtDataVisualization/qdatavisualizationglobal.h>
#include <QtCore/QObject>
#include <QtCore/QScopedPointer>
#include <QtCore/QVector>
#include <QtCore/QStringList>
#include <QtCore/QLocale>

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class QValue3DAxisFormatterPrivate;
class QValue3DAxis;

class QT_DATAVISUALIZATION_EXPORT QValue3DAxisFormatter : public QObject
{
    Q_OBJECT
protected:
    explicit QValue3DAxisFormatter(QValue3DAxisFormatterPrivate *d, QObject *parent = Q_NULLPTR);
public:
    explicit QValue3DAxisFormatter(QObject *parent = Q_NULLPTR);
    virtual ~QValue3DAxisFormatter();

protected:
    void setAllowNegatives(bool allow);
    bool allowNegatives() const;
    void setAllowZero(bool allow);
    bool allowZero() const;

    virtual QValue3DAxisFormatter *createNewInstance() const;
    virtual void recalculate();
    virtual QString stringForValue(qreal value, const QString &format) const;
    virtual float positionAt(float value) const;
    virtual float valueAt(float position) const;
    virtual void populateCopy(QValue3DAxisFormatter &copy) const;

    void markDirty(bool labelsChange = false);
    QValue3DAxis *axis() const;

    QVector<float> &gridPositions() const;
    QVector<float> &subGridPositions() const;
    QVector<float> &labelPositions() const;
    QStringList &labelStrings() const;

    void setLocale(const QLocale &locale);
    QLocale locale() const;

    QScopedPointer<QValue3DAxisFormatterPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QValue3DAxisFormatter)

    friend class Abstract3DController;
    friend class Abstract3DRenderer;
    friend class Bars3DRenderer;
    friend class Scatter3DRenderer;
    friend class Surface3DRenderer;
    friend class SurfaceObject;
    friend class QValue3DAxisFormatterPrivate;
    friend class QLogValue3DAxisFormatter;
    friend class QValue3DAxis;
    friend class QValue3DAxisPrivate;
    friend class AxisRenderCache;
    friend class QBar3DSeriesPrivate;
    friend class QScatter3DSeriesPrivate;
    friend class QSurface3DSeriesPrivate;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
