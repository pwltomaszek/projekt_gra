# -------------------------------------------------
# Project created by QtCreator 2010-10-26T23:45:23
# -------------------------------------------------
QT += opengl \
    xml

win32 {
    LIBS += -ldevil
}

!win32 {
    LIBS += -lIL
}

TARGET = projekt_gra
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    glwidget.cpp \
    gra.cpp \
    opengl/utils.cpp \
    opengl/triangles.cpp \
    opengl/transformation.cpp \
    opengl/texture.cpp \
    opengl/skeletoncontroller.cpp \
    opengl/opengl.cpp \
    opengl/interpolation.cpp \
    opengl/glmadapter.cpp \
    opengl/colladameshfactory.cpp \
    opengl/node.cpp \
    opengl/mesh.cpp \
    opengl/material.cpp \
    opengl/joint.cpp \
    opengl/animationsampler.cpp \
    opengl/animationcontroller.cpp \
    opengl/animation.cpp \
    pojazd.cpp \
    obiektnamapie.cpp \
    przeszkoda.cpp \
    mapa.cpp \
    droga.cpp \
    chodnik.cpp \
    budynek.cpp
HEADERS += mainwindow.h \
    glwidget.h \
    gra.h \
    opengl/utils.h \
    opengl/triangles.h \
    opengl/transformation.h \
    opengl/texture.h \
    opengl/skeletoncontroller.h \
    opengl/pairvector.h \
    opengl/opengl.h \
    opengl/colladameshfactory.h \
    opengl/animationsampler.h \
    opengl/node.h \
    opengl/mesh.h \
    opengl/material.h \
    opengl/joint.h \
    opengl/interpolation.h \
    opengl/animationcontroller.h \
    opengl/glmadapter.h \
    opengl/common.h \
    opengl/animation.h \
    pojazd.h \
    obiektnamapie.h \
    przeszkoda.h \
    mapa.h \
    droga.h \
    chodnik.h \
    budynek.h
FORMS += mainwindow.ui
OTHER_FILES += texture.vert \
    texture.frag
QMAKE_CXXFLAGS += --std=gnu++0x