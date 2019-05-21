#include "stem.h"

Stem::Stem(Parameters& p, Bezier& b) : params(p), bezier(b) {
    this->color = QVector3D(0.87f, 0.60f, 0.38f);
    this->generateBaseCylinder();
}

QVector<MeshVertex>* Stem::getVertices() {
    return &(this->vertices);
}

/*
* This function is used to generate the base cylinder.
* @param height height of the cylinder
* @param radius radius of the cylinder
*/
void Stem::generateBaseCylinder() {
    GLushort n = this->params.stemNumberOfVerticalDivisions;
    GLushort k = this->params.stemNumberOfHorizontalDivisions;
    double height = this->params.height*(this->params.stemHeightPart/100);
    double radius = this->params.junctionRadius;
    double globalSizeFactor = this->params.globalSizeFactor;

    double p = height/k;
    double angle = 0;
    float x = 0, y = 0, z = 0;
    // Creation of the vertices
    for (GLushort i=0; i<k; i++) {
        for (GLushort j=0; j<n; j++) {
            angle = (2*M_PI/n)*j;
            x = static_cast<float>(radius*qCos(angle));
            y = static_cast<float>(radius*qSin(angle));
            z = static_cast<float>(-p*i);

            MeshVertex v;
            v.id = i*n+j;
            v.position = QVector3D(x, y, z);
            v.color = QVector3D(0.2f, 0.6f, -z);
            v.rescale(static_cast<float>(globalSizeFactor));
            this->vertices.append(v);
        }
    }

    // Linking the different vertices
    for(auto&& v: this->vertices) {
        int i = v.id/n;

        if(i==0) {
            v.top = nullptr;
        } else {
            v.top = &this->vertices[v.id-n];
        }

        if(i>=k-1) {
            v.bottom = nullptr;
        } else {
            v.bottom = &this->vertices[v.id+n];
        }

        if(i!=(v.id+1)/n) {
            v.right = &this->vertices[v.id-n+1];
        } else {
            v.right = &this->vertices[v.id+1];
        }


        if(v.id==0 || i!=(v.id-1)/n) {
            v.left = &this->vertices[v.id+n-1];
        } else {
            v.left = &this->vertices[v.id-1];
        }

        //TODO to remove
        QQuaternion rotationQuat = this->bezier.getRotationQuaternion(v.position.z(), this->params.height);
        v.rotate(rotationQuat);
    }

    /*
    //used to print the mesh
    for(auto&& v: this->vertices) {
        qDebug() << "-- id=" << v.id;
        if(v.top != nullptr)
            qDebug() << "top=" << v.top->id;

        if(v.bottom != nullptr)
            qDebug() << "bottom=" << v.bottom->id;

        if(v.right != nullptr)
            qDebug() << "right=" << v.right->id;

        if(v.left != nullptr)
            qDebug() << "left=" << v.left->id;
    }
    */
}
