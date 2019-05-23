#include "cap.h"

Cap::Cap(Parameters& p, Bezier& b) : params(p), bezier(b) {
    this->color = QVector3D(0.87f, 0.60f, 0.38f);
    this->generateBaseEllipsoid();
    //this->applyTransformations();
    this->widenCapRealisticaly();
    this->applyBezierCurve();
    PerlinNoise perlinNoise;
    GLushort n = this->params.capNumberOfVerticalDivisions;
    // this factor has to be high so we don't see the difference when applying the perlin noise
    int perlinFactor = 5;
    for(auto&& v: this->vertices) {
        int i = v.id/n;

        if(i!=0) {
            double noise = perlinNoise.noise(v.position.x(), v.position.y(), v.position.z());
            v.position.setX(v.position.x() + v.position.x()*noise/perlinFactor);
            v.position.setY(v.position.y() + v.position.y()*noise/perlinFactor);
            v.position.setZ(v.position.z() + v.position.z()*noise/perlinFactor);
        }
    }
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
            QVector3D scaleVector = QVector3D(2.3f, 2.3f, 1.0f);
            v.rescale(scaleVector);
        }
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
    float baseHeight = this->params.height*this->params.stemHeightPart;

    for(auto&& v: this->vertices) {
        float t = this->params.stemHeightPart+(v.position.z()/this->params.height);
        this->bezier.applyFullBezierTransformationToVertex(v, t, baseHeight);
    }
}

void Cap::widenCapRealisticaly() {
    GLushort n = this->params.capNumberOfVerticalDivisions;
    float h = this->params.height*(1-this->params.stemHeightPart);

    float c = 1.5; //maxRadiusFactor
    float pow = 3; //should be an odd number

    float d = 0.20; //baseMaxHeightFactor: if d=1/3, the morel will be at it's max at 1/3
    float e = 0.80; //tipMaxHeightFactor: same but for the tip

    float b1 = h*d;
    float b2 = h*e;
    float a1 = c/(qPow(b1,pow));
    float a2 = -c/(qPow(h-b2,pow));

    for(auto&& v: this->vertices) {
        int i = v.id/n;

        if(i!=0) {
            float x = v.position.z();
            float factor = 0;
            if(x<d*h) {
                factor = a1*qPow((x-b1),pow)+c;
            } else if(x>e*h) {
                factor = -a2*qPow((x-b2),pow)+c;
            } else {
                factor = c;
            }
            v.position = QVector3D(factor*v.position.x()+v.position.x(), factor*v.position.y()+v.position.y(), v.position.z());
        }
    }

}
