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
        0.75,      // double globalSizeFactor
        0.005,      // double globalSizeVariance

        2.5,      // double height
        0.35,     // double stemHeightPart
        0,      // double heightVariance

        0.2,    // double junctionRadius
        0.0,    // double junctionRadiusVariance
        0.4,    // double capMaxRadius
        0.0,    // double capMaxRadiusVariance
        2,      // double radiusAtBaseFactor;
        0,      // double radiusAtBaseVariance;

        20,     // GLushort stemNumberOfHorizontalDivisions
        20,     // GLushort stemNumberOfVerticalDivisions
        30,    // GLushort capNumberOfHorizontalDivisions
        30,    // GLushort capNumberOfVerticalDivisions

        0.5,    // double curvatureVariance
        0.5     // double anglePosVariance;
    };

    Bezier bezier = Bezier(params.height, params.stemHeightPart, params.curvatureVariance, params.anglePosVariance);
    Cap cap;
    Stem stem;
    NormalDistribution normalDistribution;
};

#endif // MOREL_H
