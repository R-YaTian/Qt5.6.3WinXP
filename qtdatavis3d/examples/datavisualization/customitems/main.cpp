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

#include "customitemgraph.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q3DSurface *graph = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);

    container->setMinimumSize(QSize(800, 600));
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayoutLeft = new QVBoxLayout();
    vLayoutLeft->setAlignment(Qt::AlignTop);
    QVBoxLayout *vLayoutRight = new QVBoxLayout();
    vLayoutRight->setAlignment(Qt::AlignTop);
    hLayout->addLayout(vLayoutLeft);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayoutRight);

    QFont font = QFont("Century Gothic", 14);
    QLabel *label = new QLabel("Show:");
    font.setBold(true);
    label->setFont(font);
    vLayoutLeft->addWidget(label);

    font.setBold(false);
    QCheckBox *checkboxOne = new QCheckBox("Oil Rig 1");
    checkboxOne->setChecked(true);
    checkboxOne->setFont(font);
    vLayoutLeft->addWidget(checkboxOne);

    QCheckBox *checkboxTwo = new QCheckBox("Oil Rig 2");
    checkboxTwo->setChecked(true);
    checkboxTwo->setFont(font);
    vLayoutLeft->addWidget(checkboxTwo);

    QCheckBox *checkboxThree = new QCheckBox("Refinery");
    checkboxThree->setFont(font);
    vLayoutLeft->addWidget(checkboxThree);

    QLabel *label2 = new QLabel("Visuals:");
    font.setBold(true);
    label2->setFont(font);
    vLayoutRight->addWidget(label2);

    QCheckBox *checkboxOneRight = new QCheckBox("See-Through");
    font.setBold(false);
    checkboxOneRight->setFont(font);
    vLayoutRight->addWidget(checkboxOneRight);

    QCheckBox *checkboxTwoRight = new QCheckBox("Highlight Oil");
    checkboxTwoRight->setFont(font);
    vLayoutRight->addWidget(checkboxTwoRight);

    QCheckBox *checkboxThreeRight = new QCheckBox("Shadows");
    checkboxThreeRight->setFont(font);
    checkboxThreeRight->setChecked(true);
    vLayoutRight->addWidget(checkboxThreeRight);

    QLabel *label3 = new QLabel("Selection:");
    font.setBold(true);
    label3->setFont(font);
    vLayoutRight->addWidget(label3);

    QLabel *label4 = new QLabel("Nothing");
    font.setBold(false);
    font.setPointSize(11);
    label4->setFont(font);
    vLayoutRight->addWidget(label4);

    widget->setWindowTitle(QStringLiteral("Custom Items Example"));

    widget->show();

    CustomItemGraph *modifier = new CustomItemGraph(graph, label4);

    QObject::connect(checkboxOne, &QCheckBox::stateChanged,
                     modifier, &CustomItemGraph::toggleItemOne);
    QObject::connect(checkboxTwo, &QCheckBox::stateChanged,
                     modifier, &CustomItemGraph::toggleItemTwo);
    QObject::connect(checkboxThree, &QCheckBox::stateChanged,
                     modifier, &CustomItemGraph::toggleItemThree);

    QObject::connect(checkboxOneRight, &QCheckBox::stateChanged,
                     modifier, &CustomItemGraph::toggleSeeThrough);
    QObject::connect(checkboxTwoRight, &QCheckBox::stateChanged,
                     modifier, &CustomItemGraph::toggleOilHighlight);
    QObject::connect(checkboxThreeRight, &QCheckBox::stateChanged,
                     modifier, &CustomItemGraph::toggleShadows);

    return app.exec();
}
