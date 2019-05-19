#include "cap.h"

Cap::Cap() {

}

QVector<VertexData> Cap::getVertices() {
    return this->vertices;
}

QVector<GLushort> Cap::getIndices() {
    return this->indices;
}
