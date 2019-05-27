#ifndef CAP_H
#define CAP_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include <QDebug>

#include "../globals.h"
#include "../tools/bezier.h"
#include "../tools/structs.h"
#include "../tools/meshvertex.h"
#include "../tools/voronoi.h"

#include "../libs/perlinnoise.h"

class Cap
{
public:
    Cap(Bezier& bezier);
    QVector<MeshVertex>* getVertices();
private:
    QVector<MeshVertex> vertices;
    QVector3D color;
    Bezier& bezier;

    void generateBaseEllipsoid();
    void applyBezierCurve();
    void widenCapRealisticaly();
    void applyPerlin(int octaves, double factor);
    void applyVoronoiTesselation();
};

#endif // CAP_H
