/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTSENSORGESTURESENSORHANDLER_H
#define QTSENSORGESTURESENSORHANDLER_H

#include <QObject>

#include <QtSensors/QAccelerometer>
#include <QtSensors/QAccelerometerFilter>
#include <QtSensors/QSensor>
#include <QtSensors/QOrientationSensor>
#include <QtSensors/QProximitySensor>
#include <QtSensors/QIRProximitySensor>
#include <QtSensors/QTapSensor>

class QtSensorGestureSensorHandler : public QObject
{
    Q_OBJECT
    Q_ENUMS(SensorGestureSensors)
public:
    explicit QtSensorGestureSensorHandler(QObject *parent = 0);

    enum SensorGestureSensors {
        Accel = 0,
        Orientation,
        Proximity,
        IrProximity,
        Tap
    };
    static QtSensorGestureSensorHandler *instance();
    qreal accelRange;

public slots:
    void accelChanged();
    void orientationChanged();
    void proximityChanged();
    void irProximityChanged();
    void doubletap();

    bool startSensor(SensorGestureSensors sensor);
    void stopSensor(SensorGestureSensors sensor);

Q_SIGNALS:
    void accelReadingChanged(QAccelerometerReading *reading);
    void orientationReadingChanged(QOrientationReading *reading);
    void proximityReadingChanged(QProximityReading *reading);
    void irProximityReadingChanged(QIRProximityReading *reading);
    void dTabReadingChanged(QTapReading *reading);

private:
    QAccelerometer *accel;
    QOrientationSensor *orientation;
    QProximitySensor *proximity;
    QIRProximitySensor *irProx;
    QTapSensor *tapSensor;

    QMap<SensorGestureSensors, int> usedSensorsMap;

};

#endif // QTSENSORGESTURESENSORHANDLER_H
