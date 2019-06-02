#include "morelpart.h"

MorelPart::MorelPart(Bezier& bezier) : bezier(bezier) {

}


/*
* This function returns all the vertices.
* @return: the vertices
*/
QVector<MeshVertex>* MorelPart::getVertices() {
    return &(this->vertices);
}


/*
* This function apply shape variations using a Perlin noise and spherical coordinates.
*/
void MorelPart::applyPerlin(int octaves, double factor) {
    const siv::PerlinNoise perlinNoise(randomGenerator.getGenerator().operator()());

    float h = this->height;
    for(auto&& v: this->vertices) {
        if(v.layer!=0) {
            // We create a sphere of radius 1 centered on O on which we'll apply perlin
            float sZ;
            if(this->isStem) {
                sZ = 2.0*(v.baseHeight+(h/2.0))/h;
            } else {
                sZ = 2.0*(v.baseHeight-(h/2.0))/h;
            }
            double sR = sqrt(1.0-pow(sZ,2.0));
            float sX = sR*cos(v.baseAngle);
            float sY = sR*sin(v.baseAngle);

            // We convert the point's coordinate into spherical coordinates
            float r = 1.0f;
            float theta = atan2(sY, sX);
            float phi = acos(sZ);

            // We compute the noise and apply it to the radius
            double noise = perlinNoise.octaveNoise(cos(theta), sin(theta), phi, octaves);
            if(this->isStem) {
                r = r+r*noise*factor*(abs(v.z())/h); //For the stem, the variation decreses depending on the height
            } else {
                r = r+r*noise*factor;
            }

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
* This function is used to make color variations using a Perlin noise and spherical coordinates.
*/
void MorelPart::applyColorVariationWithPerlin(int octaves, double factor) {
    const siv::PerlinNoise perlinNoise(randomGenerator.getGenerator().operator()());

    float h = this->height;
    for(auto&& v: this->vertices) {
        if(v.layer!=0) {
            // We create a sphere of radius 1 centered on O on which we'll apply perlin
            float sZ;
            if(this->isStem) {
                sZ = 2.0*(v.baseHeight+(h/2.0))/h;
            } else {
                sZ = 2.0*(v.baseHeight-(h/2.0))/h;
            }
            double sR = sqrt(1.0-pow(sZ,2.0));
            float sX = sR*cos(v.baseAngle);
            float sY = sR*sin(v.baseAngle);

            // We convert the point's coordinate into spherical coordinates
            float r = 1.0f;
            float theta = atan2(sY, sX);
            float phi = acos(sZ);

            // We compute the noise and apply it to the radius
            double noise = perlinNoise.octaveNoise(cos(theta), sin(theta), phi, octaves);
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
