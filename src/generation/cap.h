#ifndef CAP_H
#define CAP_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include<QDebug>

#include "../tools/structs.h"
#include "../tools/meshvertex.h"

class Cap
{
public:
    Cap();
    QVector<MeshVertex> getVertices();
private:
    QVector<MeshVertex> vertices;
    QVector3D color;

    void generateBaseEllipsoid(double height, double radius, double maxRadius);
};

#endif // CAP_H
