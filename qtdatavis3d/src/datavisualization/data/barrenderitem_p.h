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

#ifndef BARRENDERITEM_P_H
#define BARRENDERITEM_P_H

#include "abstractrenderitem_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class BarRenderItem : public AbstractRenderItem
{
public:
    BarRenderItem();
    BarRenderItem(const BarRenderItem &other);
    virtual ~BarRenderItem();

    // Position relative to data window (for bar label generation)
    inline void setPosition(const QPoint &pos) { m_position = pos; }
    inline const QPoint &position() const { return m_position; }

    // Actual cached data value of the bar (needed to trigger label reformats)
    inline void setValue(float value) { m_value = value; }
    inline float value() const { return m_value; }

    // Normalized bar height
    inline void setHeight(GLfloat height) { m_height = height; }
    inline GLfloat height() const { return m_height; }

protected:
    float m_value;
    QPoint m_position; // x = row, y = column
    GLfloat m_height;

    friend class QBarDataItem;
};

class BarRenderSliceItem : public BarRenderItem
{
public:
    BarRenderSliceItem();
    BarRenderSliceItem(const BarRenderSliceItem &other);
    virtual ~BarRenderSliceItem();

    void setItem(const BarRenderItem &renderItem);

    // Label item for formatted label
    LabelItem &sliceLabelItem();

    // Formatted label for item.
    void setSliceLabel(const QString &label);
    const QString &sliceLabel() const; // Formats label if not previously formatted

protected:
    QString m_sliceLabel;
    LabelItem *m_sliceLabelItem;
    bool m_isNull;
};

typedef QVector<BarRenderItem> BarRenderItemRow;
typedef QVector<BarRenderItemRow> BarRenderItemArray;

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
