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

#ifndef CHARTTHEMEQT_P_H
#define CHARTTHEMEQT_P_H

#include <private/charttheme_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class ChartThemeQt : public ChartTheme
{
public:
    ChartThemeQt() : ChartTheme(QChart::ChartThemeQt)
    {
        // Series colors
        m_seriesColors << QRgb(0x80c342);
        m_seriesColors << QRgb(0x328930);
        m_seriesColors << QRgb(0x006325);
        m_seriesColors << QRgb(0x35322f);
        m_seriesColors << QRgb(0x5d5b59);
        m_seriesColors << QRgb(0x868482);
        m_seriesColors << QRgb(0xaeadac);
        m_seriesColors << QRgb(0xd7d6d5);
        m_seriesGradients = ChartThemeManager::generateSeriesGradients(m_seriesColors);

        // Background
        QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_labelBrush = QBrush(QRgb(0x35322f));
        m_axisLinePen = QPen(QRgb(0xd7d6d5));
        m_axisLinePen.setWidth(1);
        m_gridLinePen = QPen(QRgb(0xd7d6d5));
        m_gridLinePen.setWidth(1);
        m_minorGridLinePen = QPen(QRgb(0xd7d6d5));
        m_minorGridLinePen.setWidth(1);
        m_minorGridLinePen.setStyle(Qt::DashLine);
        m_backgroundShades = BackgroundShadesNone;
        m_outlinePen = QPen(QRgb(0x35322f));
        m_outlinePen.setWidthF(2.0);
    }
};

QT_CHARTS_END_NAMESPACE

#endif
