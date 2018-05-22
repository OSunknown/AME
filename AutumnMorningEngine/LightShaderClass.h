#pragma once

#include <d3d11.h>
#include "Math.h"
#include <d3dx11async.h>
#include <fstream>
#include "Debug.h"
using namespace std;

class LightShaderClass
{
private:
	struct MatrixBufferType
	{
		Matrix4 world;
		Matrix4 view;
		Matrix4 projection;
	};

	struct CameraBufferType
	{
		Vector3 cameraPosition;
		float padding;
	};

	struct LightBufferType
	{
		Vector4  diffuseColor;
		Vector3  lightDirection;
		float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
	};

public:
	LightShaderClass();
	LightShaderClass(const LightShaderClass&);
	~LightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, Matrix4, Matrix4, Matrix4, ID3D11ShaderResourceView*, Vector3, Vector4);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, Matrix4, Matrix4, Matrix4, ID3D11ShaderResourceView*, Vector3, Vector4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader * m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
};

