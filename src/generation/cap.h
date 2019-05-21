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
    Cap(Parameters& p);
    QVector<MeshVertex>* getVertices();
private:
    QVector<MeshVertex> vertices;
    QVector3D color;
    Parameters& params;

    void generateBaseEllipsoid();
    void applyTransformations();
};

#endif // CAP_H
