#include "globals.h"

const int WINDOW_HEIGHT = 1280;
const int WINDOW_WIDTH = 720;

RandomGenerator randomGenerator;

Parameters parameters = {
    //Size
    1,      // double globalSizeFactor
    0.005,      // double globalSizeVariance


    //Height
    2.6,      // double height
    0.38,     // double stemHeightPart


    //Radius
    0.17,    // double junctionRadius

    0.3,    // double capMaxRadiusFactor
    0,    // double capMaxRadiusVariance

    1.13,    // double capMaxRadiusFactor2;
    0.60f,  // float capBaseMaxRadiusLocationFactor: if d=1/3, the morel will be at it's max at 1/3
    0.99f,  // float capTipMaxRadiusLocationFactor: same but for the tip

    1.5,      // double radiusAtBaseFactor;
    0.1,      // double radiusAtBaseVariance;

    //Mesh
    50,     // GLushort stemNumberOfHorizontalDivisions
    50,     // GLushort stemNumberOfVerticalDivisions
    250,    // GLushort capNumberOfHorizontalDivisions
    250,    // GLushort capNumberOfVerticalDivisions

    0.008,    // double curvatureVariance
    0.05,     // double anglePosVariance;


    //Colors
    //QVector3D(205.0f/255.0f, 122.0f/255.0f, 54.0f/255.0f), //QVector3D capColor;
    //QVector3D(225.0f/255.0f, 188.0f/255.0f, 144.0f/255.0f), //QVector3D holesEdgesColor;
    QVector3D(97.0f/255.0f, 76.0f/255.0f, 57.0f/255.0f), //QVector3D capColor;
    QVector3D(110.0f/255.0f, 90.0f/255.0f, 72.0f/255.0f), //QVector3D holesEdgesColor;
    QVector3D(188.0f/255.0f, 158.0f/255.0f, 104.0f/255.0f), //QVector3D stemColor;


    //Perlin
    0.12,    // double capGlobalPerlinPower;
    0.08,    // double capDetailsPerlinPower;


    //Voronoi
    1.0,        // double holesDensityFactor
    0.5         // double holesEdgesWidthFactor
};
