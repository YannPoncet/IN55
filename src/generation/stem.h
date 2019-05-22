#ifndef STEM_H
#define STEM_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include<QDebug>

#include "../tools/bezier.h"
#include "../tools/structs.h"
#include "../tools/meshvertex.h"

class Stem
{
public:
    Stem(Parameters& p, Bezier& bezier);
    QVector<MeshVertex>* getVertices();
private:
    QVector<MeshVertex> vertices;
    QVector3D color;
    Parameters& params;
    Bezier& bezier;

    void generateBaseCylinder();
    void applyBezierCurve();
    void widenStemBase();
};

#endif // STEM_H
