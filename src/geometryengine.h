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



};

#endif // GEOMETRYENGINE_H
