QT       += core gui widgets

LIBS += -lopengl32

QMAKE_CFLAGS_YACC   = -Wno-sign-conversion

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/generation/stem.cpp \
    src/generation/cap.cpp \
    src/generation/morel.cpp \
    src/structures/meshvertex.cpp \
    src/tools/bezier.cpp \
    src/tools/voronoi.cpp \
    src/globals.cpp \
    src/generation/morelpart.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/generation/stem.h \
    src/generation/cap.h \
    src/generation/morel.h \
    src/structures/structs.h \
    src/structures/meshvertex.h \
    src/tools/bezier.h \
    src/libs/perlinnoise.h \
    src/tools/voronoi.h \
    src/tools/randomgenerator.h \
    src/globals.h \
    src/generation/morelpart.h

RESOURCES += \
    ressources/shaders.qrc \
    ressources/textures.qrc \
