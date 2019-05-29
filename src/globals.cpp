#include "globals.h"

const int WINDOW_HEIGHT = 1280;
const int WINDOW_WIDTH = 720;

bool showBezier = false;
bool showSystem = false;
bool showSoil = true;

bool lightsEnabled[5] = {0,0,0,0,1}; //Only light on camera enabled by default

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
        {   QVector3D(205.0f/255.0f, 122.0f/255.0f, 54.0f/255.0f), //capColor
            QVector3D(241.0f/255.0f, 162.0f/255.0f, 97.0f/255.0f), //holesEdgesColor
            QVector3D(188.0f/255.0f, 158.0f/255.0f, 104.0f/255.0f) }, // stemColor

        //Brown morel
        {   QVector3D(97.0f/255.0f, 76.0f/255.0f, 57.0f/255.0f), //capColor
            QVector3D(110.0f/255.0f, 90.0f/255.0f, 72.0f/255.0f), //holesEdgesColor
            QVector3D(188.0f/255.0f, 158.0f/255.0f, 104.0f/255.0f) }, // stemColor

        //Black morel
        {   QVector3D(17.0f/255.0f, 17.0f/255.0f, 17.0f/255.0f), //capColor
            QVector3D(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f), //holesEdgesColor
            QVector3D(199.0f/255.0f, 185.0f/255.0f, 172.0f/255.0f) }, // stemColor

        //Gray morel
        {   QVector3D(67.0f/255.0f, 64.0f/255.0f, 71.0f/255.0f), //capColor
            QVector3D(120.0f/255.0f, 120.0f/255.0f, 130.0f/255.0f), //holesEdgesColor
            QVector3D(192.0f/255.0f, 201.0f/255.0f, 207.0f/255.0f) } // stemColor
    },
    0, // choosenSet -> is set in GeometryEngine::createAndBindMorels


    //Perlin
    0.12,    // double capGlobalPerlinPower;
    0.08,    // double capDetailsPerlinPower;


    //Voronoi
    1.0,        // double holesDensityFactor
    0.5         // double holesEdgesWidthFactor
};
