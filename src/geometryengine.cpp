#include "geometryengine.h"

VertexData systemVertices[] = {
    {QVector3D(0.0f, 0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)}, // x is red
    {QVector3D(5.0f, 0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
    {QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)}, // y is green
    {QVector3D(0.0f, 5.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)},
    {QVector3D(0.0f, 0.0f, -5.0f), QVector3D(0.0f, 0.0f, 1.0f)}, // z is blue
    {QVector3D(0.0f, 0.0f, 5.0f), QVector3D(0.0f, 0.0f, 1.0f)},
};

const int nbrSystemVertices = 6;

GLushort systemIndices[] = {
    0,1,
    2,3,
    4,5
};

const int nbrSystemIndices = 6;

GeometryEngine::GeometryEngine() : systemIndexBuf(QOpenGLBuffer::IndexBuffer), indexBuf(QOpenGLBuffer::IndexBuffer), bezierIndexBuf(QOpenGLBuffer::IndexBuffer)  {
    initializeOpenGLFunctions();

    systemArrayBuf.create();
    systemIndexBuf.create();

    bezierArrayBuf.create();
    bezierIndexBuf.create();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine() {
    systemArrayBuf.destroy();
    systemIndexBuf.destroy();

    bezierArrayBuf.destroy();
    bezierIndexBuf.destroy();

    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initGeometry() {
    Morel morel1;
    IndicesStruct indicesStruct = morel1.getConvertedIndices();
    VerticesStruct verticesStruct = morel1.getConvertedVertices();


    IndicesStruct bezierIndicesStruct = morel1.getBezierIndices();
    VerticesStruct bezierVerticesStruct = morel1.getBezierVertices();
    bezierArrayBuf.bind();
    bezierArrayBuf.allocate(bezierVerticesStruct.vertices, bezierVerticesStruct.nbrVertices * static_cast<int>(sizeof(VertexData)));
    bezierIndexBuf.bind();
    bezierIndexBuf.allocate(bezierIndicesStruct.indices, bezierIndicesStruct.nbrIndices * static_cast<int>(sizeof(GLushort)));

    systemArrayBuf.bind();
    systemArrayBuf.allocate(systemVertices, nbrSystemVertices * static_cast<int>(sizeof(VertexData)));
    systemIndexBuf.bind();
    systemIndexBuf.allocate(systemIndices, nbrSystemIndices * static_cast<int>(sizeof(GLushort)));

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(verticesStruct.vertices, verticesStruct.nbrVertices * static_cast<int>(sizeof(VertexData)));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indicesStruct.indices, indicesStruct.nbrIndices * static_cast<int>(sizeof(GLushort)));
}

void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program) {
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

    //qDebug() << indexBuf.size();
    //qDebug() << (arrayBuf.size()/sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, indexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
    //glDrawElements(GL_POINTS, indexBuf.size(), GL_UNSIGNED_SHORT, nullptr);


    systemArrayBuf.bind();
    systemIndexBuf.bind();
    offset = 0;
    vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
    offset += sizeof(QVector3D);
    colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
    glDrawElements(GL_LINES, systemIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
    glDrawElements(GL_POINTS, systemIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);


    bezierArrayBuf.bind();
    bezierIndexBuf.bind();
    offset = 0;
    vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
    offset += sizeof(QVector3D);
    colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
    glDrawElements(GL_LINE_STRIP, bezierIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
    //glDrawElements(GL_POINTS, bezierIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
}
