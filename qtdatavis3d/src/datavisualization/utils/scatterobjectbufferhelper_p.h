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

#ifndef SCATTEROBJECTBUFFERHELPER_P_H
#define SCATTEROBJECTBUFFERHELPER_P_H

#include "datavisualizationglobal_p.h"
#include "abstractobjecthelper_p.h"
#include "scatterseriesrendercache_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class ScatterObjectBufferHelper : public AbstractObjectHelper
{
public:
    ScatterObjectBufferHelper();
    virtual ~ScatterObjectBufferHelper();

    void fullLoad(ScatterSeriesRenderCache *cache, qreal dotScale);
    void update(ScatterSeriesRenderCache *cache, qreal dotScale);
    void updateUVs(ScatterSeriesRenderCache *cache);
    void setScaleY(float scale) { m_scaleY = scale; }

private:
    uint createRangeGradientUVs(ScatterSeriesRenderCache *cache,
                                QVector<QVector2D> &buffered_uvs);
    uint createObjectGradientUVs(ScatterSeriesRenderCache *cache,
                                 QVector<QVector2D> &buffered_uvs,
                                 const QVector<QVector3D> &indexed_vertices);

    float m_scaleY;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
