/**
 * Original Author: Doron Nussbaum (C) 2011 All Rights Reserved.
 * Modified By:     Nicolas Porter, original author retains copyrights.
 * 
 * License
 * -------
 * Code can be used for instructional and educational purposes and for
 * assignments in the gaming courses at the School of Computer Science at
 * Carleton University.
 * 
 * Usage of code for other purposes is not allowed without a given
 * permission by the author.
 * 
 * 
 * Disclaimer
 * ----------
 * The code is provided as is without any warranty
 * 
 */

#pragma once

#include <vector>
#include "GraphicsComponent.h"

using std::vector;

class MeshSurfaceGraphicsComponent
    : public GraphicsComponent
{
public:
    MeshSurfaceGraphicsComponent();
    ~MeshSurfaceGraphicsComponent();

    void init(GraphicsEngine &graphicsEngine);
    void initSurface(int numRows, int numCols, float dx, float dz);
    void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

private:
    void initVertices(int rows, int columns, float xOffset, float zOffset, float yMin, float yMax);
    void initIndices(int rows, int columns);

    void initVertexBuffer(GraphicsEngine &graphicsEngine);
    void initIndexBuffer(GraphicsEngine &graphicsEngine);
    void initVertexDeclaration(GraphicsEngine &graphicsEngine);

    vector<CustomVertex> vertices;
    vector<long> indices;

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DINDEXBUFFER9 indexBuffer;
    LPDIRECT3DVERTEXDECLARATION9 vertexDeclaration;

    int vertexCount;
    int quadCount;
    int triangleCount;
    float xCellDimension;
    float zCellDimension;

    static IDirect3DVertexDeclaration9* meshDecl;

    int numRows;
    int numCols;
    int setScale(float scaleX, float scaleY, float scaleZ);
};

