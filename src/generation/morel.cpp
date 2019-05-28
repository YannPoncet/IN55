#include "morel.h"

Morel::Morel() : cap(this->bezier), stem(this->bezier)
{
    for(auto&& v: *(this->stem.getVertices())) {
        this->vertices.append(v);
    }

    int size = this->vertices.size();
    for(auto&& v: *(this->cap.getVertices())) {
        v.id += size;
        this->vertices.append(v);
    }

    this->rescaleWithGlobalFactor();
    this->updateIndices();
}

VerticesStruct Morel::getConvertedVertices() {
    int size = this->vertices.size();
    VertexData* newArray = new VertexData[size];

    for(int i=0; i<size; i++) {
        this->vertices[i].computeNormalVector();
        VertexData vData = {this->vertices[i].position, this->vertices[i].color, this->vertices[i].normal};
        newArray[i] = vData;
    }

    VerticesStruct vStruct;
    vStruct.vertices = newArray;
    vStruct.nbrVertices = size;

    return vStruct;
}

IndicesStruct Morel::getConvertedIndices() {
    int size = this->indices.size();
    GLushort* newArray = new GLushort[size];

    for(int i=0; i<size; i++) {
        newArray[i] = this->indices[i];
    }

    IndicesStruct iStruct;
    iStruct.indices = newArray;
    iStruct.nbrIndices = size;

    return iStruct;
}

void Morel::updateIndices() {
    for(auto&& v: this->vertices) {
        if(v.right != nullptr && v.bottom != nullptr) {
            this->indices.append({v.id, v.bottom->id, v.right->id});
        }
        if(v.top != nullptr && v.left != nullptr) {
            this->indices.append({v.id, v.top->id, v.left->id});
        }
    }
}

void Morel::rescaleWithGlobalFactor() {
    float normalized = randomGenerator.getNormalNumber<float>(parameters.globalSizeFactor, parameters.globalSizeVariance);
    for(auto&& v: this->vertices) {
        v.rescale(static_cast<float>(normalized));
    }
}

VerticesStruct Morel::getBezierVertices() {
    int n = 50;
    VertexData* newArray = new VertexData[n];

    for(int i=0; i<n; i++) {
        float t = ((i+1)*1.0f)/(n*1.0f);
        QVector3D p = this->bezier.getBezierPoint(t, parameters.height, parameters.stemHeightPart);
        VertexData vData = {p*parameters.globalSizeFactor, QVector3D(1.0f,0.0f,0.3f)};
        newArray[i] = vData;
    }

    VerticesStruct vStruct;
    vStruct.vertices = newArray;
    vStruct.nbrVertices = n;

    return vStruct;
}

IndicesStruct Morel::getBezierIndices() {
    int n = 50;
    GLushort* newArray = new GLushort[n];

    for(int i=0; i<n; i++) {
        newArray[i] = i;
    }

    IndicesStruct iStruct;
    iStruct.indices = newArray;
    iStruct.nbrIndices = n;

    return iStruct;
}

