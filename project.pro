QT       += core gui widgets

LIBS += -lopengl32

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/generation/stem.cpp \
    src/generation/cap.cpp \
    src/generation/morel.cpp \
    src/tools/meshvertex.cpp \
    src/tools/normaldistribution.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/generation/stem.h \
    src/generation/cap.h \
    src/generation/morel.h \
    src/tools/normaldistribution.h \
    src/tools/structs.h \
    src/tools/meshvertex.h

RESOURCES += \
    ressources/shaders.qrc \
