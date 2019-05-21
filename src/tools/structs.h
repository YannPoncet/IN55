#ifndef STRUCT_H
#define STRUCT_H

#include <QVector3D>
#include <QOpenGLFunctions>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

struct VerticesStruct
{
    VertexData* vertices;
    int nbrVertices;
};


struct IndicesStruct
{
    GLushort* indices;
    int nbrIndices;
};


struct Parameters
{
    //Global Size
    double globalSizeFactor; //Will multiply the whole morel by that factor
    double globalSizeVariance;

    //Height parameters
    double height; //Height of the morel if it is 100% vertical
    double stemHeightPart; //Part of the stem in the morel's height, in percentage (0 to 100)
    double heightVariance;

    //Radius parameters
    double junctionRadius; //Radius at the junction between the cap and the stem
    double junctionRadiusVariance;
    double capMiddleRadius;
    double capMiddleRadiusVariance;


    //Meshing parameters
    GLushort stemNumberOfHorizontalDivisions;
    GLushort stemNumberOfVerticalDivisions;
    GLushort capNumberOfHorizontalDivisions;
    GLushort capNumberOfVerticalDivisions;
};

#endif // STRUCT_H
