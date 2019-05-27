#include "globals.h"

const int WINDOW_HEIGHT = 1280;
const int WINDOW_WIDTH = 720;

RandomGenerator randomGenerator;

Parameters parameters = {
    1.3,      // double globalSizeFactor
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
    200,    // GLushort capNumberOfHorizontalDivisions
    200,    // GLushort capNumberOfVerticalDivisions

    0.008,    // double curvatureVariance
    0.05     // double anglePosVariance;
};
