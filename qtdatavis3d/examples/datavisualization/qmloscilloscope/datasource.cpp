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

#include "datasource.h"
#include <QtCore/qmath.h>

using namespace QtDataVisualization;

//! [3]
Q_DECLARE_METATYPE(QSurface3DSeries *)
//! [3]

DataSource::DataSource(QObject *parent) :
    QObject(parent),
    m_index(-1),
    m_resetArray(0)
{
    //! [4]
    qRegisterMetaType<QSurface3DSeries *>();
    //! [4]
}

DataSource::~DataSource()
{
    clearData();
}

//! [0]
void DataSource::generateData(int cacheCount, int rowCount, int columnCount,
                              float xMin, float xMax, float yMin, float yMax,
                              float zMin, float zMax)
{
    if (!cacheCount || !rowCount || !columnCount)
        return;

    clearData();
    // Re-create the cache array
    m_data.resize(cacheCount);
    for (int i(0); i < cacheCount; i++) {
        QSurfaceDataArray &array = m_data[i];
        array.reserve(rowCount);
        for (int j(0); j < rowCount; j++)
            array.append(new QSurfaceDataRow(columnCount));
    }

    float xRange = xMax - xMin;
    float yRange = yMax - yMin;
    float zRange = zMax - zMin;
    int cacheIndexStep = columnCount / cacheCount;
    float cacheStep = float(cacheIndexStep) * xRange / float(columnCount);

    // Populate caches
    for (int i(0); i < cacheCount; i++) {
        QSurfaceDataArray &cache = m_data[i];
        float cacheXAdjustment = cacheStep * i;
        float cacheIndexAdjustment = cacheIndexStep * i;
        for (int j(0); j < rowCount; j++) {
            QSurfaceDataRow &row = *(cache[j]);
            float rowMod = (float(j)) / float(rowCount);
            float yRangeMod = yRange * rowMod;
            float zRangeMod = zRange * rowMod;
            float z = zRangeMod + zMin;
            qreal rowColWaveAngleMul = M_PI * M_PI * rowMod;
            float rowColWaveMul = yRangeMod * 0.2f;
            for (int k(0); k < columnCount; k++) {
                float colMod = (float(k)) / float(columnCount);
                float xRangeMod = xRange * colMod;
                float x = xRangeMod + xMin + cacheXAdjustment;
                float colWave = float(qSin((2.0 * M_PI * colMod) - (1.0 / 2.0 * M_PI)) + 1.0);
                float y = (colWave * ((float(qSin(rowColWaveAngleMul * colMod) + 1.0))))
                        * rowColWaveMul
                        + (0.15f * float(qrand()) / float(RAND_MAX)) * yRangeMod;

                int index = k + cacheIndexAdjustment;
                if (index >= columnCount) {
                    // Wrap over
                    index -= columnCount;
                    x -= xRange;
                }
                row[index] = QVector3D(x, y, z);
            }
        }
    }
}
//! [0]

//! [1]
void DataSource::update(QSurface3DSeries *series)
{
    if (series && m_data.size()) {
        // Each iteration uses data from a different cached array
        m_index++;
        if (m_index > m_data.count() - 1)
            m_index = 0;

        QSurfaceDataArray array = m_data.at(m_index);
        int newRowCount = array.size();
        int newColumnCount = array.at(0)->size();

        // If the first time or the dimensions of the cache array have changed,
        // reconstruct the reset array
        if (m_resetArray || series->dataProxy()->rowCount() != newRowCount
                || series->dataProxy()->columnCount() != newColumnCount) {
            m_resetArray = new QSurfaceDataArray();
            m_resetArray->reserve(newRowCount);
            for (int i(0); i < newRowCount; i++)
                m_resetArray->append(new QSurfaceDataRow(newColumnCount));
        }

        // Copy items from our cache to the reset array
        for (int i(0); i < newRowCount; i++) {
            const QSurfaceDataRow &sourceRow = *(array.at(i));
            QSurfaceDataRow &row = *(*m_resetArray)[i];
            for (int j(0); j < newColumnCount; j++)
                row[j].setPosition(sourceRow.at(j).position());
        }

        // Notify the proxy that data has changed
        series->dataProxy()->resetArray(m_resetArray);
    }
}
//! [1]

void DataSource::clearData()
{
    for (int i(0); i < m_data.size(); i++) {
        QSurfaceDataArray &array = m_data[i];
        for (int j(0); j < array.size(); j++)
            delete array[j];
        array.clear();
    }
}
