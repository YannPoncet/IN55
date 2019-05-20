#ifndef STEM_H
#define STEM_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include<QDebug>

#include "../tools/structs.h"
#include "../tools/meshvertex.h"

class Stem
{
public:
    Stem();
    QVector<MeshVertex>* getVertices();
private:
    QVector<MeshVertex> vertices;
    QVector3D color;

    void generateBaseCylinder(double height, double radius);
};

#endif // STEM_H
