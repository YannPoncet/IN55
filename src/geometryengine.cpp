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



VertexData soilVertices[] = {
    {QVector3D(-3.0f, 2.0f, 0.0f), QVector3D(41.0f/255.0, 74.0f/255.0, 28.0f/255.0)},
    {QVector3D(3.0f, 2.0f, 0.0f), QVector3D(41.0f/255.0, 74.0f/255.0, 28.0f/255.0)},
    {QVector3D(3.0f, -2.0f, 0.0f), QVector3D(41.0f/255.0, 74.0f/255.0, 28.0f/255.0)},
    {QVector3D(-3.0f, -2.0f, 0.0f), QVector3D(41.0f/255.0, 74.0f/255.0, 28.0f/255.0)},
    {QVector3D(-3.0f, 2.0f, -1.0f), QVector3D(46.0f/255.0, 29.0f/255.0, 18.0f/255.0)},
    {QVector3D(3.0f, 2.0f, -1.0f), QVector3D(46.0f/255.0, 29.0f/255.0, 18.0f/255.0)},
    {QVector3D(3.0f, -2.0f, -1.0f), QVector3D(46.0f/255.0, 29.0f/255.0, 18.0f/255.0)},
    {QVector3D(-3.0f, -2.0f, -1.0f), QVector3D(46.0f/255.0, 29.0f/255.0, 18.0f/255.0)},
};
const int nbrSoilVertices = 8;

GLushort soilIndices[] = {
    0,1,2,
    2,3,0,
    3,2,6,
    7,6,3,
    5,1,2,
    2,6,5,
    1,0,4,
    4,5,1,
    0,3,4,
    4,3,7,
    4,5,7,
    7,5,6
};
const int nbrSoilIndices = 36;


GeometryEngine::GeometryEngine() : systemIndexBuf(QOpenGLBuffer::IndexBuffer), soilIndexBuf(QOpenGLBuffer::IndexBuffer), indexBuf(QOpenGLBuffer::IndexBuffer), bezierIndexBuf(QOpenGLBuffer::IndexBuffer)  {
    initializeOpenGLFunctions();

    if(showSystem) {
        systemArrayBuf.create();
        systemIndexBuf.create();
    }

    if(showSoil) {
        soilArrayBuf.create();
        soilIndexBuf.create();
    }

    if(showBezier) {
        bezierArrayBuf.create();
        bezierIndexBuf.create();
    }


    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine() {
    if(showSystem) {
        systemArrayBuf.destroy();
        systemIndexBuf.destroy();
    }

    if(showSoil) {
        soilArrayBuf.destroy();
        soilIndexBuf.destroy();
    }

    if(showBezier) {
        bezierArrayBuf.destroy();
        bezierIndexBuf.destroy();
    }

    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::createAndBindMorels() {
    Morel morel1;
    IndicesStruct indicesStruct = morel1.getConvertedIndices();
    VerticesStruct verticesStruct = morel1.getConvertedVertices();
    arrayBuf.bind();
    arrayBuf.allocate(verticesStruct.vertices, verticesStruct.nbrVertices * static_cast<int>(sizeof(VertexData)));
    indexBuf.bind();
    indexBuf.allocate(indicesStruct.indices, indicesStruct.nbrIndices * static_cast<int>(sizeof(GLushort)));
    delete[] verticesStruct.vertices;
    delete[] indicesStruct.indices;

    if(showBezier) {
        IndicesStruct bezierIndicesStruct = morel1.getBezierIndices();
        VerticesStruct bezierVerticesStruct = morel1.getBezierVertices();
        bezierArrayBuf.bind();
        bezierArrayBuf.allocate(bezierVerticesStruct.vertices, bezierVerticesStruct.nbrVertices * static_cast<int>(sizeof(VertexData)));
        bezierIndexBuf.bind();
        bezierIndexBuf.allocate(bezierIndicesStruct.indices, bezierIndicesStruct.nbrIndices * static_cast<int>(sizeof(GLushort)));
    }
}

void GeometryEngine::initGeometry() {
    this->createAndBindMorels();

    if(showSystem) {
        systemArrayBuf.bind();
        systemArrayBuf.allocate(systemVertices, nbrSystemVertices * static_cast<int>(sizeof(VertexData)));
        systemIndexBuf.bind();
        systemIndexBuf.allocate(systemIndices, nbrSystemIndices * static_cast<int>(sizeof(GLushort)));
    }

    if(showSoil) {
        soilArrayBuf.bind();
        soilArrayBuf.allocate(soilVertices, nbrSoilVertices * static_cast<int>(sizeof(VertexData)));
        soilIndexBuf.bind();
        soilIndexBuf.allocate(soilIndices, nbrSoilIndices * static_cast<int>(sizeof(GLushort)));
    }
}

void GeometryEngine::drawMorels(QOpenGLShaderProgram *program) {
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

    offset += sizeof(QVector3D);

    int normalLocation = program->attributeLocation("normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, indexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
    //glDrawElements(GL_POINTS, indexBuf.size(), GL_UNSIGNED_SHORT, nullptr);

    if(showBezier) {
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
}

void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program) {
    this->drawMorels(program);

    quintptr offset = 0;
    int vertexLocation = 0;
    int colorLocation = 0;
    if(showSystem) {
        systemArrayBuf.bind();
        systemIndexBuf.bind();
        offset = 0;
        vertexLocation = vertexLocation = program->attributeLocation("position");
        program->enableAttributeArray(vertexLocation);
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        offset += sizeof(QVector3D);
        colorLocation = program->attributeLocation("color");
        program->enableAttributeArray(colorLocation);
        program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        glDrawElements(GL_LINES, systemIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
        glDrawElements(GL_POINTS, systemIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
    }

    if(showSoil) {
        soilArrayBuf.bind();
        soilIndexBuf.bind();
        offset = 0;
        vertexLocation = program->attributeLocation("position");
        program->enableAttributeArray(vertexLocation);
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        offset += sizeof(QVector3D);
        colorLocation = program->attributeLocation("color");
        program->enableAttributeArray(colorLocation);
        program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        glDrawElements(GL_TRIANGLES, soilIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
    }
}
