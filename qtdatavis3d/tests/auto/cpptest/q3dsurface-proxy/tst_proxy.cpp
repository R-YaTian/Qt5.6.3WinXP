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

#include <QtDataVisualization/QSurfaceDataProxy>

using namespace QtDataVisualization;

class tst_proxy: public QObject
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

private:
    QSurfaceDataProxy *m_proxy;
};

void tst_proxy::initTestCase()
{
}

void tst_proxy::cleanupTestCase()
{
}

void tst_proxy::init()
{
    m_proxy = new QSurfaceDataProxy();
}

void tst_proxy::cleanup()
{
    delete m_proxy;
}

void tst_proxy::construct()
{
    QSurfaceDataProxy *proxy = new QSurfaceDataProxy();
    QVERIFY(proxy);
    delete proxy;
}

void tst_proxy::initialProperties()
{
    QVERIFY(m_proxy);

    QCOMPARE(m_proxy->columnCount(), 0);
    QCOMPARE(m_proxy->rowCount(), 0);
    QVERIFY(!m_proxy->series());

    QCOMPARE(m_proxy->type(), QAbstractDataProxy::DataTypeSurface);
}

void tst_proxy::initializeProperties()
{
    QVERIFY(m_proxy);

    QSurfaceDataArray *data = new QSurfaceDataArray;
    QSurfaceDataRow *dataRow1 = new QSurfaceDataRow;
    QSurfaceDataRow *dataRow2 = new QSurfaceDataRow;
    *dataRow1 << QVector3D(0.0f, 0.1f, 0.5f) << QVector3D(1.0f, 0.5f, 0.5f);
    *dataRow2 << QVector3D(0.0f, 1.8f, 1.0f) << QVector3D(1.0f, 1.2f, 1.0f);
    *data << dataRow1 << dataRow2;

    m_proxy->resetArray(data);

    QCOMPARE(m_proxy->columnCount(), 2);
    QCOMPARE(m_proxy->rowCount(), 2);
}

QTEST_MAIN(tst_proxy)
#include "tst_proxy.moc"
