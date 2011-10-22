#include "MeshSurfaceGraphicsComponent.h"

MeshSurfaceGraphicsComponent::~MeshSurfaceGraphicsComponent()
{
    this->vertexBuffer->Release();
    this->indexBuffer->Release();
}

void MeshSurfaceGraphicsComponent::init( GraphicsEngine &graphicsEngine )
{
    initVertexDeclaration(graphicsEngine);
    initVertexBuffer(graphicsEngine);
    initIndexBuffer(graphicsEngine);
}

void MeshSurfaceGraphicsComponent::draw( GameObject &gameObject, GraphicsEngine &graphicsEngine )
{
    // FIXME hardcoded
    float scaleX = 10.0f;
    float scaleY = 10.0f;
    float scaleZ = 10.0f;
    D3DXVECTOR3 position(0.0,0.0,0.0);

    D3DXMATRIX worldMatrix, scalingMatrix, translationMatrix,  rotationMatrix;

    D3DXMatrixScaling(&scalingMatrix, scaleX, scaleY, scaleZ);
    worldMatrix = scalingMatrix;

    // D3DXMatrixTranslation(&translationMatrix, position.x, position.y, position.z);
    // worldMatrix *= translationMatrix;

    graphicsEngine.getDirect3DDevice()->SetTransform(D3DTS_WORLD, &worldMatrix);

    graphicsEngine.getDirect3DDevice()->SetStreamSource( 0, this->vertexBuffer, 0, sizeof(CustomVertex) );
    graphicsEngine.getDirect3DDevice()->SetVertexDeclaration(this->vertexDeclaration);
    graphicsEngine.getDirect3DDevice()->SetIndices(this->indexBuffer);

    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_COLORVERTEX, FALSE);
    // graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    graphicsEngine.getDirect3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    graphicsEngine.getDirect3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->vertices.size(), 0, this->triangleCount);
}

void MeshSurfaceGraphicsComponent::initSurface( int numRows, int numCols, float dx, float dz )
{
    // FIXME hardcoded
    float rangeMax = 10;
    float rangeMin = 0;

    this->vertexCount = numRows * numCols;
    this->xCellDimension = dx;
    this->zCellDimension = dz;

    initVertices(numRows, numCols, xCellDimension, zCellDimension, rangeMin, rangeMax);
    initIndices(numRows, numCols);
}

void MeshSurfaceGraphicsComponent::initVertices( int rows, int columns, float xOffset, float zOffset, float yMin, float yMax )
{
    vertices.resize(rows * columns);

    D3DXVECTOR3 columnPosition(0,0,0);
    D3DXVECTOR3 rowPosition(0,0,0);

    int currentVertex = 0;
    for(int i = 0; i < rows; i++) {
        columnPosition = rowPosition;

        for(int j = 0; j < columns; j++) {
            vertices[currentVertex].position = columnPosition;
            vertices[currentVertex].position.y = (float)((double)rand() / (RAND_MAX+1) * (yMax - yMin) + yMin); // FIXME casting
            
            if (vertices[currentVertex].position.y < yMax / 6.0f) {
                vertices[currentVertex].color = D3DCOLOR_XRGB(10, 50, 10);
            }
            else if (vertices[currentVertex].position.y < 4.0f * yMax / 6.0f) {
                vertices[currentVertex].color = D3DCOLOR_XRGB(50, 128, 50);
            }
            else {
                vertices[currentVertex].color = D3DCOLOR_XRGB(240, 255, 240);
            }

            columnPosition.x += xOffset;
            currentVertex++;
        }

        rowPosition.z += zOffset;
    }
}

void MeshSurfaceGraphicsComponent::initIndices( int rows, int columns )
{
    this->quadCount = (rows-1) * (columns-1);
    this->triangleCount = quadCount * 2;
    indices.resize(triangleCount * 3); // Why times 3? 

    int currentIndex = 0;
    for(int i = 0; i < rows-1; i++) {
        for(int j = 0; j < columns-1; j++)
        {
            indices[currentIndex++] = i * columns + j;
            indices[currentIndex++] = i * columns + j + 1;
            indices[currentIndex++] = (i+1) * columns + j + 1;

            indices[currentIndex++] = i * columns + j;
            indices[currentIndex++] = (i+1) * columns + j + 1;
            indices[currentIndex++] = (i+1) * columns + j;
        }
    }
}

void MeshSurfaceGraphicsComponent::initVertexBuffer( GraphicsEngine &graphicsEngine )
{
    int vertexBufferSize = this->vertices.size() * sizeof(CustomVertex);

    graphicsEngine.getDirect3DDevice()->CreateVertexBuffer(
        vertexBufferSize,
        D3DUSAGE_WRITEONLY,
        NULL,
        D3DPOOL_MANAGED,
        &vertexBuffer,
        NULL
    );

    VOID* pVoid;
    vertexBuffer->Lock(0, 0, static_cast<void**>(&pVoid), 0);
    memcpy(pVoid, &vertices[0], vertexBufferSize);
    vertexBuffer->Unlock();
}

void MeshSurfaceGraphicsComponent::initIndexBuffer( GraphicsEngine &graphicsEngine )
{
    int indexBufferSize = this->indices.size() * sizeof(long);
    graphicsEngine.getDirect3DDevice()->CreateIndexBuffer(
        indexBufferSize,
        D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX32,
        D3DPOOL_MANAGED,
        &this->indexBuffer,
        NULL
    );

    VOID* pVoid;
    indexBuffer->Lock(0, 0, static_cast<void**>(&pVoid), 0);
    memcpy(pVoid, &indices[0], indexBufferSize);
    indexBuffer->Unlock();
}

void MeshSurfaceGraphicsComponent::initVertexDeclaration(GraphicsEngine &graphicsEngine)
{
    CustomVertex meshVertex;
    D3DVERTEXELEMENT9 vertexElement[] = {
        {0, 0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
        {0, 0, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
        D3DDECL_END()
    };
    vertexElement[0].Offset = reinterpret_cast<char*>(&meshVertex.position) - reinterpret_cast<char*>(&meshVertex);
    vertexElement[1].Offset = reinterpret_cast<char*>(&meshVertex.color) - reinterpret_cast<char*>(&meshVertex);
    graphicsEngine.getDirect3DDevice()->CreateVertexDeclaration(vertexElement, &vertexDeclaration);
}
