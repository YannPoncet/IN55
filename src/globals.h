#ifndef GLOBALS_H
#define GLOBALS_H

#include "tools/randomgenerator.h"
#include "structures/structs.h"

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;

extern RandomGenerator randomGenerator;
extern Parameters parameters;

extern bool showBezier;
extern bool showSystem;
extern bool showSoil;
extern bool showLights;

extern QVector<bool> lightsEnabled;

#endif // GLOBALS_H
