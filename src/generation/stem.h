#ifndef STEM_H
#define STEM_H

#include "morelpart.h"

class Stem : public MorelPart
{
public:
    Stem(Bezier& bezier);
private:
    void generateBaseCylinder();
    void applyBezierCurve();
    void widenStemBase();
};

#endif // STEM_H
