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

#ifndef DECLARATIVEPIESERIES_H
#define DECLARATIVEPIESERIES_H

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlParserStatus>

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativePieSlice : public QPieSlice
{
    Q_OBJECT
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged)

public:
    explicit DeclarativePieSlice(QObject *parent = 0);
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);

Q_SIGNALS:
    void brushFilenameChanged(const QString &brushFilename);

private Q_SLOTS:
    void handleBrushChanged();

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

class DeclarativePieSeries : public QPieSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativePieSeries(QQuickItem *parent = 0);
    QQmlListProperty<QObject> seriesChildren();
    Q_INVOKABLE QPieSlice *at(int index);
    Q_INVOKABLE QPieSlice *find(QString label);
    Q_INVOKABLE DeclarativePieSlice *append(QString label, qreal value);
    Q_INVOKABLE bool remove(QPieSlice *slice);
    Q_INVOKABLE void clear();

public:
    void classBegin();
    void componentComplete();

Q_SIGNALS:
    void sliceAdded(QPieSlice *slice);
    void sliceRemoved(QPieSlice *slice);

public Q_SLOTS:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);
    void handleAdded(QList<QPieSlice *> slices);
    void handleRemoved(QList<QPieSlice *> slices);
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVEPIESERIES_H
