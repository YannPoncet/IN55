#include "cap.h"

/*
* Constructors, creates and apply the different transformations on the vertices
*/
Cap::Cap(Bezier& b) : MorelPart(b) {
    this->height = parameters.height*(1.0f-parameters.stemHeightPart);
    this->isStem = false;

    this->generateBaseEllipsoid(); // Global shape
    this->widenCapRealisticaly(); // Better global shape
    MorelPart::applyPerlin(1, parameters.capGlobalPerlinPower); // Big variations
    this->applyVoronoiTesselation(); // Holes
    MorelPart::applyPerlin(10, parameters.capDetailsPerlinPower); // Smaller variations
    MorelPart::applyColorVariationWithPerlin(50,0.3); // Small color differences
    this->applyBezierCurve(); // Bezier curve
}


/*
* This function generates the holes using spherical coordinates and Voronoi tesselation.
*/
void Cap::applyVoronoiTesselation() {
    double fMax = 1.6;
    double fMin = 0.8;
    double densityFactor = parameters.holesDensityFactor;
    double widthFactor = parameters.holesEdgesWidthFactor;
    Voronoi voronoiGenerator(1000, 1000, 300*densityFactor, 15*widthFactor, fMax, fMin);

    float h = this->height;
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

            float tmp_angle = asin(sin(theta));
            if(cos(theta) < 0) {
                tmp_angle = M_PI-tmp_angle;
            } else if(tmp_angle < 0) {
                tmp_angle += 2*M_PI;
            }
            theta = tmp_angle;

            // We compute the noise and apply it to the radius
            double factor = voronoiGenerator.getFactorAt((theta)/(2*M_PI), (phi+M_PI)/(2*M_PI));
            if(abs(factor-fMax) <= 0.001f) {
                v.color = parameters.colorSets[parameters.choosenSet].holesEdgesColor;
            }
            r = r*factor;

            // We could replace this by a shadow shader
            v.color = QVector3D(v.color.x()*pow(r,1.0/3.0), v.color.y()*pow(r,1.0/3.0), v.color.z()*pow(r,1.0/3.0));
            if(v.color.x()<0) v.color.setX(0);
            if(v.color.y()<0) v.color.setY(0);
            if(v.color.z()<0) v.color.setZ(0);
            if(v.color.x()>1) v.color.setX(1);
            if(v.color.y()>1) v.color.setY(1);
            if(v.color.z()>1) v.color.setZ(1);

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


/*
* This function generates the base shape of the cap.
*/
void Cap::generateBaseEllipsoid() {
    GLushort n = parameters.capNumberOfVerticalDivisions;
    GLushort k = parameters.capNumberOfHorizontalDivisions;
    double height = this->height;
    double radius = parameters.junctionRadius;
    double b = randomGenerator.getNormalNumber<float>(parameters.capMaxRadiusFactor, parameters.capMaxRadiusVariance)-parameters.junctionRadius;

    // p = height of a division
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
            // We use a mathematical function that generates half an ellipsoid depending on the height of the point
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
            //qDebug() << v.z();
            v.color = parameters.colorSets[parameters.choosenSet].capColor;
            //v.color = QVector3D(0.6f, 0.2f, z/height);
            v.layer = i;
            v.baseAngle = angle;
            v.baseHeight = z;
            this->vertices.append(v);
        }
    }

    // Adding a vertex at the top
    MeshVertex v;
    v.id = n*k;
    v.setPosition(0.0f, 0.0f, height);
    v.color = parameters.colorSets[parameters.choosenSet].capColor; v.layer = k;
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


/*
* This function applies the Bezier curve to the points depending on their height.
*/
void Cap::applyBezierCurve() {
    float baseHeight = parameters.height*parameters.stemHeightPart;

    for(auto&& v: this->vertices) {
        float t = parameters.stemHeightPart+(v.z()/parameters.height);
        this->bezier.applyFullBezierTransformationToVertex(v, t, baseHeight);
    }
}


/*
* This function is used to work on the global shape of the ellipsoid.
* Uses mathematical functions to do it.
*/
void Cap::widenCapRealisticaly() {
    GLushort n = parameters.capNumberOfVerticalDivisions;
    float h = parameters.height*(1-parameters.stemHeightPart);

    float c = parameters.capMaxRadiusFactor2;
    float pow = 3; //should be an odd number

    float d = parameters.capBaseMaxRadiusLocationFactor;
    float e = parameters.capTipMaxRadiusLocationFactor;

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
