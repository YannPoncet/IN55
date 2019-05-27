#include "globals.h"

const int WINDOW_HEIGHT = 1280;
const int WINDOW_WIDTH = 720;

RandomGenerator randomGenerator;

Parameters parameters = {
    //Size
    1,      // double globalSizeFactor
    0.005,      // double globalSizeVariance


    //Height
    3,      // double height
    0.38,     // double stemHeightPart


    //Radius
    0.18,    // double junctionRadius

    0.30,    // double capMaxRadiusFactor
    0.04,    // double capMaxRadiusVariance

    1.2,    // double capMaxRadiusFactor2;
    0.20f,  // float capBaseMaxRadiusLocationFactor: if d=1/3, the morel will be at it's max at 1/3
    0.99f,  // float capTipMaxRadiusLocationFactor: same but for the tip

    1.5,      // double radiusAtBaseFactor;
    0.1,      // double radiusAtBaseVariance;

    //Mesh
    20,     // GLushort stemNumberOfHorizontalDivisions
    20,     // GLushort stemNumberOfVerticalDivisions
    200,    // GLushort capNumberOfHorizontalDivisions
    200,    // GLushort capNumberOfVerticalDivisions

    0.008,    // double curvatureVariance
    0.05,     // double anglePosVariance;


    //Colors
    QVector3D(205.0f/255.0f, 122.0f/255.0f, 54.0f/255.0f), //QVector3D capColor;
    QVector3D(238.0f/255.0f, 200.0f/255.0f, 164.0f/255.0f), //QVector3D stemColor;
    QVector3D(225.0f/255.0f, 188.0f/255.0f, 144.0f/255.0f), //QVector3D holesEdgesColor;


    //Perlin
    0.12,    // double capGlobalPerlinPower;
    0.08,    // double capDetailsPerlinPower;


    //Voronoi
    1.0,        // double holesDensityFactor
    1.0         // double holesEdgesWidthFactor
};
