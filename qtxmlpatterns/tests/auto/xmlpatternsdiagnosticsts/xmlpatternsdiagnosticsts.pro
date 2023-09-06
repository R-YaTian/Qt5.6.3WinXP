TARGET = tst_xmlpatternsdiagnosticsts
CONFIG += testcase
SOURCES += tst_xmlpatternsdiagnosticsts.cpp \
           ../qxmlquery/TestFundament.cpp

include (../xmlpatterns.pri)

TARGET = tst_xmlpatternsdiagnosticsts

HEADERS += ../xmlpatternsxqts/tst_suitetest.h
SOURCES += ../xmlpatternsxqts/tst_suitetest.cpp
LIBS += -L$$QT.xmlpatterns.libs -l$$XMLPATTERNS_SDK

QT += xml testlib

INCLUDEPATH += $$(QTSRCDIR)/tests/auto/xmlpatternssdk  \
               $$(QTDIR)/include/QtXmlPatterns/private \
               $$(QTSRCDIR)/tests/auto/xmlpatternsxqts \
               ../xmlpatternsxqts                      \
               ../xmlpatternssdk

wince* {
   catalog.files = TestSuite Baseline.xml
   catalog.path = .
   DEPLOYMENT += catalog
}

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
requires(contains(QT_CONFIG,private_tests))

