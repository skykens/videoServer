QT += core
QT -= gui

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
TARGET = FrontServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    Epoll/EpollBase.cpp \
    Epoll/EpollServer.cpp \
    sqlVideo/SqliteBase.cpp \
    sqlVideo/videoSqlite.cpp \
    TCP/TCPClient.cpp \
    TCP/TCPServer.cpp \
    TCP/TCPSocket.cpp \
    Thread/M_Condition.cpp \
    ShmFIFO.cpp \
    Thread/ThreadBase.cpp \
    Thread/ThreadPool.cpp \
    Thread/ThreadPoolTask.cpp \
    Log/LogBase.cpp \
    Log/LogSystem.cpp \
    Log/TaskLog.cpp \
    Thread/Task/TaskBase.cpp \
    Thread/Task/ClientTask.cpp \
    Thread/Task/ListenMemTask.cpp \
    Thread/Task/ListenClientTask.cpp \
    Log/EpollLog.cpp \
    main.cpp \
    Log/MallocLog.cpp \
    ../../common/NetPacket/CommonProto.pb.cc \
    ../../common/NetPacket/PacketBase.cpp \
    ../../common/NetPacket/Config.cpp \
    Log/ThreadLog.cpp \
    coreGui.cpp \
    Thread/Lock.cpp

HEADERS += \
    Epoll/EpollBase.h \
    Epoll/EpollServer.h \
    sqlVideo/SqliteBase.h \
    sqlVideo/videoSqlite.h \
    TCP/TCPClient.h \
    TCP/TCPServer.h \
    TCP/TCPSocket.h \
    Thread/M_Condition.h \
    ShmFIFO.h \
    Thread/ThreadBase.h \
    Thread/ThreadPool.h \
    Thread/ThreadPoolTask.h \
    Log/LogBase.h \
    Log/LogSystem.h \
    Log/TaskLog.h \
    Thread/Task/TaskBase.h \
    Thread/Task/ClientTask.h \
    Thread/Task/ListenMemTask.h \
    Thread/Task/ListenClientTask.h \
    Log/EpollLog.h \
    Log/MallocLog.h \
    ../../common/NetPacket/CommonProto.pb.h \
    ../../common/NetPacket/NetPacket.h \
    ../../common/NetPacket/PacketBase.h \
    ../../common/NetPacket/public.h \
    ../../common/NetPacket/Config.h \
    Log/ThreadLog.h \
    coreGui.h \
    Thread/Lock.h \
    Thread/safeQueue.hpp
unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3
LIBS += -lpthread
LIBS += -L/usr/lib/protoc -lprotobuf
LIBS += -L/usr/lib/log4cplus -llog4cplus
INCLUDEPATH += -L/usr/include/log4cplus
