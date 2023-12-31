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

#ifndef QCUSTOM3DVOLUME_P_H
#define QCUSTOM3DVOLUME_P_H

#include "qcustom3dvolume.h"
#include "qcustom3ditem_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

struct QCustomVolumeDirtyBitField {
    bool textureDimensionsDirty : 1;
    bool slicesDirty            : 1;
    bool colorTableDirty        : 1;
    bool textureDataDirty       : 1;
    bool textureFormatDirty     : 1;
    bool alphaDirty             : 1;
    bool shaderDirty            : 1;

    QCustomVolumeDirtyBitField()
        : textureDimensionsDirty(false),
          slicesDirty(false),
          colorTableDirty(false),
          textureDataDirty(false),
          textureFormatDirty(false),
          alphaDirty(false),
          shaderDirty(false)
    {
    }
};

class QCustom3DVolumePrivate : public QCustom3DItemPrivate
{
    Q_OBJECT

public:
    QCustom3DVolumePrivate(QCustom3DVolume *q);
    QCustom3DVolumePrivate(QCustom3DVolume *q, const QVector3D &position, const QVector3D &scaling,
                           const QQuaternion &rotation, int textureWidth,
                           int textureHeight, int textureDepth, QVector<uchar> *textureData,
                           QImage::Format textureFormat, const QVector<QRgb> &colorTable);
    virtual ~QCustom3DVolumePrivate();

    void resetDirtyBits();
    QImage renderSlice(Qt::Axis axis, int index);

    QCustom3DVolume *qptr();

public:
    int m_textureWidth;
    int m_textureHeight;
    int m_textureDepth;
    int m_sliceIndexX;
    int m_sliceIndexY;
    int m_sliceIndexZ;

    QImage::Format m_textureFormat;
    QVector<QRgb> m_colorTable;
    QVector<uchar> *m_textureData;

    float m_alphaMultiplier;
    bool m_preserveOpacity;
    bool m_useHighDefShader;

    bool m_drawSlices;
    bool m_drawSliceFrames;
    QColor m_sliceFrameColor;
    QVector3D m_sliceFrameWidths;
    QVector3D m_sliceFrameGaps;
    QVector3D m_sliceFrameThicknesses;

    QCustomVolumeDirtyBitField m_dirtyBitsVolume;

private:
    int multipliedAlphaValue(int alpha);

    friend class QCustom3DVolume;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
