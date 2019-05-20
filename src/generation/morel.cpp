#include "morel.h"

Morel::Morel()
{
    this->vertices = this->stem.getVertices();



    this->updateIndices();
}

VerticesStruct Morel::getConvertedVertices() {
    QVector<VertexData> convertedVertices;
    for(auto&& v: this->vertices) {
        convertedVertices.append({v.position, v.color});
    }

    VerticesStruct vStruct;
    vStruct.vertices = convertedVertices.data();
    vStruct.nbrVertices = convertedVertices.size();

    return vStruct;
}

IndicesStruct Morel::getConvertedIndices() {
    IndicesStruct iStruct;
    iStruct.indices = this->indices.data();
    iStruct.nbrIndices = this->indices.size();

    return iStruct;
}

void Morel::updateIndices() {
    for(auto&& v: this->vertices) {
        if(v.right != nullptr && v.bottom != nullptr) {
            this->indices.append({v.id, v.right->id, v.bottom->id});
        }
        if(v.top != nullptr && v.left != nullptr) {
            this->indices.append({v.id, v.top->id, v.left->id});
        }
    }
}
