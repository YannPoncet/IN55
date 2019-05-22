#ifndef MOREL_H
#define MOREL_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include <QDebug>

#include "cap.h"
#include "stem.h"
#include "../tools/bezier.h"
#include "../tools/meshvertex.h"
#include "../tools/normaldistribution.h"
#include "../tools/structs.h"

class Morel
{
public:
    Morel();
    VerticesStruct getConvertedVertices();
    IndicesStruct getConvertedIndices();
    void updateIndices();
    void rescaleWithGlobalFactor();

private:
    QVector<MeshVertex> vertices;
    QVector<GLushort> indices;

    Parameters params = {
        0.65,      // double globalSizeFactor
        0.05,      // double globalSizeVariance

        2,      // double height
        0.5,     // double stemHeightPart
        0,      // double heightVariance

        0.2,    // double junctionRadius
        0.0,    // double junctionRadiusVariance
        0.3,    // double capMiddleRadius
        0.0,    // double capMiddleRadiusVariance
        2,      // double radiusAtBaseFactor;
        0,      // double radiusAtBaseVariance;

        50,     // GLushort stemNumberOfHorizontalDivisions
        50,     // GLushort stemNumberOfVerticalDivisions
        200,    // GLushort capNumberOfHorizontalDivisions
        200,    // GLushort capNumberOfVerticalDivisions

        500,    // double curvatureVariance
        50     // double anglePosVariance;
    };

    Bezier bezier = Bezier(params.height, params.stemHeightPart, params.curvatureVariance, params.anglePosVariance, params.stemNumberOfHorizontalDivisions);
    Cap cap;
    Stem stem;
    NormalDistribution normalDistribution;
};

#endif // MOREL_H
