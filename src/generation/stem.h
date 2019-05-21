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
    Stem(Parameters& p);
    QVector<MeshVertex>* getVertices();
private:
    QVector<MeshVertex> vertices;
    QVector3D color;
    Parameters& params;

    void generateBaseCylinder();
};

#endif // STEM_H
