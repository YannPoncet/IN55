#include "cap.h"

Cap::Cap(Parameters& p, Bezier& b) : params(p), bezier(b) {
    this->color = QVector3D(0.87f, 0.60f, 0.38f);
    this->generateBaseEllipsoid();
    this->applyBezierCurve();
    //this->applyTransformations();
}

QVector<MeshVertex>* Cap::getVertices() {
    return &(this->vertices);
}

void Cap::applyTransformations() {
    GLushort n = this->params.capNumberOfVerticalDivisions;
    GLushort k = this->params.capNumberOfHorizontalDivisions;

    // applying some transformations to the cap (to every vertex but the ones forming the base)
    for(auto&& v: this->vertices) {
        int i = v.id/n;

        if(i!=0) {
            QVector3D scaleVector = QVector3D(2.3f, 2.3f, 2.3f);
            v.rescale(scaleVector);
        }

        /*
        if(i!=0 && i<k/5) {
            QVector3D translation = QVector3D(0, 0, -0.1f);
            QVector3D scaleVector = QVector3D(2.3f, 2.3f, 2.3f);
            v.translate(translation);
            v.rescale(scaleVector);
        } else if(i!=0) {
            QVector3D translation = QVector3D(0, 0.1f, 0);
            QVector3D scaleVector = QVector3D(2.1f, 2.1f, 2.1f);
            QVector3D rotationAxis = QVector3D(1, 0, 0);
            QVector3D rotationPoint = QVector3D(0, 0, 0);
            v.translate(translation);
            v.rescale(scaleVector);
            v.rotate(M_PI/10,rotationAxis,rotationPoint);
        }
        */
    }
}

void Cap::generateBaseEllipsoid() {
    GLushort n = this->params.capNumberOfVerticalDivisions;
    GLushort k = this->params.capNumberOfHorizontalDivisions;
    double height = this->params.height*(1-this->params.stemHeightPart);
    double radius = this->params.junctionRadius;
    double capMiddleRadius = this->params.capMiddleRadius;

    // height of a division
    double p = height/k;
    double angle = 0;
    float x = 0, y = 0, z = 0;
    // Creation of the vertices
    for (GLushort i=0; i<k; i++) {
        // function ax^2+bx+c going from f(x=0)=radius to f(x=k)=0, with f(x=k/2)=capMiddleRadius
        double a = (1/pow(k,2))*(2*radius-4*capMiddleRadius);
        double b = (1/double(k))*(4*capMiddleRadius-3*radius);
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
}

void Cap::applyBezierCurve() {
    float zeroAngle = this->bezier.getZeroAngle();
    QVector3D rotationPoint(0, 0, -this->params.height*this->params.stemHeightPart);

    for(auto&& v: this->vertices) {
        float t = this->params.stemHeightPart+(v.position.z()/this->params.height);
        QQuaternion rotationQuat = this->bezier.getRotationQuaternion(t);

        QVector3D axis;
        float useless;
        rotationQuat.getAxisAndAngle(&axis, &useless);
        QQuaternion rotateBack = QQuaternion::fromAxisAndAngle(axis, -zeroAngle*180/M_PI);

        v.rotate(rotationQuat);
        v.translate(-rotationPoint);
        v.rotate(rotateBack);
        v.translate(rotationPoint);
    }

}
