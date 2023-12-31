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

#ifndef QCUSTOMLABELITEM_H
#define QCUSTOMLABELITEM_H

#include <QtDataVisualization/qdatavisualizationglobal.h>
#include <QtDataVisualization/QCustom3DItem>
#include <QtGui/QVector3D>
#include <QtGui/QQuaternion>
#include <QtGui/QFont>
#include <QtGui/QColor>

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class QCustom3DLabelPrivate;

class QT_DATAVISUALIZATION_EXPORT QCustom3DLabel : public QCustom3DItem
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(bool borderEnabled READ isBorderEnabled WRITE setBorderEnabled NOTIFY borderEnabledChanged)
    Q_PROPERTY(bool backgroundEnabled READ isBackgroundEnabled WRITE setBackgroundEnabled NOTIFY backgroundEnabledChanged)
    Q_PROPERTY(bool facingCamera READ isFacingCamera WRITE setFacingCamera NOTIFY facingCameraChanged)

public:
    explicit QCustom3DLabel(QObject *parent = Q_NULLPTR);
    explicit QCustom3DLabel(const QString &text, const QFont &font, const QVector3D &position,
                            const QVector3D &scaling, const QQuaternion &rotation,
                            QObject *parent = Q_NULLPTR);
    virtual ~QCustom3DLabel();

    void setText(const QString &text);
    QString text() const;

    void setFont(const QFont &font);
    QFont font() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setBorderEnabled(bool enabled);
    bool isBorderEnabled() const;

    void setBackgroundEnabled(bool enabled);
    bool isBackgroundEnabled() const;

    void setFacingCamera(bool enabled);
    bool isFacingCamera() const;

Q_SIGNALS:
    void textChanged(const QString &text);
    void fontChanged(const QFont &font);
    void textColorChanged(const QColor &color);
    void backgroundColorChanged(const QColor &color);
    void borderEnabledChanged(bool enabled);
    void backgroundEnabledChanged(bool enabled);
    void facingCameraChanged(bool enabled);

protected:
    QCustom3DLabelPrivate *dptr();
    const QCustom3DLabelPrivate *dptrc() const;

private:
    Q_DISABLE_COPY(QCustom3DLabel)

    friend class Abstract3DRenderer;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
