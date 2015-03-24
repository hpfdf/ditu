# DiTu: an indoor map and locating system.
#
# Pufan He <hpfdf@126.com>
# Qiwei Feng <gdfqw93@163.com>
#
# Desktop map interface.

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ditu
TEMPLATE = app
DESTDIR = ../bin

SOURCES += \
    utils/libJson/json_writer.cpp \
    utils/libJson/json_valueiterator.inl \
    utils/libJson/json_value.cpp \
    utils/libJson/json_reader.cpp \
    utils/libJson/json_internalmap.inl \
    utils/libJson/json_internalarray.inl \
    utils/jsonobject.cpp \
    map/trainer.cpp \
    map/contents.cpp \
    desktop/main.cpp

HEADERS += \
    utils/libJson/writer.h \
    utils/libJson/value.h \
    utils/libJson/reader.h \
    utils/libJson/json_tool.h \
    utils/libJson/json_batchallocator.h \
    utils/libJson/json.h \
    utils/libJson/forwards.h \
    utils/libJson/features.h \
    utils/libJson/config.h \
    utils/libJson/autolink.h \
    utils/jsonobject.h
    map/contents.h
    map/trainer.h

QMAKE_CXXFLAGS += --std=c++0x

