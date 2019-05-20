#ifndef CAP_H
#define CAP_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include "../tools/structs.h"

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
