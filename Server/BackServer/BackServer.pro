QT += core
QT -= gui

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
TARGET = BackServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Thread/M_Condition.cpp \
    Epoll/EpollBase.cpp \
    sqlVideo/SqliteBase.cpp \
    sqlVideo/videoSqlite.cpp \
    ShmFIFO.cpp \
    Epoll/BackServer.cpp \
    Thread/ThreadBase.cpp \
    Log/EpollLog.cpp \
    Log/LogBase.cpp \
    Log/LogSystem.cpp \
    Log/TaskLog.cpp \
    Log/BackLog.cpp \
    ../../common/NetPacket/CommonProto.pb.cc \
    ../../common/NetPacket/Factory.cpp \
    ../../common/NetPacket/PacketBase.cpp \
    Log/ThreadLog.cpp \
    Thread/Lock.cpp \
    Thread/ThreadParsdata.cpp


HEADERS += \
    Thread/M_Condition.h \
    Epoll/BackServer.h \
    Epoll/EpollBase.h \
    sqlVideo/SqliteBase.h \
    sqlVideo/videoSqlite.h \
    ShmFIFO.h \
    Thread/ThreadBase.h \
    Log/EpollLog.h \
    Log/LogBase.h \
    Log/LogSystem.h \
    Log/TaskLog.h \
    Log/BackLog.h \
    ../../common/NetPacket/CommonProto.pb.h \
    ../../common/NetPacket/Factory.h \
    ../../common/NetPacket/NetPacket.h \
    ../../common/NetPacket/NetPacket.h.autosave \
    ../../common/NetPacket/PacketBase.h \
    ../../common/NetPacket/public.h \
    Log/ThreadLog.h \
    Thread/Lock.h \
    Thread/M_Condition.h \
    Thread/safeQueue.hpp \
    Thread/ThreadParsdata.h
##INCLUDEPATH += -L/usr/include/log4cplus
LIBS += -lpthread
LIBS += -L/usr/lib/protoc -lprotobuf
LIBS += -L/usr/lib/log4cplus -llog4cplus
unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3
