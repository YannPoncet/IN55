#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>

#include <QDebug>

#include "tools/structs.h"
#include "generation/morel.h"

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawGeometry(QOpenGLShaderProgram *program);
    void drawCube(QOpenGLShaderProgram *program);

private:
    void initGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;


};

#endif // GEOMETRYENGINE_H
