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

#ifndef Q3DOBJECT_P_H
#define Q3DOBJECT_P_H

#include "datavisualizationglobal_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class Q3DObject;
class Q3DScene;

class Q3DObjectPrivate
{
public:
    Q3DObjectPrivate(Q3DObject *q);
    ~Q3DObjectPrivate();

public:
    Q3DObject *q_ptr;
    QVector3D m_position;
    bool m_isDirty;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
