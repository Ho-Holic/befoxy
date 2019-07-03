#-------------------------------------------------
#
# Project created by QtCreator 2018-09-04T23:31:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = befoxy
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        visual/Befoxy.cpp \
    core/DataStorage.cpp \
    core/Engine.cpp \
    core/Services.cpp \
    core/Conversion.cpp \
    visual/NewDayWatcher.cpp \
    visual/IconGenerator.cpp \
    visual/TapLabel.cpp \
    visual/ColorScheme.cpp

HEADERS  += visual/Befoxy.hpp \
    core/Serializer.hpp \
    core/DataStorage.hpp \
    core/Engine.hpp \
    core/Component.hpp \
    core/Services.hpp \
    visual/Component.hpp \
    style/Guidelines.hpp \
    core/utility/MirrorMap.hpp \
    core/Conversion.hpp \
    visual/Conversion.hpp \
    visual/NewDayWatcher.hpp \
    visual/IconGenerator.hpp \
    visual/TapLabel.hpp \
    core/Methods.hpp \
    visual/ColorScheme.hpp \
    style/Backport.hpp

