#include "voronoi.h"

Voronoi::Voronoi(int xMax, int yMax, int maxNbPoints, int width, double fMax, double fMin) {
    this->xMax = xMax;
    this->yMax = yMax;
    this->maxNbPoints = maxNbPoints;
    this->width = width;
    this->fMax = fMax;
    this->fMin = fMin;

    this->distanceType = 3;
    this->separationFactor = 2;

}


void Voronoi::generatePoints() {
    for(int i=0; i<this->maxNbPoints; i++) {
        int x = this->randgen(this->xMax);
        int y = this->randgen(this->yMax);

        for(auto&& p: this->points) {
            double d = dist(x-p.x(), y-p.y());
            if(d<this->separationFactor*this->width) {
                return;
            }
        }

        this->points.append(QVector2D(x, y));
    }
}


double Voronoi::getFactorAt(double x, double y) {
    double d1 = INFINITY;
    double d2 = INFINITY;
    double d = 0;
    QVector2D p1;

    // First, we find the closest point of the coordinates and store its distance in d1
    for(auto&& p: this->points) {
        double d = dist(x-p.x(), y-p.y());
        if(d<d1) {
            d1 = d;
            p1 = p;
        }
    }

    // Then, we find the second closest point and store its distance in d2
    for(auto&& p: this->points) {
        double d = dist(x-p.x(), y-p.y());
        if(d<d2 && p!=p1) {
            d2 = d;
        }
    }

    // If the point is in this->width between p1 and p2
    if((d2-d1) < (this->width/2)) {
        return this->fMax;
    }

    return this->fMin;
}


/*
* This function is used to give a value between fMax and fMin, following
* an inverse function.
* @param x between 0 and 1, ordoninate used in the functions computation
* @return the result of the function
*/
double Voronoi::factorFunction(double x) {
    double k = 3;
    double a = (1.0/2.0)*((-1.0) - sqrt( 1.0 - ((4.0*k) / (this->fMin-this->fMax))));
    double b = this->fMax-(k/a);

    return k*(1.0/(x+a))+b;
}


int Voronoi::randgen(int max) {
    return static_cast<int>(floor(rand()*max));
}


double Voronoi::dist(int x, int y) {
    switch (this->distanceType) {
    case 1: return sqrt(x*x+y*y); // Euclidian distance
    case 2: return abs(x)+abs(y); // Manhattan
    case 3: return pow(pow(abs(x),3) + pow(abs(y),3),1/3); // Minkovski
   }
}


