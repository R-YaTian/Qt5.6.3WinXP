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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef BOXPLOTANIMATION_P_H
#define BOXPLOTANIMATION_P_H

#include <private/chartanimation_p.h>
#include <private/boxwhiskers_p.h>
#include <private/boxwhiskersdata_p.h>
#include <private/boxwhiskersanimation_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class BoxPlotChartItem;

class BoxPlotAnimation : public QObject
{
    Q_OBJECT
public:
    BoxPlotAnimation(BoxPlotChartItem *item, int duration, QEasingCurve &curve);
    ~BoxPlotAnimation();

    void addBox(BoxWhiskers *box);
    ChartAnimation *boxAnimation(BoxWhiskers *box);
    ChartAnimation *boxChangeAnimation(BoxWhiskers *box);

    void setAnimationStart(BoxWhiskers *box);
    void stopAll();
    void removeBoxAnimation(BoxWhiskers *box);

protected:
    BoxPlotChartItem *m_item;
    QHash<BoxWhiskers *, BoxWhiskersAnimation *> m_animations;
    int m_animationDuration;
    QEasingCurve m_animationCurve;
};

QT_CHARTS_END_NAMESPACE

#endif // BOXPLOTANIMATION_P_H
