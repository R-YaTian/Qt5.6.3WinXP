/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -p manager_p.h:manager.cpp org.bluez.Manager.xml org.bluez.Manager
 *
 * Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "manager_p.h"

/*
 * Implementation of interface class OrgBluezManagerInterface
 */

OrgBluezManagerInterface::OrgBluezManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OrgBluezManagerInterface::~OrgBluezManagerInterface()
{
}

