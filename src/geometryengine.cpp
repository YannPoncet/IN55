#include "geometryengine.h"
#include "globals.h"


GeometryEngine::GeometryEngine() : systemIndexBuf(QOpenGLBuffer::IndexBuffer), soilIndexBuf(QOpenGLBuffer::IndexBuffer), bezierIndexBuf(QOpenGLBuffer::IndexBuffer), indexBuf(QOpenGLBuffer::IndexBuffer), lightsIndexBuf(QOpenGLBuffer::IndexBuffer) {
    initializeOpenGLFunctions();

    // Coordinates system VBOs
    systemArrayBuf.create();
    systemIndexBuf.create();


    // Soil VBOs
    soilArrayBuf.create();
    soilIndexBuf.create();


    // Bezier curve VBOs
    bezierArrayBuf.create();
    bezierIndexBuf.create();

    //Lights VBOs
    lightsArrayBuf.create();
    lightsIndexBuf.create();


    // Main VBOs, morel
    arrayBuf.create();
    indexBuf.create();

    // Initializes geometry and transfers it to VBOs
    initGeometry();
}

GeometryEngine::~GeometryEngine() {
    systemArrayBuf.destroy();
    systemIndexBuf.destroy();

    soilArrayBuf.destroy();
    soilIndexBuf.destroy();

    bezierArrayBuf.destroy();
    bezierIndexBuf.destroy();

    lightsArrayBuf.destroy();
    lightsIndexBuf.destroy();

    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::createAndBindMorels() {
    parameters.choosenSet = randomGenerator.getFastRandom(0, parameters.colorSets.size()-1);

    Morel morel1;
    IndicesStruct indicesStruct = morel1.getConvertedIndices();
    VerticesStruct verticesStruct = morel1.getConvertedVertices();
    arrayBuf.bind();
    arrayBuf.allocate(verticesStruct.vertices, verticesStruct.nbrVertices * static_cast<int>(sizeof(VertexData)));
    indexBuf.bind();
    indexBuf.allocate(indicesStruct.indices, indicesStruct.nbrIndices * static_cast<int>(sizeof(GLushort)));
    delete[] verticesStruct.vertices;
    delete[] indicesStruct.indices;

    IndicesStruct bezierIndicesStruct = morel1.getBezierIndices();
    VerticesStructWithoutNormal bezierVerticesStruct = morel1.getBezierVertices();
    bezierArrayBuf.bind();
    bezierArrayBuf.allocate(bezierVerticesStruct.vertices, bezierVerticesStruct.nbrVertices * static_cast<int>(sizeof(VertexDataWithoutNormal)));
    bezierIndexBuf.bind();
    bezierIndexBuf.allocate(bezierIndicesStruct.indices, bezierIndicesStruct.nbrIndices * static_cast<int>(sizeof(GLushort)));
}

void GeometryEngine::initGeometry() {
    this->createAndBindMorels();

    VertexDataWithoutNormal systemVertices[] = {
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

    systemArrayBuf.bind();
    systemArrayBuf.allocate(systemVertices, nbrSystemVertices * static_cast<int>(sizeof(VertexDataWithoutNormal)));
    systemIndexBuf.bind();
    systemIndexBuf.allocate(systemIndices, nbrSystemIndices * static_cast<int>(sizeof(GLushort)));


    QVector3D color1 = QVector3D(41.0f/255.0f, 74.0f/255.0f, 28.0f/255.0f);
    QVector3D color2 = QVector3D(43.0f/255.0f, 22.0f/255.0f, 14.0f/255.0f);
    QVector3D P0 = QVector3D(-3.0f, 2.0f, 0.0f);
    QVector3D P1 = QVector3D(3.0f, 2.0f, 0.0f);
    QVector3D P2 = QVector3D(3.0f, -2.0f, 0.0f);
    QVector3D P3 = QVector3D(-3.0f, -2.0f, 0.0f);
    QVector3D P4 = QVector3D(-3.0f, 2.0f, -1.0f);
    QVector3D P5 = QVector3D(3.0f, 2.0f, -1.0f);
    QVector3D P6 = QVector3D(3.0f, -2.0f, -1.0f);
    QVector3D P7 = QVector3D(-3.0f, -2.0f, -1.0f);
    VertexData soilVertices[] = {
        {P0, color1, QVector3D::crossProduct(P0-P3,P0-P1)+QVector3D::crossProduct(P0-P1,P0-P4)+QVector3D::crossProduct(P0-P4,P0-P3), QVector2D(0.0f, 1.0f), 1.0},
        {P1, color1, QVector3D::crossProduct(P1-P0,P1-P2)+QVector3D::crossProduct(P1-P2,P1-P5)+QVector3D::crossProduct(P1-P5,P1-P0), QVector2D(1.0f, 1.0f), 1.0},
        {P2, color1, QVector3D::crossProduct(P2-P1,P2-P3)+QVector3D::crossProduct(P2-P3,P2-P6)+QVector3D::crossProduct(P2-P6,P2-P1), QVector2D(1.0f, 0.0f), 1.0},
        {P3, color1, QVector3D::crossProduct(P3-P2,P3-P0)+QVector3D::crossProduct(P3-P0,P3-P7)+QVector3D::crossProduct(P3-P7,P3-P2), QVector2D(0.0f, 0.0f), 1.0},

        {P4, color2, QVector3D::crossProduct(P4-P7,P4-P0)+QVector3D::crossProduct(P4-P0,P4-P5)+QVector3D::crossProduct(P4-P5,P4-P7), QVector2D(), 0.0},
        {P5, color2, QVector3D::crossProduct(P5-P6,P5-P4)+QVector3D::crossProduct(P5-P4,P5-P1)+QVector3D::crossProduct(P5-P1,P5-P6), QVector2D(), 0.0},
        {P6, color2, QVector3D::crossProduct(P6-P5,P6-P2)+QVector3D::crossProduct(P6-P2,P6-P7)+QVector3D::crossProduct(P6-P7,P6-P5), QVector2D(), 0.0},
        {P7, color2, QVector3D::crossProduct(P7-P3,P7-P4)+QVector3D::crossProduct(P7-P4,P7-P6)+QVector3D::crossProduct(P7-P6,P7-P3), QVector2D(), 0.0},

        {P0, color2, QVector3D::crossProduct(P0-P3,P0-P1)+QVector3D::crossProduct(P0-P1,P0-P4)+QVector3D::crossProduct(P0-P4,P0-P3), QVector2D(), 0.0},
        {P1, color2, QVector3D::crossProduct(P1-P0,P1-P2)+QVector3D::crossProduct(P1-P2,P1-P5)+QVector3D::crossProduct(P1-P5,P1-P0), QVector2D(), 0.0},
        {P2, color2, QVector3D::crossProduct(P2-P1,P2-P3)+QVector3D::crossProduct(P2-P3,P2-P6)+QVector3D::crossProduct(P2-P6,P2-P1), QVector2D(), 0.0},
        {P3, color2, QVector3D::crossProduct(P3-P2,P3-P0)+QVector3D::crossProduct(P3-P0,P3-P7)+QVector3D::crossProduct(P3-P7,P3-P2), QVector2D(), 0.0},
    };
    const int nbrSoilVertices = 12;

    GLushort soilIndices[] = {
        0,1,2,
        2,3,0,

        11,10,6,
        7,6,11,
        5,9,10,
        10,6,5,
        9,8,4,
        4,5,9,
        8,11,4,
        4,11,7,
        4,5,7,
        7,5,6
    };
    const int nbrSoilIndices = 36;

    soilArrayBuf.bind();
    soilArrayBuf.allocate(soilVertices, nbrSoilVertices * static_cast<int>(sizeof(VertexData)));
    soilIndexBuf.bind();
    soilIndexBuf.allocate(soilIndices, nbrSoilIndices * static_cast<int>(sizeof(GLushort)));

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
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexDataWithoutNormal));
        offset += sizeof(QVector3D);
        colorLocation = program->attributeLocation("color");
        program->enableAttributeArray(colorLocation);
        program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexDataWithoutNormal));
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
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexDataWithoutNormal));
        offset += sizeof(QVector3D);
        colorLocation = program->attributeLocation("color");
        program->enableAttributeArray(colorLocation);
        program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexDataWithoutNormal));
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
        offset += sizeof(QVector3D);
        int normalLocation = program->attributeLocation("normal");
        program->enableAttributeArray(normalLocation);
        program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        offset += sizeof(QVector3D);
        int texcoordLocation = program->attributeLocation("a_texcoord");
        program->enableAttributeArray(texcoordLocation);
        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
        offset += sizeof(QVector2D);
        int texpartLocation = program->attributeLocation("a_texpart");
        program->enableAttributeArray(texpartLocation);
        program->setAttributeBuffer(texpartLocation, GL_FLOAT, offset, 1, sizeof(VertexData));
        glDrawElements(GL_TRIANGLES, soilIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
    }

    if(showLights) {
        //Lights positions for drawing "cube light" except for the camera light
        const int nbrLights = 4;
        QVector3D lightPositions[nbrLights];
        lightPositions[0] = QVector3D(-3.0f, 2.0f, 3.0f);
        lightPositions[1] = QVector3D(3.0f, 2.0f, 3.0f);
        lightPositions[2] = QVector3D(3.0f, -2.0f, 3.0f);
        lightPositions[3] = QVector3D(-3.0f, -2.0f, 3.0f);

        const int nbrLightsVertices = 8*nbrLights;
        VertexData lightsVertices[nbrLightsVertices];
        for(int i=0; i<nbrLights; i++){
            computeLightVertices(lightsVertices, i, lightPositions[i]);
        }

        const int nbrLightsIndices = 36*nbrLights;
        GLushort lightsIndices[nbrLightsIndices];
        GLushort lightIndices[] = {
            0,1,2,
            2,3,0,

            0,4,7,
            7,3,0,

            0,4,5,
            5,1,0,

            1,5,6,
            6,2,1,

            6,2,3,
            3,7,6,

            7,6,5,
            5,4,7
        };

        for(int i=0; i<nbrLights; i++){
            for(int j=0; j<36; j++){
                lightsIndices[36*i+j] = lightIndices[j] + 8*i;
            }
        }

        lightsArrayBuf.bind();
        lightsArrayBuf.allocate(lightsVertices, nbrLightsVertices * static_cast<int>(sizeof(VertexData)));
        lightsIndexBuf.bind();
        lightsIndexBuf.allocate(lightsIndices, nbrLightsIndices * static_cast<int>(sizeof(GLushort)));

        lightsArrayBuf.bind();
        lightsIndexBuf.bind();
        offset = 0;
        vertexLocation = program->attributeLocation("position");
        program->enableAttributeArray(vertexLocation);
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        offset += sizeof(QVector3D);
        colorLocation = program->attributeLocation("color");
        program->enableAttributeArray(colorLocation);
        program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        offset += sizeof(QVector3D);
        int normalLocation = program->attributeLocation("normal");
        program->enableAttributeArray(normalLocation);
        program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        offset += sizeof(QVector3D);
        int texcoordLocation = program->attributeLocation("a_texcoord");
        program->enableAttributeArray(texcoordLocation);
        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
        offset += sizeof(QVector2D);
        int texpartLocation = program->attributeLocation("a_texpart");
        program->enableAttributeArray(texpartLocation);
        program->setAttributeBuffer(texpartLocation, GL_FLOAT, offset, 1, sizeof(VertexData));
        glDrawElements(GL_TRIANGLES, lightsIndexBuf.size(), GL_UNSIGNED_SHORT, nullptr);
    }
}

void GeometryEngine::computeLightVertices(VertexData *array, int index, QVector3D lightPosition, double size){
    QVector3D cubeColor = QVector3D(0.0,0.0,0.0); //black color
    if(lightsEnabled[index])
        cubeColor = QVector3D(1.0,1.0,1.0); //white if enabled

    //Upper face of cube
    QVector3D tmpPose1 = QVector3D(lightPosition[0] - size, lightPosition[1] - size, lightPosition[2] + size);
    QVector3D tmpPose2 = QVector3D(lightPosition[0] + size, lightPosition[1] - size, lightPosition[2] + size);
    QVector3D tmpPose3 = QVector3D(lightPosition[0] + size, lightPosition[1] + size, lightPosition[2] + size);
    QVector3D tmpPose4 = QVector3D(lightPosition[0] - size, lightPosition[1] + size, lightPosition[2] + size);

    //Down face of cube
    QVector3D tmpPose5 = QVector3D(lightPosition[0] - size, lightPosition[1] - size, lightPosition[2] - size);
    QVector3D tmpPose6 = QVector3D(lightPosition[0] + size, lightPosition[1] - size, lightPosition[2] - size);
    QVector3D tmpPose7 = QVector3D(lightPosition[0] + size, lightPosition[1] + size, lightPosition[2] - size);
    QVector3D tmpPose8 = QVector3D(lightPosition[0] - size, lightPosition[1] + size, lightPosition[2] - size);

    //Normals are vectors from the vertex to the lightPosition (center of cube)
    array[8*index + 0] = {tmpPose1, cubeColor, lightPosition - tmpPose1, QVector2D(), 0};
    array[8*index + 1] = {tmpPose2, cubeColor, lightPosition - tmpPose2, QVector2D(), 0};
    array[8*index + 2] = {tmpPose3, cubeColor, lightPosition - tmpPose3, QVector2D(), 0};
    array[8*index + 3] = {tmpPose4, cubeColor, lightPosition - tmpPose4, QVector2D(), 0};
    array[8*index + 4] = {tmpPose5, cubeColor, lightPosition - tmpPose5, QVector2D(), 0};
    array[8*index + 5] = {tmpPose6, cubeColor, lightPosition - tmpPose6, QVector2D(), 0};
    array[8*index + 6] = {tmpPose7, cubeColor, lightPosition - tmpPose7, QVector2D(), 0};
    array[8*index + 7] = {tmpPose8, cubeColor, lightPosition - tmpPose8, QVector2D(), 0};
}
