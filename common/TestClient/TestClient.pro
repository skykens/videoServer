TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpthread
LIBS += -L/usr/lib/protoc -lprotobuf
SOURCES += main.cpp \
    ../CommonProto.pb.cc

HEADERS += \
    ../CommonProto.pb.h
