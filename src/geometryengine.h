#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>

#include <QDebug>

#include "structures/structs.h"
#include "generation/morel.h"

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawGeometry(QOpenGLShaderProgram *program);
    void drawCube(QOpenGLShaderProgram *program);
    void initGeometry();
    void createAndBindMorels();
    void drawMorels(QOpenGLShaderProgram *program);

private:
    QOpenGLBuffer systemArrayBuf;
    QOpenGLBuffer systemIndexBuf;

    QOpenGLBuffer soilArrayBuf;
    QOpenGLBuffer soilIndexBuf;

    QOpenGLBuffer bezierArrayBuf;
    QOpenGLBuffer bezierIndexBuf;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    QOpenGLBuffer lightsArrayBuf;
    QOpenGLBuffer lightsIndexBuf;

    void computeLightVertices(VertexData *array, int index, QVector3D lightPosition, double size=.1);
    QVector3D computeNormal(QVector3D o, QVector3D a, QVector3D b, QVector3D c);
};

#endif // GEOMETRYENGINE_H
