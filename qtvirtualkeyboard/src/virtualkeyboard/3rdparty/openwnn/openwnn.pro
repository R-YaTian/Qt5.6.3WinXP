TEMPLATE = lib
QT += core-private
QT -= gui
TARGET = openwnn
VERSION = 1.3.6
CONFIG += staticlib
CONFIG += warn_off

build_pass {
    CONFIG(debug, debug|release): SUBPATH = debug
    else: SUBPATH = release
} else {
    debug_and_release: CONFIG += build_all
}

DESTDIR = $$SUBPATH

INCLUDEPATH += \
    wnnDictionary/include \
    wnnEngine/include

SOURCES += \
    wnnDictionary/engine/ndapi.c \
    wnnDictionary/engine/ndbdic.c \
    wnnDictionary/engine/ndcommon.c \
    wnnDictionary/engine/ndfdic.c \
    wnnDictionary/engine/ndldic.c \
    wnnDictionary/engine/ndrdic.c \
    wnnDictionary/engine/neapi.c \
    wnnDictionary/engine/necode.c \
    wnnDictionary/engine/nj_str.c \
    wnnEngine/WnnJpnDic.c \
    wnnEngine/openwnndictionary.cpp \
    wnnEngine/openwnnenginejajp.cpp \
    wnnEngine/openwnnclauseconverterjajp.cpp \
    wnnEngine/kanaconverter.cpp \
    wnnEngine/composingtext.cpp \
    wnnEngine/letterconverter.cpp \
    wnnEngine/romkan.cpp \
    wnnEngine/romkanfullkatakana.cpp \
    wnnEngine/romkanhalfkatakana.cpp

HEADERS += \
    wnnDictionary/include/nj_dic.h \
    wnnDictionary/include/nj_err.h \
    wnnDictionary/include/nj_ext.h \
    wnnDictionary/include/nj_lib.h \
    wnnDictionary/include/njd.h \
    wnnDictionary/include/njx_lib.h \
    wnnEngine/predef_table.h \
    wnnEngine/include/openwnndictionary.h \
    wnnEngine/include/openwnnenginejajp.h \
    wnnEngine/include/openwnnclauseconverterjajp.h \
    wnnEngine/include/wnnword.h \
    wnnEngine/include/kanaconverter.h \
    wnnEngine/include/composingtext.h \
    wnnEngine/include/strsegment.h \
    wnnEngine/include/letterconverter.h \
    wnnEngine/include/romkan.h \
    wnnEngine/include/romkanfullkatakana.h \
    wnnEngine/include/romkanhalfkatakana.h
