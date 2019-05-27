#include "cap.h"

Cap::Cap(Parameters& p, Bezier& b) : params(p), bezier(b) {
    this->color = QVector3D(0.87f, 0.60f, 0.38f);
    this->generateBaseEllipsoid();
    this->widenCapRealisticaly();
    this->applyVoronoiTesselation();
    this->applyPerlin();
    this->applyBezierCurve();
}

void Cap::applyPerlin() {
    float perlinFactor = 0.18;

    std::uint32_t seed = 19894264;
    const siv::PerlinNoise perlinNoise(time(0));

    float h = this->params.height*(1.0f-this->params.stemHeightPart);
    for(auto&& v: this->vertices) {
        if(v.layer!=0) {
            // We create a sphere of radius 1 centered on O on which we'll apply perlin
            float sZ = 2.0*(v.baseHeight-(h/2.0))/h;
            double sR = sqrt(1.0-pow(sZ,2.0));
            float sX = sR*cos(v.baseAngle);
            float sY = sR*sin(v.baseAngle);

            // We convert the point's coordinate into spherical coordinates
            float r = 1.0f;
            float theta = atan2(sY, sX);
            float phi = acos(sZ);
            // Below is the real conversion (if radius wasn't 1)
            //float r = sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0));
            //float theta = qAtan(y/x);
            //float phi = qAcos(z/r);

            // We compute the noise and apply it to the radius
            double noise = perlinNoise.octaveNoise(theta, phi, 2);
            r = r+r*noise;

            // We convert back to cartesian coordinates
            float x = r*cos(theta)*sin(phi);
            float y = r*sin(theta)*sin(phi);
            float z = r*cos(phi);

            // We apply the noise on the actual position of the point
            v.setX(v.x()+v.x()*perlinFactor*x);
            v.setY(v.y()+v.y()*perlinFactor*y);
            v.setZ(v.z());
        }
    }
}


void Cap::applyVoronoiTesselation() {
    float voronoiFactor = 0.5;
    double fMax = 1.1;
    double fMin = 0.9;
    Voronoi voronoiGenerator(1800, 1800, 500, 15, fMax, fMin);

    float h = this->params.height*(1.0f-this->params.stemHeightPart);
    for(auto&& v: this->vertices) {
        if(v.layer!=0) {
            // We create a sphere of radius 1 centered on O on which we'll apply voronoi's tesselation
            float sZ = 2.0*(v.baseHeight-(h/2.0))/h;
            double sR = sqrt(1.0-pow(sZ,2.0));
            float sX = sR*cos(v.baseAngle);
            float sY = sR*sin(v.baseAngle);

            // We convert the point's coordinate into spherical coordinates
            float r = 1.0f;
            float theta = atan2(sY, sX);
            float phi = acos(sZ);

            // We compute the noise and apply it to the radius
            double factor = voronoiGenerator.getFactorAt((theta+M_PI)/(2*M_PI), (phi+M_PI)/(2*M_PI));
            if(abs(factor-fMax) <= 0.01f) {
                v.color = QVector3D(225.0/255.0, 188.0/255.0, 144.0/255.0);
            }
            r = r*factor;

            // We convert back to cartesian coordinates
            float x = r*cos(theta)*sin(phi);
            float y = r*sin(theta)*sin(phi);
            float z = r*cos(phi);

            float factorX = x/sX;
            if (abs(sX) <= 0.01f) factorX = 1.0f;
            float factorY = y/sY;
            if (abs(sY) <= 0.01f) factorY = 1.0f;
            float factorZ = z/sZ;
            if (abs(sZ) <= 0.01f) factorZ = 1.0f;

            //qDebug() << v.x() << "  x" << factor << "=  " << v.x()*factorX;

            // We apply the factor on the actual position of the point
            v.setX(v.x()*factorX);
            v.setY(v.y()*factorY);
            //v.setZ(v.z());
        }
    }
}


QVector<MeshVertex>* Cap::getVertices() {
    return &(this->vertices);
}


void Cap::generateBaseEllipsoid() {
    GLushort n = this->params.capNumberOfVerticalDivisions;
    GLushort k = this->params.capNumberOfHorizontalDivisions;
    double height = this->params.height*(1-this->params.stemHeightPart);
    double radius = this->params.junctionRadius;
    double b = this->params.capMaxRadius-this->params.junctionRadius;

    // height of a division
    double p = height/k;
    double angle = 0;
    float x = 0, y = 0, z = 0;
    // Creation of the vertices
    for (GLushort i=0; i<k; i++) {
        double h = height;
        double r = radius;
        double a = (i*1.0/k*1.0)*h;

        double newRadius;
        if(a<=0) {
            newRadius = r;
        } else {
            newRadius = sqrt(pow(b,2.0)*(1.0-pow(a-h/2.0,2.0)/pow(h/2.0,2.0)))+r-(r/h)*a;
        }

        for (GLushort j=0; j<n; j++) {
            angle = (2*M_PI/n)*j;
            x = static_cast<float>(newRadius*qCos(angle));
            y = static_cast<float>(newRadius*qSin(angle));
            z = static_cast<float>(p*i);

            MeshVertex v;
            v.id = i*n+j;
            v.setPosition(x,y,z);
            //v.color = QVector3D(0.6f, 0.2f, z/height);
            v.color = QVector3D(205/255.0, 122.0/255.0, 54.0/255.0);
            v.layer = i;
            v.baseAngle = angle;
            v.baseHeight = z;
            this->vertices.append(v);
        }
    }

    // adding a vertex at the top
    MeshVertex v;
    v.id = n*k;
    v.setPosition(0.0f, 0.0f, height);
    //v.color = QVector3D(0.6f, 0.2f, 1.0f);
    v.color = QVector3D(205/255.0, 122.0/255.0, 54.0/255.0);
    v.layer = k;
    v.baseAngle = 0;
    v.baseHeight = height;
    this->vertices.append(v);

    // Linking the different vertices
    for(auto&& v: this->vertices) {
        int i = v.id/n;

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

    for(auto&& v: this->vertices) {
        v.computeNormalVector();
    }
}

void Cap::applyBezierCurve() {
    float baseHeight = this->params.height*this->params.stemHeightPart;

    for(auto&& v: this->vertices) {
        float t = this->params.stemHeightPart+(v.z()/this->params.height);
        this->bezier.applyFullBezierTransformationToVertex(v, t, baseHeight);
    }
}

void Cap::widenCapRealisticaly() {
    GLushort n = this->params.capNumberOfVerticalDivisions;
    float h = this->params.height*(1-this->params.stemHeightPart);

    float c = 1.2; //maxRadiusFactor
    float pow = 3; //should be an odd number

    float d = 0.20; //baseMaxHeightFactor: if d=1/3, the morel will be at it's max at 1/3
    float e = 0.99; //tipMaxHeightFactor: same but for the tip

    float b1 = h*d;
    float b2 = h*e;
    float a1 = c/(qPow(b1,pow));
    float a2 = -c/(qPow(h-b2,pow));

    for(auto&& v: this->vertices) {
        int i = v.id/n;

        if(i!=0) {
            float x = v.z();
            float factor = 0;
            if(x<d*h) {
                factor = a1*qPow((x-b1),pow)+c;
            } else if(x>e*h) {
                factor = -a2*qPow((x-b2),pow)+c;
            } else {
                factor = c;
            }
            v.setPosition(factor*v.x()+v.x(), factor*v.y()+v.y(), v.z());
        }
    }

}
