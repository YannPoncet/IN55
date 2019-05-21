#ifndef MOREL_H
#define MOREL_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include <QDebug>

#include "cap.h"
#include "stem.h"
#include "../tools/structs.h"
#include "../tools/meshvertex.h"

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

    Parameters params = {
        1,      // double globalSizeFactor
        0,      // double globalSizeVariance

        2,      // double height
        50,     // double stemHeightPart
        0,      // double heightVariance

        0.2,    // double junctionRadius
        0.0,    // double junctionRadiusVariance
        0.3,    // double capMiddleRadius
        0.0,    // double capMiddleRadiusVariance

        50,     // GLushort stemNumberOfHorizontalDivisions
        50,     // GLushort stemNumberOfVerticalDivisions
        200,    // GLushort capNumberOfHorizontalDivisions
        200     // GLushort capNumberOfVerticalDivisions
    };

    Cap cap;
    Stem stem;
};

#endif // MOREL_H
