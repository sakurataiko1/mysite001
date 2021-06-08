android|ios|winrt {
    error( "This example is not supported for android, ios, or winrt." )
}

#!include( ../examples.pri ) {
#    error( "Couldn't find the examples.pri file!" )
#}
TEMPLATE = app

QT += datavisualization

#contains(TARGET, qml.*) {
#    QT += qml quick
#}


SOURCES += main.cpp \
           customitemgraph.cpp

HEADERS += customitemgraph.h

QT += widgets

RESOURCES += customitems.qrc

OTHER_FILES += doc/src/* \
               doc/images/*
