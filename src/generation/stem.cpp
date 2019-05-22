#include "stem.h"

Stem::Stem(Parameters& p, Bezier& b) : params(p), bezier(b) {
    this->color = QVector3D(0.87f, 0.60f, 0.38f);
    this->generateBaseCylinder();
    this->widenStemBase();
    this->applyBezierCurve();
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
    double height = this->params.height*this->params.stemHeightPart;
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
    }
}

void Stem::applyBezierCurve() {
    for(auto&& v: this->vertices) {
        float t = ((this->params.stemHeightPart*this->params.height)+v.position.z())/this->params.height;
        QQuaternion rotationQuat = this->bezier.getRotationQuaternion(t);
        v.rotate(rotationQuat);
    }
}

void Stem::widenStemBase() {
    float h = this->params.stemHeightPart*this->params.height;
    float b = this->params.radiusAtBaseFactor;
    float factor = 1;

    for(auto&& v: this->vertices) {
        float tmpPos = (h+v.position.z());
        factor = b - b/(qPow(h,-1.0/3.0))*qPow(tmpPos,1.0/3.0);
        v.position = QVector3D(factor*v.position.x()+v.position.x(), factor*v.position.y()+v.position.y(), v.position.z());
    }
}

