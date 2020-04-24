#-------------------------------------------------
#
# Project created by QtCreator 2019-10-21T20:55:49
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Text_Press
TEMPLATE = app
LIBS += -lpthread
LIBS += -L/usr/lib/protoc -lprotobuf

SOURCES += main.cpp\
        fun_connect.cpp \
    loginwidget.cpp \
    Base/HostAddress.cpp \
    Base/CEpollBase.cpp \
    Base/CBaseThread.cpp \
    Base/CBaseStream.cpp \
    Base/CBaseSocket.cpp \
    Pthread/CThreadPool.cpp \
    Pthread/CPThreadMutex.cpp \
    Pthread/CPThreadCond.cpp \
    Texting.cpp \
    TcpSocket.cpp \
    TaskEpoll.cpp \
    ShmFIFO.cpp \
    SettingText.cpp \
    ResultText.cpp \
    Task.cpp \
    CEpollClient.cpp \
    ../common/NetPacket/PacketBase.cpp \
    ../common/NetPacket/CommonProto.pb.cc
HEADERS  += fun_connect.h \
    loginwidget.h \
    Base/HostAddress.h \
    Base/CEpollBase.h \
    Base/CBaseThread.h \
    Base/CBaseStream.h \
    Base/CBaseSocket.h \
    Pthread/CThreadPool.h \
    Pthread/CPThreadMutex.h \
    Pthread/CPThreadCond.h \
    Texting.h \
    TcpSocket.h \
    TaskEpoll.h \
    ShmFIFO.h \
    SettingText.h \
    ResultText.h \
    Task.h \
    CEpollClient.h \
    ../common/NetPacket/NetPacket.h \
    ../common/NetPacket/PacketBase.h \
    ../common/NetPacket/public.h \
    ../common/NetPacket/CommonProto.pb.h
