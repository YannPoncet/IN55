#ifndef MORELPART_H
#define MORELPART_H

#include <QOpenGLFunctions>
#include <QVector>
#include <QtMath>
#include <QDebug>

#include "../globals.h"

#include "../structures/structs.h"
#include "../structures/meshvertex.h"

#include "../tools/bezier.h"

#include "../libs/perlinnoise.h"



class MorelPart
{
public:
    MorelPart(Bezier& bezier);
    QVector<MeshVertex>* getVertices();
protected:
    Bezier& bezier;
    QVector<MeshVertex> vertices;
    float height;
    bool isStem;

    void applyPerlin(int octaves, double factor);
    void applyColorVariationWithPerlin(int octaves, double factor);
};

#endif // MORELPART_H
