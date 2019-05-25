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

    VerticesStruct getBezierVertices();
    IndicesStruct getBezierIndices();

private:
    QVector<MeshVertex> vertices;
    QVector<GLushort> indices;

    Parameters params = {
        1.0,      // double globalSizeFactor
        0.005,      // double globalSizeVariance

        2.3,      // double height
        0.38,     // double stemHeightPart
        0,      // double heightVariance

        0.18,    // double junctionRadius
        0.0,    // double junctionRadiusVariance
        0.30,    // double capMaxRadius
        0.0,    // double capMaxRadiusVariance
        1.5,      // double radiusAtBaseFactor;
        0,      // double radiusAtBaseVariance;

        20,     // GLushort stemNumberOfHorizontalDivisions
        20,     // GLushort stemNumberOfVerticalDivisions
        100,    // GLushort capNumberOfHorizontalDivisions
        100,    // GLushort capNumberOfVerticalDivisions

        0.008,    // double curvatureVariance
        0.05     // double anglePosVariance;
    };

    Bezier bezier = Bezier(params.height, params.stemHeightPart, params.curvatureVariance, params.anglePosVariance);
    Cap cap;
    Stem stem;
    NormalDistribution normalDistribution;
};

#endif // MOREL_H
