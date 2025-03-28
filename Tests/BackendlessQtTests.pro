QT += testlib

CONFIG += core gui widgets qt testcase c++20 warn_on

QT += network

TEMPLATE = app

SOURCES += \
    test.cpp

SOURCES += \
    ../BasicAPI.cpp \
    ../BackendlessAPI.cpp \
    ../BackendlessUserAPI.cpp \
    ../BackendlessUser.cpp \
    ../StandardNetworkManager.cpp

HEADERS += \
    ../BasicAPI.hpp \
    ../BackendlessAPI.hpp \
    ../BackendlessUserAPI.hpp \
    ../BackendlessUser.hpp \
    ../StandardNetworkManager.hpp
