#ifndef MOREL_H
#define MOREL_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include <QDebug>

#include "../tools/structs.h"
#include "cap.h"
#include "stem.h"

class Morel
{
public:
    Morel();
    VerticesStruct getConvertedVertices();
    IndicesStruct getConvertedIndices();
    void updateIndices();

private:
    QVector<MeshVertex> vertices;
    QVector<GLushort> indices;

    Cap cap;
    Stem stem;
};

#endif // MOREL_H
