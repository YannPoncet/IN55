#ifndef CAP_H
#define CAP_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include <QDebug>

#include "../globals.h"
#include "../structures/structs.h"
#include "../structures/meshvertex.h"
#include "../tools/bezier.h"
#include "../tools/voronoi.h"

#include "../libs/perlinnoise.h"

class Cap
{
public:
    Cap(Bezier& bezier);
    QVector<MeshVertex>* getVertices();
private:
    QVector<MeshVertex> vertices;
    Bezier& bezier;

    void generateBaseEllipsoid();
    void applyBezierCurve();
    void widenCapRealisticaly();
    void applyPerlin(int octaves, double factor);
    void applyColorVariationWithPerlin(int octaves, double factor);
    void applyVoronoiTesselation();
};

#endif // CAP_H
