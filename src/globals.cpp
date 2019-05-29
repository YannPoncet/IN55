#include "globals.h"

const int WINDOW_HEIGHT = 1280;
const int WINDOW_WIDTH = 720;

bool showBezier = false;
bool showSystem = false;
bool showSoil = true;

QVector<bool> lightsEnabled = {0,0,0,0,1}; //Only light on camera enabled by default

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
    {   //Blond morel
        {   QVector3D(131.0f/255.0f, 109.0f/255.0f, 52.0f/255.0f), //capColor
            QVector3D(216.0f/255.0f, 191.0f/255.0f, 134.0f/255.0f), //holesEdgesColor
            QVector3D(188.0f/255.0f, 158.0f/255.0f, 104.0f/255.0f) }, // stemColor

        //Brown morel
        {   QVector3D(80.0f/255.0f, 58.0f/255.0f, 44.0f/255.0f), //capColor
            QVector3D(131.0f/255.0f, 91.0f/255.0f, 66.0f/255.0f), //holesEdgesColor
            QVector3D(200.0f/255.0f, 176.0f/255.0f, 116.0f/255.0f) }, // stemColor

        //Black morel
        {   QVector3D(48.0f/255.0f, 40.0f/255.0f, 29.0f/255.0f), //capColor
            QVector3D(145.0f/255.0f, 133.0f/255.0f, 109.0f/255.0f), //holesEdgesColor
            QVector3D(181.0f/255.0f, 164.0f/255.0f, 118.0f/255.0f) }, // stemColor

        //Gray morel
        {   QVector3D(159.0f/255.0f, 142.0f/255.0f, 117.0f/255.0f), //capColor
            QVector3D(183.0f/255.0f, 179.0f/255.0f, 176.0f/255.0f), //holesEdgesColor
            QVector3D(188.0f/255.0f, 158.0f/255.0f, 104.0f/255.0f) }, // stemColor
    },
    0, // choosenSet -> is set in GeometryEngine::createAndBindMorels


    //Perlin
    0.12,    // double capGlobalPerlinPower;
    0.08,    // double capDetailsPerlinPower;


    //Voronoi
    1.0,        // double holesDensityFactor
    0.5         // double holesEdgesWidthFactor
};
