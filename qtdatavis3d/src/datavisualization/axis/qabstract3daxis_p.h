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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QABSTRACT3DAXIS_P_H
#define QABSTRACT3DAXIS_P_H

#include "datavisualizationglobal_p.h"
#include "qabstract3daxis.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class QAbstract3DAxisPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstract3DAxisPrivate(QAbstract3DAxis *q, QAbstract3DAxis::AxisType type);
    virtual ~QAbstract3DAxisPrivate();

    void setOrientation(QAbstract3DAxis::AxisOrientation orientation);

    inline bool isDefaultAxis() { return m_isDefaultAxis; }
    inline void setDefaultAxis(bool isDefault) { m_isDefaultAxis = isDefault; }

    virtual void setRange(float min, float max, bool suppressWarnings = false);
    virtual void setMin(float min);
    virtual void setMax (float max);

protected:
    virtual void updateLabels();
    virtual bool allowZero() = 0;
    virtual bool allowNegatives() = 0;
    virtual bool allowMinMaxSame() = 0;

    QAbstract3DAxis *q_ptr;

    QString m_title;
    QStringList m_labels;
    QAbstract3DAxis::AxisOrientation m_orientation;
    QAbstract3DAxis::AxisType m_type;
    bool m_isDefaultAxis;
    float m_min;
    float m_max;
    bool m_autoAdjust;
    float m_labelAutoRotation;
    bool m_titleVisible;
    bool m_titleFixed;

    friend class QAbstract3DAxis;
    friend class QValue3DAxis;
    friend class QCategory3DAxis;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
