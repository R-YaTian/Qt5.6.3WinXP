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

#ifndef QITEMMODELSURFACEDATAPROXY_P_H
#define QITEMMODELSURFACEDATAPROXY_P_H

#include "qitemmodelsurfacedataproxy.h"
#include "qsurfacedataproxy_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class SurfaceItemModelHandler;

class QItemModelSurfaceDataProxyPrivate : public QSurfaceDataProxyPrivate
{
    Q_OBJECT
public:
    QItemModelSurfaceDataProxyPrivate(QItemModelSurfaceDataProxy *q);
    virtual ~QItemModelSurfaceDataProxyPrivate();

    void connectItemModelHandler();

private:
    QItemModelSurfaceDataProxy *qptr();

    SurfaceItemModelHandler *m_itemModelHandler;

    QString m_rowRole;
    QString m_columnRole;
    QString m_xPosRole;
    QString m_yPosRole;
    QString m_zPosRole;

    // For row/column items, sort items into these categories. Other categories are ignored.
    QStringList m_rowCategories;
    QStringList m_columnCategories;

    bool m_useModelCategories;
    bool m_autoRowCategories;
    bool m_autoColumnCategories;

    QRegExp m_rowRolePattern;
    QRegExp m_columnRolePattern;
    QRegExp m_xPosRolePattern;
    QRegExp m_yPosRolePattern;
    QRegExp m_zPosRolePattern;

    QString m_rowRoleReplace;
    QString m_columnRoleReplace;
    QString m_xPosRoleReplace;
    QString m_yPosRoleReplace;
    QString m_zPosRoleReplace;

    QItemModelSurfaceDataProxy::MultiMatchBehavior m_multiMatchBehavior;

    friend class SurfaceItemModelHandler;
    friend class QItemModelSurfaceDataProxy;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
