
QT       += core gui
#-start- add for vox
QT += opengl
#-end- add for vox

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OBJ-Reader_myk

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    qobj3dreader.cpp \
    qobj3dviewer.cpp \
    voxRead_makeGLdata.cpp

HEADERS  += mainwindow.h \
    qobj3dreader.h \
    qobj3dviewer.h \
    voxRead_makeGLdata.h

FORMS    += mainwindow.ui

#-start- add for vox
LIBS += -lOpengl32
#-end-  add for vox

VERSION = 1.0.0

#-start- add for vox
#DISTFILES += \
#    frag-shader.fsh \
#    vert-shader.vsh
#-end-  add for vox

RESOURCES += \
    resources.qrc
