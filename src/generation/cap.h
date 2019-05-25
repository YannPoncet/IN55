#ifndef CAP_H
#define CAP_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include <QDebug>

#include "../tools/bezier.h"
#include "../tools/structs.h"
#include "../tools/meshvertex.h"
#include "../tools/voronoi.h"

#include "../libs/perlinnoise.h"

class Cap
{
public:
    Cap(Parameters& p, Bezier& bezier);
    QVector<MeshVertex>* getVertices();
private:
    QVector<MeshVertex> vertices;
    QVector3D color;
    Parameters& params;
    Bezier& bezier;

    void generateBaseEllipsoid();
    void applyBezierCurve();
    void widenCapRealisticaly();
    void applyPerlin();
    void applyVoronoiTesselation();
};

#endif // CAP_H
