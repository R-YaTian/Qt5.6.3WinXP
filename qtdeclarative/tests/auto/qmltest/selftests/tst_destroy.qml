/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
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

import QtQuick 2.1
import QtTest 1.1

TestCase {
    id: testCase
    width: 100
    height: 100
    name: "SelfTests_Destroy"

    function test_a_QTBUG_30523() {
        compare(testCase.children.length, 0)
        var tmp = Qt.createQmlObject('import QtQuick 2.1; Rectangle {width: 20; height: 20;}', testCase, '')
        compare(testCase.children.length, 1)
        tmp.destroy()
    }

    function test_b_QTBUG_30523() {
        // The object created in test above should be deleted
        compare(testCase.children.length, 0)
    }

    function test_c_QTBUG_42185_data() {
   // Adding dummy data objects for the purpose of calling multiple times the test function
   // and checking that the created object (tmp) is destroyed as expected between each data run.
        return [{tag: "test 0"}, {tag: "test 1"}, {tag: "test 2"},];
    }

    function test_c_QTBUG_42185() {
        compare(testCase.children.length, 0)
        var tmp = Qt.createQmlObject('import QtQuick 2.1; Rectangle {width: 20; height: 20;}', testCase, '')
        compare(testCase.children.length, 1)
        tmp.destroy()
    }

    function test_d_QTBUG_42185() {
        // The object created in test above should be deleted
        compare(testCase.children.length, 0)
    }
}
