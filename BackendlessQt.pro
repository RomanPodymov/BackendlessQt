CONFIG += c++20 warn_on

QT += core network

TEMPLATE = lib

DEFINES += MAKE_TEST_LIB

TARGET = BackendlessQt

SOURCES += \
    BasicAPI.cpp \
    BackendlessAPI.cpp \
    BackendlessUserAPI.cpp

HEADERS += \
    BasicAPI.hpp \
    BackendlessAPI.hpp \
    BackendlessUserAPI.hpp \
    BackendlessUser.hpp

ios {
    CONFIG += staticlib
}
macos {
    CONFIG += staticlib
}
