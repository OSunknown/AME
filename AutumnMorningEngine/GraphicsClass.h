#pragma once 

//////////////
// INCLUDES //
//////////////
#include <Windows.h>
#include "D3DClass.h"
#include "Cameraclass.h"
#include "ModelClass.h"
#include "TextClass.h"
#include "TextureShaderClass.h"
#include "LightClass.h"
#include "LightShaderClass.h"
#include "ModelListClass.h"
#include "FrustumClass.h"
#include "Debug.h"
#include "Math.h"
#include "FbxLoader.h"
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float);
	bool Render();
private:
	D3DClass * m_D3D;
	CameraClass* m_Camera;
	TextClass* m_Text;
	ModelClass* m_Model;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	ModelListClass* m_ModelList;
	FrustumClass* m_Frustum;
	FbxLoader *fbxloader;
};

