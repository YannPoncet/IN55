#include "morel.h"

Morel::Morel()
{
    this->vertices = this->stem.getVertices();
    this->indices = this->stem.getIndices();
}

VerticesStruct Morel::getConvertedVertices() {
    VerticesStruct vStruct;
    vStruct.vertices = this->vertices.data();
    vStruct.nbrVertices = this->vertices.size();

    return vStruct;
}

IndicesStruct Morel::getConvertedIndices() {
    IndicesStruct iStruct;
    iStruct.indices = this->indices.data();
    iStruct.nbrIndices = this->indices.size();

    return iStruct;
}

