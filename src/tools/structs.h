#ifndef STRUCT_H
#define STRUCT_H

#include <QVector3D>
#include <QVector2D>
#include <QOpenGLFunctions>
#include <string>
#include <QSlider>

struct VertexData
{
    QVector3D position;
    QVector3D color;
    QVector3D normal;
};

struct VertexDataTexture
{
    QVector3D position;
    QVector3D color;
    QVector2D texture;
    float hasTexture;
};

struct VerticesStruct
{
    VertexData* vertices;
    long nbrVertices;
};


struct IndicesStruct
{
    GLushort* indices;
    long nbrIndices;
};

struct SliderParameters
{
    double min;
    double max;
    double baseValue;
    std::string text;
    QSlider* slider;
};


struct Parameters
{
    //Global Size
    double globalSizeFactor; //Will multiply the whole morel by that factor
    double globalSizeVariance;


    //Height parameters
    double height; //Height of the morel if it is 100% vertical
    double stemHeightPart; //Part of the stem in the morel's height, in percentage (0 to 100)


    //Radius parameters
    double junctionRadius; //Radius at the junction between the cap and the stem

    double capMaxRadiusFactor;
    double capMaxRadiusVariance;

    double capMaxRadiusFactor2;
    float capBaseMaxRadiusLocationFactor; //if d=1/3, the morel will be at it's max at 1/3 of its height
    float capTipMaxRadiusLocationFactor; //same but for the tip

    double radiusAtBaseFactor;
    double radiusAtBaseVariance;


    //Meshing parameters
    GLushort stemNumberOfHorizontalDivisions;
    GLushort stemNumberOfVerticalDivisions;
    GLushort capNumberOfHorizontalDivisions;
    GLushort capNumberOfVerticalDivisions;

    //Morel curvature parameters (Bezier)
    double curvatureVariance;
    double anglePosVariance;


    //Colors
    QVector3D capColor;
    QVector3D holesEdgesColor;
    QVector3D stemColor;


    //Perlin parameters
    double capGlobalPerlinPower;
    double capDetailsPerlinPower;


    //Voronoi tesselation factor
    double holesDensityFactor;
    double holesEdgesWidthFactor;
};

#endif // STRUCT_H
