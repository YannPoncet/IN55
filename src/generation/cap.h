#ifndef CAP_H
#define CAP_H

#include "morelpart.h"
#include "../tools/voronoi.h"


class Cap : public MorelPart
{
public:
    Cap(Bezier& bezier);
private:
    void generateBaseEllipsoid();
    void applyBezierCurve();
    void widenCapRealisticaly();
    void applyVoronoiTesselation();
};

#endif // CAP_H
