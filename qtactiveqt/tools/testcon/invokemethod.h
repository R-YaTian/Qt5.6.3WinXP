/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the tools applications of the Qt Toolkit.
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

#ifndef INVOKEMETHOD_H
#define INVOKEMETHOD_H

#include <QtCore/qglobal.h>
#include "ui_invokemethod.h"

QT_BEGIN_NAMESPACE

class QAxBase;

class InvokeMethod : public QDialog, Ui::InvokeMethod
{
    Q_OBJECT
public:
    InvokeMethod(QWidget *parent);

    void setControl(QAxBase *ax);

protected slots:
    void on_buttonInvoke_clicked();
    void on_buttonSet_clicked();

    void on_comboMethods_activated(const QString &method);
    void on_listParameters_currentItemChanged(QTreeWidgetItem *item);

private:
    QAxBase *activex;
};

QT_END_NAMESPACE

#endif // INVOKEMETHOD_H
