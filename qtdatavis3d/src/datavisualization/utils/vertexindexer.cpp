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

#include "vertexindexer_p.h"

#include <QtCore/qmath.h>

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

int unique_vertices = 0;

bool VertexIndexer::getSimilarVertexIndex_fast(const PackedVertex &packed,
                                               QMap<PackedVertex, GLuint> &VertexToOutIndex,
                                               GLuint &result)
{
    QMap<PackedVertex, GLuint>::iterator it = VertexToOutIndex.find(packed);
    if (it == VertexToOutIndex.end()) {
        return false;
    } else {
        result = it.value();
        return true;
    }
}

void VertexIndexer::indexVBO(const QVector<QVector3D> &in_vertices,
                             const QVector<QVector2D> &in_uvs,
                             const QVector<QVector3D> &in_normals,
                             QVector<GLuint> &out_indices,
                             QVector<QVector3D> &out_vertices,
                             QVector<QVector2D> &out_uvs,
                             QVector<QVector3D> &out_normals)
{
    unique_vertices = 0;
    QMap<PackedVertex, GLuint> VertexToOutIndex;

    // For each input vertex
    for (int i = 0; i < in_vertices.size(); i++) {
        PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};

        // Try to find a similar vertex in out_XXXX
        GLuint index;
        bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

        if (found) {
            out_indices.append(index);
        } else {
            unique_vertices++;
            out_vertices.append(in_vertices[i]);
            out_uvs.append(in_uvs[i]);
            out_normals.append(in_normals[i]);
            GLuint newindex = (GLuint)out_vertices.size() - 1;
            out_indices.append(newindex);
            VertexToOutIndex[packed] = newindex;
        }
    }
}

QT_END_NAMESPACE_DATAVISUALIZATION
