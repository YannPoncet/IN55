#include "cap.h"

Cap::Cap() {
    this->color = QVector3D(0.87f, 0.60f, 0.38f);
    this->generateBaseEllipsoid(1, 0.2, 0.3);
}

QVector<MeshVertex>* Cap::getVertices() {
    return &(this->vertices);
}

void Cap::generateBaseEllipsoid(double height, double radius, double radiusDeformation) {
    /*
        struct MeshVertex
        {
            GLushort id;
            QVector3D position;
            QVector3D color;
            struct MeshVertex* top;
            struct MeshVertex* bottom;
            struct MeshVertex* right;
            struct MeshVertex* left;
        };
    */

    // number of horizontal divisions
    GLushort n = 30;
    // number of vertical divisions
    GLushort k = 30;
    // height of a division
    double p = height/k;
    double angle = 0;
    float x = 0, y = 0, z = 0;
    // Creation of the vertices
    for (GLushort i=0; i<k; i++) {
        // function ax^2+bx+c going from f(x=0)=radius to f(x=k)=0, with f(x=k/2)=radiusDeformation
        double a = (1/pow(k,2))*(2*radius-4*radiusDeformation);
        double b = (1/double(k))*(4*radiusDeformation-3*radius);
        double newRadius = a*pow(i,2) + b*i + radius;
        for (GLushort j=0; j<n; j++) {
            angle = (2*M_PI/n)*j;
            x = static_cast<float>(newRadius*qCos(angle));
            y = static_cast<float>(newRadius*qSin(angle));
            z = static_cast<float>(p*i);

            MeshVertex v;
            v.id = i*n+j;
            v.position = QVector3D(x, y, z);
            v.color = QVector3D(0.6f, 0.2f, z/height);
            this->vertices.append(v);
        }
    }

    MeshVertex v;
    v.id = n*k;
    v.position = QVector3D(0.0f, 0.0f, height);
    v.color = QVector3D(0.6f, 0.2f, 1.0f);
    this->vertices.append(v);

    // Linking the different vertices
    for(auto&& v: this->vertices) {
        int i = v.id/n;

        v.top = nullptr;
        v.bottom = nullptr;
        v.right = nullptr;
        v.left = nullptr;

        if(i!=k) {
            if(i!=0) {
                v.bottom = &this->vertices[v.id-n];
            }

            if(i>=k-1) {
                v.top = &this->vertices[k*n];
            } else {
                v.top = &this->vertices[v.id+n];
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
        }
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
