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

#include "surfacegraph.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtGui/QScreen>
#include <QtGui/QPainter>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q3DSurface *graph = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    widget->setWindowTitle(QStringLiteral("Textured surface example"));

    QCheckBox *enableTexture = new QCheckBox(widget);
    enableTexture->setText(QStringLiteral("Surface texture"));

    int height = 400;
    int width = 100;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    gr.setColorAt(1.0f, Qt::black);
    gr.setColorAt(0.8f, Qt::darkGreen);
    gr.setColorAt(0.6f, Qt::green);
    gr.setColorAt(0.4f, Qt::yellow);
    gr.setColorAt(0.2f, Qt::red);
    gr.setColorAt(0.0f, Qt::darkRed);

    QPixmap pm(width, height);
    pm.fill(Qt::transparent);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(gr));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(border, border, 35, height - 2 * border);
    pmp.setPen(Qt::black);
    int step = (height - 2 * border) / 5;
    for (int i = 0; i < 6; i++) {
        int yPos = i * step + border;
        pmp.drawLine(border, yPos, 55, yPos);
        pmp.drawText(60, yPos + 2, QString("%1 m").arg(550 - (i * 110)));
    }

    QLabel *label = new QLabel(widget);
    label->setPixmap(pm);

    QGroupBox *heightMapGroupBox = new QGroupBox(QStringLiteral("Highlight color map"));
    QVBoxLayout *colorMapVBox = new QVBoxLayout;
    colorMapVBox->addWidget(label);
    heightMapGroupBox->setLayout(colorMapVBox);

    vLayout->addWidget(enableTexture);
    vLayout->addWidget(heightMapGroupBox);

    widget->show();

    SurfaceGraph *modifier = new SurfaceGraph(graph);

    QObject::connect(enableTexture, &QCheckBox::stateChanged,
                     modifier, &SurfaceGraph::toggleSurfaceTexture);

    enableTexture->setChecked(true);

    return app.exec();
}
