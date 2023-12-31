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

#ifndef DECLARATIVETHEME_P_H
#define DECLARATIVETHEME_P_H

#include "datavisualizationglobal_p.h"
#include "declarativecolor_p.h"
#include "colorgradient_p.h"
#include "q3dtheme_p.h"

#include <QtQml/QQmlParserStatus>

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class DeclarativeTheme3D : public Q3DTheme, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> themeChildren READ themeChildren)
    Q_PROPERTY(QQmlListProperty<DeclarativeColor> baseColors READ baseColors)
    Q_PROPERTY(QQmlListProperty<ColorGradient> baseGradients READ baseGradients)
    Q_PROPERTY(ColorGradient *singleHighlightGradient READ singleHighlightGradient WRITE setSingleHighlightGradient NOTIFY singleHighlightGradientChanged)
    Q_PROPERTY(ColorGradient *multiHighlightGradient READ multiHighlightGradient WRITE setMultiHighlightGradient NOTIFY multiHighlightGradientChanged)
    Q_CLASSINFO("DefaultProperty", "themeChildren")

public:
    DeclarativeTheme3D(QObject *parent = 0);
    virtual ~DeclarativeTheme3D();

    QQmlListProperty<QObject> themeChildren();
    static void appendThemeChildren(QQmlListProperty<QObject> *list, QObject *element);

    QQmlListProperty<DeclarativeColor> baseColors();
    static void appendBaseColorsFunc(QQmlListProperty<DeclarativeColor> *list,
                                     DeclarativeColor *color);
    static int countBaseColorsFunc(QQmlListProperty<DeclarativeColor> *list);
    static DeclarativeColor *atBaseColorsFunc(QQmlListProperty<DeclarativeColor> *list, int index);
    static void clearBaseColorsFunc(QQmlListProperty<DeclarativeColor> *list);

    QQmlListProperty<ColorGradient> baseGradients();
    static void appendBaseGradientsFunc(QQmlListProperty<ColorGradient> *list,
                                        ColorGradient *gradient);
    static int countBaseGradientsFunc(QQmlListProperty<ColorGradient> *list);
    static ColorGradient *atBaseGradientsFunc(QQmlListProperty<ColorGradient> *list, int index);
    static void clearBaseGradientsFunc(QQmlListProperty<ColorGradient> *list);

    void setSingleHighlightGradient(ColorGradient *gradient);
    ColorGradient *singleHighlightGradient() const;

    void setMultiHighlightGradient(ColorGradient *gradient);
    ColorGradient *multiHighlightGradient() const;

    // From QQmlParserStatus
    virtual void classBegin();
    virtual void componentComplete();

Q_SIGNALS:
    void singleHighlightGradientChanged(ColorGradient *gradient);
    void multiHighlightGradientChanged(ColorGradient *gradient);

protected:
    void handleTypeChange(Theme themeType);
    void handleBaseColorUpdate();
    void handleBaseGradientUpdate();
    void handleSingleHLGradientUpdate();
    void handleMultiHLGradientUpdate();

    enum GradientType {
        GradientTypeBase = 0,
        GradientTypeSingleHL,
        GradientTypeMultiHL
    };

private:
    void addColor(DeclarativeColor *color);
    QList<DeclarativeColor *> colorList();
    void clearColors();
    void clearDummyColors();

    void addGradient(ColorGradient *gradient);
    QList<ColorGradient *> gradientList();
    void clearGradients();
    void clearDummyGradients();

    void setThemeGradient(ColorGradient *gradient, GradientType type);
    QLinearGradient convertGradient(ColorGradient *gradient);
    ColorGradient *convertGradient(const QLinearGradient &gradient);

    QList<DeclarativeColor *> m_colors; // Not owned
    QList<ColorGradient *> m_gradients; // Not owned
    ColorGradient *m_singleHLGradient; // Not owned
    ColorGradient *m_multiHLGradient; // Not owned

    bool m_dummyGradients;
    bool m_dummyColors;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
