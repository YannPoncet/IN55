#include "voronoi.h"

Voronoi::Voronoi(int xMax, int yMax, int maxNbPoints, int width, double fMax, double fMin) {
    this->xMax = xMax;
    this->yMax = yMax;
    this->maxNbPoints = maxNbPoints;
    this->width = width;
    this->fMax = fMax;
    this->fMin = fMin;

    this->distanceType = 1;
    this->separationFactor = 2;

    this->generatePoints();
    qsrand(0);
}


void Voronoi::generatePoints() {
    for(int i=0; i<this->maxNbPoints; i++) {
        int x = this->randgen(this->xMax);
        int y = this->randgen(this->yMax);
        bool doNotAdd = false;

        for(auto&& p: this->points) {
            double d = dist(x-p.x(), y-p.y());
            if(d<this->separationFactor*this->width) {
                doNotAdd = true;
            }
        }

        if(!doNotAdd) {
            this->points.append(QVector2D(x, y));
        }
    }
}


/*
* This function is used to compute the voronoi tesselation
* @param x between 0 and 1
* @param y between 0 and 1
* @return a factor between this->fMin and this->fMax
*/
double Voronoi::getFactorAt(double x, double y) {
    x = x*this->xMax;
    y = y*this->yMax;

    double d1 = this->xMax;
    double d2 = this->yMax;
    double d = 0;
    QVector2D p1, p2;

    // First, we find the closest point of the coordinates and store its distance in d1
    for(auto&& p: this->points) {
        d = dist(x-p.x(), y-p.y());
        if(d<d1) {
            d1 = d;
            p1 = p;
        }
    }

    // Then, we find the second closest point and store its distance in d2
    for(auto&& p: this->points) {
        d = dist(x-p.x(), y-p.y());
        if(d<d2 && p.x()!=p1.x()) {
            d2 = d;
            p2 = p;
        }
    }

    // If the point is in this->width between p1 and p2
    double d12 = this->dist(p1.x()-p2.x(), p1.y()-p2.y());
    double halfwayDist = d12/2.0;

    QVector2D v(p2.x()-p1.x(), p2.y()-p1.y());
    QVector2D u(x-p1.x(), y-p1.y());
    double distFactor = ((x-p1.x())*v.x()+(y-p1.y())*v.y())/this->dist(v.x(), v.y());


    if(halfwayDist-distFactor <= this->width/2.0) {
        return this->fMax;
    }

    if(distFactor >= 0) {
        qDebug() << distFactor << halfwayDist << halfwayDist - this->width/2.0;
        return this->factorFunction((-1.0/(halfwayDist-this->width/2.0))*distFactor+1);
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
    double k = 1;
    double a = (1.0/2.0)*((-1.0) - sqrt( 1.0 - ((4.0*k) / (this->fMin-this->fMax))));
    double b = this->fMax-(k/a);

    return k*(1.0/(x+a))+b;
}


int Voronoi::randgen(int max) {
    return randomGenerator.getRand(0, max);
}


double Voronoi::dist(int x, int y) {
    switch (this->distanceType) {
    case 1: return sqrt(x*x+y*y); // Euclidian distance
    case 2: return abs(x)+abs(y); // Manhattan
    case 3: return pow(pow(abs(x),3.0) + pow(abs(y),3.0),1.0/3.0); // Minkovski
   }
}


