#pragma once
#include<D3D11.h>
#pragma comment(lib,"D3D11.lib")
#include <fstream>
using namespace std;
#include "Math.h"
#include "textureClass.h"
#include "Debug.h"


class ModelClass
{
private:
	struct VertexType
	{
		Vector3 position;
		Vector2 texture;
		Vector3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, WCHAR*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	
	ID3D11ShaderResourceView* GetTexture();
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();
private:
	ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_Texture;

	ModelType* m_model;
};

