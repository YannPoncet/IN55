#ifndef MOREL_H
#define MOREL_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include <QDebug>

#include "../globals.h"
#include "cap.h"
#include "stem.h"
#include "../tools/bezier.h"
#include "../tools/meshvertex.h"
#include "../tools/structs.h"


class Morel
{
public:
    Morel();
    VerticesStruct getConvertedVertices();
    IndicesStruct getConvertedIndices();
    void updateIndices();
    void rescaleWithGlobalFactor();

    VerticesStructWithoutNormal getBezierVertices();
    IndicesStruct getBezierIndices();

private:
    QVector<MeshVertex> vertices;
    QVector<GLushort> indices;

    Bezier bezier = Bezier(parameters.height, parameters.stemHeightPart, parameters.curvatureVariance, parameters.anglePosVariance);
    Cap cap;
    Stem stem;
};

#endif // MOREL_H
