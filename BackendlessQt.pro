CONFIG += c++20 warn_on staticlib

QT += core network

TEMPLATE = lib

SOURCES += \
    BackendlessAPI.cpp \
    BackendlessUserAPI.cpp

HEADERS += \
    BackendlessAPI.hpp \
    BackendlessUserAPI.hpp \
    BackendlessUser.hpp
