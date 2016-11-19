QT += core
QT -= gui

TARGET = Branch_and_bound
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    graph.cpp \
    graph_algorithms/branck_bound_shortest_way.cpp \
    graph_algorithms/dijkstra_shortest_way.cpp

HEADERS += \
    graph.h \
    orl_algorithms.h

