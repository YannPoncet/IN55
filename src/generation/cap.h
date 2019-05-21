#ifndef CAP_H
#define CAP_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include<QDebug>

#include "../tools/bezier.h"
#include "../tools/structs.h"
#include "../tools/meshvertex.h"

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
    void applyTransformations();
};

#endif // CAP_H
