TARGET = tst_patternistheaders
CONFIG += testcase
SOURCES += tst_patternistheaders.cpp
QT = core testlib

include (../xmlpatterns.pri)
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
