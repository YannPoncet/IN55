#include "voronoi.h"

Voronoi::Voronoi(int xMax, int yMax, int maxNbPoints, int width, double fMax, double fMin) {
    this->xMax = xMax;
    this->yMax = yMax;
    this->maxNbPoints = maxNbPoints;
    this->width = width;
    this->fMax = fMax;
    this->fMin = fMin;

    this->distanceType = 1;
    this->separationFactor = this->width/10;

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

    // Then, we find the second point, closest to... cannot explain here must be done on paper
    for(auto&& p: this->points) {
        if(p != p1) {
            QVector2D A(x,y);
            QVector2D P1 = p1;
            QVector2D P2 = p;
            // u = vector between P1 and P2
            QVector2D u(P2.x()-P1.x(),P2.y()-P1.y());
            // v = vector between P1 and A
            QVector2D v(A.x()-P1.x(),A.y()-P1.y());
            // M = middle of P1P2
            QVector2D M((P1.x()+P2.x())/2.0, (P1.y()+P2.y())/2.0);

            if(u.dotProduct(u,v) > 0) {
                // We compute the intersection point between the lines P1P2 going through M and P1A going through A
                QVector2D H = this->perpendicularLineLineIntersection(P1,P2, P1,A, M, A);
                // We find the closest distance to the different Hs
                d = dist(H.x()-P1.x(), H.y()-P1.y());
                if(d<d2) {
                    d2 = d;
                    p2 = P2;
                }
            }
        }
    }

    // Now, p2 is the closest point of the triangle... cannot explain either :)
    // We compute the distance between P1 and the given point
    double distP1A = dist(x-p1.x(), y-p1.y());

    //qDebug() << distP1A << d2;
    if(d2-distP1A <= this->width/2.0) {
        return this->fMax;
    }

    // We get the ratio of its distance to the side of the polygon
    double ratio = distP1A/(d2-this->width/2.0);
    double invertedRatio = 1-ratio;

    return this->factorFunction(invertedRatio);
}


QVector2D Voronoi::perpendicularLineLineIntersection(QVector2D A, QVector2D B, QVector2D C, QVector2D D, QVector2D Pab, QVector2D Pcd)
{
    double b1 = B.y() - A.y();
    double a1 = B.x() - A.x();
    double c1 = a1*(Pab.x()) + b1*(Pab.y());

    // Line CD represented as a2x + b2y = c2
    double a2 = D.y() - C.y();
    double b2 = C.x() - D.x();
    double c2 = a2*(Pcd.x())+ b2*(Pcd.y());

    double determinant = a1*b2 - a2*b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return QVector2D(INFINITY, INFINITY);
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return QVector2D(x, y);
    }
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
    return randomGenerator.getFastRandom(0, max);
}


double Voronoi::dist(double x, double y) {
    switch (this->distanceType) {
    case 1: return sqrt(qPow(x,2.0)+qPow(y,2.0)); // Euclidian distance
    case 2: return abs(x)+abs(y); // Manhattan
    case 3: return pow(pow(abs(x),3.0) + pow(abs(y),3.0),1.0/3.0); // Minkovski
   }
}



