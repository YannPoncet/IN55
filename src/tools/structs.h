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


struct parameters
{
    //Global Size
    float globalSizeFactor; //Will multiply the whole morel by that factor
    float globalSizeVariance;

    //Height parameters
    float height; //Height of the morel if it is 100% vertical
    float stemHeightPart; //Part of the stem in the morel's height, in percentage (0 to 100)
    float heightVariance;

    //Radius parameters
    float junctionRadius; //Radius at the junction between the cap and the stem
    float junctionRadiusVariance;
    float capMiddleRadius;
    float capMiddleRadiusVariance;


    //Meshing parameters
    int stemNumberOfHorizontalDivisions;
    int stemNumberOfVerticalDivisions;
    int capNumberOfHorizontalDivisions;
    int capNumberOfVerticalDivisions;
};

#endif // STRUCT_H
