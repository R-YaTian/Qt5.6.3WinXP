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

#include <QtTest/QtTest>

#include <QtDataVisualization/QSurface3DSeries>

using namespace QtDataVisualization;

class tst_series: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void construct();

    void initialProperties();
    void initializeProperties();
    void invalidProperties();

private:
    QSurface3DSeries *m_series;
};

void tst_series::initTestCase()
{
}

void tst_series::cleanupTestCase()
{
}

void tst_series::init()
{
    m_series = new QSurface3DSeries();
}

void tst_series::cleanup()
{
    delete m_series;
}

void tst_series::construct()
{
    QSurface3DSeries *series = new QSurface3DSeries();
    QVERIFY(series);
    delete series;

    QSurfaceDataProxy *proxy = new QSurfaceDataProxy();

    series = new QSurface3DSeries(proxy);
    QVERIFY(series);
    QCOMPARE(series->dataProxy(), proxy);
    delete series;
}

void tst_series::initialProperties()
{
    QVERIFY(m_series);

    QVERIFY(m_series->dataProxy());
    QCOMPARE(m_series->drawMode(), QSurface3DSeries::DrawSurfaceAndWireframe);
    QCOMPARE(m_series->isFlatShadingEnabled(), true);
    QCOMPARE(m_series->isFlatShadingSupported(), true);
    QCOMPARE(m_series->selectedPoint(), m_series->invalidSelectionPosition());

    // Common properties. The ones identical between different series are tested in QBar3DSeries tests
    QCOMPARE(m_series->itemLabelFormat(), QString("@xLabel, @yLabel, @zLabel"));
    QCOMPARE(m_series->mesh(), QAbstract3DSeries::MeshSphere);
    QCOMPARE(m_series->type(), QAbstract3DSeries::SeriesTypeSurface);
}

void tst_series::initializeProperties()
{
    QVERIFY(m_series);

    m_series->setDataProxy(new QSurfaceDataProxy());
    m_series->setDrawMode(QSurface3DSeries::DrawWireframe);
    m_series->setFlatShadingEnabled(false);
    m_series->setSelectedPoint(QPoint(0, 0));

    QCOMPARE(m_series->drawMode(), QSurface3DSeries::DrawWireframe);
    QCOMPARE(m_series->isFlatShadingEnabled(), false);
    QCOMPARE(m_series->selectedPoint(), QPoint(0, 0));

    // Common properties. The ones identical between different series are tested in QBar3DSeries tests
    m_series->setMesh(QAbstract3DSeries::MeshPyramid);

    QCOMPARE(m_series->mesh(), QAbstract3DSeries::MeshPyramid);
}

void tst_series::invalidProperties()
{
    m_series->setMesh(QAbstract3DSeries::MeshPoint);

    QCOMPARE(m_series->mesh(), QAbstract3DSeries::MeshSphere);
}

QTEST_MAIN(tst_series)
#include "tst_series.moc"
