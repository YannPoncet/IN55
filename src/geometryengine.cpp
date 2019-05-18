#include "geometryengine.h"

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

// Vertices of a cube 1X1
const int nbrVertices = 8;
VertexData vertices[] = {
    {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(0.0f, 1.0f,0.0f)},
    {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(0.0f, 0.0f,1.0f)},
    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 1.0f,0.0f)},
    {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(0.0f, 1.0f,1.0f)},
    {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,1.0f)},
    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 1.0f,1.0f)},
    {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 1.0f,1.0f)},
};



// Faces of the cube
const int nbrIndices = 36;
GLushort indices[] = {
    3,6,7,
    7,5,3,
    2,7,4,
    5,7,2,
    6,1,7,
    1,4,7,
    2,4,0,
    4,1,0,
    5,2,0,
    0,3,5,
    0,1,6,
    6,3,0
};


GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initGeometry()
{
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));
}

void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();


    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(/*GL_POINTS*/GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}
