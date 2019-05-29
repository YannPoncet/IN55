#ifndef STEM_H
#define STEM_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>

#include<QDebug>

#include "../globals.h"
#include "../tools/bezier.h"
#include "../tools/structs.h"
#include "../tools/meshvertex.h"

#include "../libs/perlinnoise.h"

class Stem
{
public:
    Stem(Bezier& bezier);
    QVector<MeshVertex>* getVertices();
private:
    QVector<MeshVertex> vertices;
    Bezier& bezier;

    void generateBaseCylinder();
    void applyBezierCurve();
    void widenStemBase();
    void applyPerlin(int octaves, double factor);
    void applyColorVariationWithPerlin(int octaves, double factor);
};

#endif // STEM_H
