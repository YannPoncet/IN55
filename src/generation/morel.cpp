#include "morel.h"

Morel::Morel() : cap(this->bezier), stem(this->bezier)
{
    // We copy the vertices array from the stem into the global vertices array
    for(auto&& v: *(this->stem.getVertices())) {
        this->vertices.append(v);
    }

    // We add the vertices from the cap, and increments its ids accordingly
    int size = this->vertices.size();
    for(auto&& v: *(this->cap.getVertices())) {
        v.id += size;
        this->vertices.append(v);
    }

    // We apply the size parameter on all the vertices
    this->rescaleWithGlobalFactor();

    // We compute our indices array
    this->updateIndices();
}


/*
* This function is used to return an array of VertexData that can be used by OpenGL, using the vector of MeshVertex
* @return: a struct containing the converted array of VertexData and the number of vertices
*/
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


/*
* This function is used to return an array of indices that can be used by OpenGL, using the vector of indices
* @return: a structure containing the converted array of indices and the number of indices
*/
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


/*
* This function updates the indices using the neighbours vertices of each vertex to generates the triangles
*/
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


/*
* This function rescales all the vertices by the factor in parameter
*/
void Morel::rescaleWithGlobalFactor() {
    float normalized = randomGenerator.getNormalNumber<float>(parameters.globalSizeFactor, parameters.globalSizeVariance);
    for(auto&& v: this->vertices) {
        v.rescale(static_cast<float>(normalized));
    }
}


/*
* This function can be used for debug purposes to print the bezier curve
*/
VerticesStructWithoutNormal Morel::getBezierVertices() {
    int n = 50;
    VertexDataWithoutNormal* newArray = new VertexDataWithoutNormal[n];

    for(int i=0; i<n; i++) {
        float t = ((i+1)*1.0f)/(n*1.0f);
        QVector3D p = this->bezier.getBezierPoint(t);
        VertexDataWithoutNormal vData = {p*parameters.globalSizeFactor, QVector3D(1.0f,0.0f,0.3f)};
        newArray[i] = vData;
    }

    VerticesStructWithoutNormal vStruct;
    vStruct.vertices = newArray;
    vStruct.nbrVertices = n;

    return vStruct;
}


/*
* This function can be used for debug purposes to print the bezier curve
*/
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

