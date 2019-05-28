#include "stem.h"

Stem::Stem(Bezier& b) : bezier(b) {
    this->color = QVector3D(0.87f, 0.60f, 0.38f);
    this->generateBaseCylinder();
    this->widenStemBase();
    this->applyPerlin(1,1);
    this->applyColorVariationWithPerlin(10,0.15);
    this->applyBezierCurve();
}

QVector<MeshVertex>* Stem::getVertices() {
    return &(this->vertices);
}


void Stem::applyPerlin(int octaves, double factor) {
    const siv::PerlinNoise perlinNoise(randomGenerator.getGenerator().operator()());

    float h = parameters.height*parameters.stemHeightPart;
    for(auto&& v: this->vertices) {
        if(v.layer!=0) {
            // We create a sphere of radius 1 centered on O on which we'll apply perlin
            float sZ = 2.0*(v.baseHeight+(h/2.0))/h;
            double sR = sqrt(1.0-pow(sZ,2.0));
            float sX = sR*cos(v.baseAngle);
            float sY = sR*sin(v.baseAngle);

            // We convert the point's coordinate into spherical coordinates
            float r = 1.0f;
            float theta = atan2(sY, sX);
            float phi = acos(sZ);

            // We compute the noise and apply it to the radius
            double noise = perlinNoise.octaveNoise(theta, phi, octaves);
            r = r+r*noise*factor*(abs(v.z())/h);

            // We convert back to cartesian coordinates
            float x = r*cos(theta)*sin(phi);
            float y = r*sin(theta)*sin(phi);

            float factorX = x/sX;
            if (abs(sX) <= 0.01f) factorX = 1.0f;
            float factorY = y/sY;
            if (abs(sY) <= 0.01f) factorY = 1.0f;

            // We apply the factor on the actual position of the point
            v.setX(v.x()*factorX);
            v.setY(v.y()*factorY);
        }
    }
}


void Stem::applyColorVariationWithPerlin(int octaves, double factor) {
    const siv::PerlinNoise perlinNoise(randomGenerator.getGenerator().operator()());

    float h = parameters.height*parameters.stemHeightPart;
    for(auto&& v: this->vertices) {
        if(v.layer!=0) {
            // We create a sphere of radius 1 centered on O on which we'll apply perlin
            float sZ = 2.0*(v.baseHeight+(h/2.0))/h;
            double sR = sqrt(1.0-pow(sZ,2.0));
            float sX = sR*cos(v.baseAngle);
            float sY = sR*sin(v.baseAngle);

            // We convert the point's coordinate into spherical coordinates
            float r = 1.0f;
            float theta = atan2(sY, sX);
            float phi = acos(sZ);

            // We compute the noise and apply it to the radius
            double noise = perlinNoise.octaveNoise(theta, phi, octaves);
            r = r+r*noise*factor;

            v.color = QVector3D(v.color.x()*r, v.color.y()*r, v.color.z()*r);
            if(v.color.x()<0) v.color.setX(0);
            if(v.color.y()<0) v.color.setY(0);
            if(v.color.z()<0) v.color.setZ(0);
            if(v.color.x()>1) v.color.setX(1);
            if(v.color.y()>1) v.color.setY(1);
            if(v.color.z()>1) v.color.setZ(1);
        }
    }
}

/*
* This function is used to generate the base cylinder.
* @param height height of the cylinder
* @param radius radius of the cylinder
*/
void Stem::generateBaseCylinder() {
    GLushort n = parameters.stemNumberOfVerticalDivisions;
    GLushort k = parameters.stemNumberOfHorizontalDivisions;
    double height = parameters.height*parameters.stemHeightPart;
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
            v.setPosition(x, y, z);
            //v.color = QVector3D(0.2f, 0.6f, -z);
            v.color = parameters.stemColor;
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

void Stem::applyBezierCurve() {
    float baseHeight = parameters.height*parameters.stemHeightPart;

    for(auto&& v: this->vertices) {
        float t = ((parameters.stemHeightPart*parameters.height)+v.z())/parameters.height;
        this->bezier.applyFullBezierTransformationToVertex(v, t, baseHeight);
    }
}

void Stem::widenStemBase() {
    float h = parameters.stemHeightPart*parameters.height;
    float b = randomGenerator.getNormalNumber<float>(parameters.radiusAtBaseFactor, parameters.radiusAtBaseVariance);
    float factor = 1;

    for(auto&& v: this->vertices) {
        float x = (h+v.z());
        factor = b - (b/(pow(h,1.0/3.0)))*pow(x,1.0/3.0);
        v.setPosition(factor*v.x()+v.x(), factor*v.y()+v.y(), v.z());
    }
}

