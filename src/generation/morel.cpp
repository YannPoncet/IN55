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
        if(v.bottom != nullptr && v.bottom->right != nullptr && v.right != nullptr) {
            //qDebug() << "-";
            //qDebug() << v.id << ", bot=" << v.bottom->id << ", bottomright =" << v.bottom->right->id;
            this->indices.append({v.id, v.bottom->id, v.bottom->right->id});
            //qDebug() << v.id << ", bottomright=" << v.bottom->right->id << ", right =" <<  v.right->id;
            this->indices.append({v.id, v.bottom->right->id, v.right->id});
        }
    }
}
