#include "stem.h"

Stem::Stem() {
    this->color = QVector3D(0.87f, 0.60f, 0.38f);
    this->generateBaseCylinder(3, 0.3);
}

QVector<VertexData> Stem::getVertices() {
    return this->vertices;
}


QVector<GLushort> Stem::getIndices() {
    return this->indices;
}


/*
* This function is used to generate the base cylinder.
* @param height height of the cylinder
* @param radius radius of the cylinder
*/
void Stem::generateBaseCylinder(double height, double radius) {
    this->vertices.append({QVector3D(0.0f, 0.0f, 0.0f), this->color});

    int n = 10;
    int k = 10;
    double p = height/k;
    double angle = 0;
    float x = 0, y = 0, z = 0;

    // Creation of the vertices
    for (int i=0; i<k; i++) {
        for (int j=0; j<n; j++) {
            angle = (2*M_PI/n)*j;
            x = static_cast<float>(radius*qCos(angle));
            y = static_cast<float>(radius*qSin(angle));
            z = static_cast<float>(-p*i);
            this->vertices.append({QVector3D(x, y, z), this->color});
        }
    }

    ushort a = 0, b = 0, c = 0, d = 0;
    // Creation of the indices array
    for (int i=0; i<k-1; i++) {
        for (int j=0; j<n; j++) {
            a = static_cast<ushort>(i*n+j+1);
            b = static_cast<ushort>(i*n+j+1+n);
            c = static_cast<ushort>(i*n+j+2+n);
            d = static_cast<ushort>(i*n+j+2);
            this->indices.append({a,b,c});
            this->indices.append({a,c,d});
        }
    }
}
