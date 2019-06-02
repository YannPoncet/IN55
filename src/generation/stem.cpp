#include "stem.h"

Stem::Stem(Bezier& b) : MorelPart(b) {
    this->height = parameters.height*parameters.stemHeightPart;
    this->isStem = true;

    this->generateBaseCylinder();
    this->widenStemBase();
    MorelPart::applyPerlin(1, 1);
    MorelPart::applyColorVariationWithPerlin(10, 0.15);
    this->applyBezierCurve();
}


/*
* This function is used to generate the base cylinder, it also links the different
* vertices to their neighbours.
*/
void Stem::generateBaseCylinder() {
    GLushort n = parameters.stemNumberOfVerticalDivisions;
    GLushort k = parameters.stemNumberOfHorizontalDivisions;
    double height = this->height;
    double radius = parameters.junctionRadius;

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
            v.setPosition(x, y, z);v.color = parameters.colorSets[parameters.choosenSet].stemColor;
            v.layer = i;
            v.baseAngle = angle;
            v.baseHeight = z;
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


/*
* This function applies the Bezier curve to the points depending on their height.
*/
void Stem::applyBezierCurve() {
    float baseHeight = this->height;

    for(auto&& v: this->vertices) {
        float t = ((parameters.stemHeightPart*parameters.height)+v.z())/parameters.height;
        this->bezier.applyFullBezierTransformationToVertex(v, t, baseHeight);
    }
}


/*
* This function is used to make the base of the stem wider, following an inverse function with the height.
*/
void Stem::widenStemBase() {
    float h = this->height;
    float b = randomGenerator.getNormalNumber<float>(parameters.radiusAtBaseFactor, parameters.radiusAtBaseVariance);
    float factor = 1;

    for(auto&& v: this->vertices) {
        float x = (h+v.z());
        factor = b - (b/(pow(h,1.0/3.0)))*pow(x,1.0/3.0);
        v.setPosition(factor*v.x()+v.x(), factor*v.y()+v.y(), v.z());
    }
}

