#pragma once
#include<D3D11.h>
#pragma comment(lib,"D3D11.lib")
#include <fbxsdk.h>
#include "Mesh.h"
#include <vector>
#include <unordered_map>

using namespace std;

class FbxLoader
{
public:
	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector2 uv;
		Vector3 binormal;
		Vector3 tangent;

		/*Vertex(Vector3 position, Vector3 normal, Vector2 uv, Vector3 binormal, Vector3 tangent) :
			position(position), normal(normal), uv(uv), binormal(binormal), tangent(tangent) {};*/
		//Vertex(const Vertex&) {};

		bool operator==(const Vertex& other) const
		{
			return position == other.position &&
				normal == other.normal &&
				uv == other.uv &&
				binormal == other.binormal &&
				tangent == other.tangent;
		}
	};

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	//std::unordered_map<Vertex, unsigned int> indexMapping;

	

public:
	Vector3 * positions = nullptr;
	ID3D11Buffer * m_vertexBuffer, *m_indexBuffer;
public:
	bool Initialize(ID3D11Device* device, WCHAR* textureFileName, char* modelFileName)
	{
		FbxManager* manager = nullptr;

		manager = FbxManager::Create();

		FbxIOSettings * ios = FbxIOSettings::Create(manager, IOSROOT);
		manager->SetIOSettings(ios);

		FbxImporter * importer = FbxImporter::Create(manager, "");

		bool status = importer->Initialize(modelFileName, -1, manager->GetIOSettings());
		if (!status)
		{
			printf("Not Find Fbx %s", modelFileName);
			return false;
		}


		FbxScene * scene = FbxScene::Create(manager, "Scene");

		importer->Import(scene);



		// 좌표축을 가져온다. 
		FbxAxisSystem sceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();
		// 씬 내의 좌표축을 바꾼다. 
		FbxAxisSystem::MayaYUp.ConvertScene(scene);
		// 씬 내에서 삼각형화 할 수 있는 모든 노드를 삼각형화 시킨다. 
		FbxGeometryConverter geometryConverter(manager);
		geometryConverter.Triangulate(scene, true);
		FbxNode *rootNode = scene->GetRootNode();
		
		LoadNode(rootNode);
	}

	void LoadNode(FbxNode* node)
	{
		printf("%s \n", node->GetName());
		FbxNodeAttribute *  nodeAttribute = node->GetNodeAttribute();
		if (nodeAttribute)
		{
			if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				FbxMesh* mesh = node->GetMesh();
				ProcessControlPoints(mesh);
				
				// 제어점으로부터 위치 리스트를 채운다. 
				unsigned int triCount = mesh->GetPolygonCount(); // 메쉬의 삼각형 개수를 가져온다. 
				unsigned int vertexCount = 0; // 정점의 개수 
				for (unsigned int i = 0; i < triCount; ++i) // 삼각형의 개수 
				{
					for (unsigned int j = 0; j < 3; ++j) // 삼각형은 세 개의 정점으로 구성 
					{
						int controlPointIndex = mesh->GetPolygonVertex(i, j); // 제어점 인덱스를 가져온다. 
						Vector3& position = positions[controlPointIndex]; // 현재 정점에 대한 위치 

						Vector3 normal = ReadNormal(mesh, controlPointIndex, vertexCount);
						Vector3 binormal = ReadBinormal(mesh, controlPointIndex, vertexCount);
						Vector3 tangent = ReadTangent(mesh, controlPointIndex, vertexCount);
						Vector2 uv = ReadUV(mesh, controlPointIndex, mesh->GetTextureUVIndex(i, j));
						InsertVertex(position, normal, uv, binormal, tangent);

						vertexCount++; // 정점의 개수++ 
					}
				}

			}
		}

		const int childCount = node->GetChildCount();
		for (unsigned int i = 0; i < childCount; ++i)
		{
			printf(" ");
			LoadNode(node->GetChild(i));
		}
	}

	void InsertVertex(const Vector3& position, const Vector3& normal, const Vector2& uv, const Vector3& binormal, const Vector3& tangent)
	{
		Vertex vertex = { position, normal, uv, binormal, tangent }; 
		unsigned int index = vertices.size();
		indices.push_back(index);
		vertices.push_back(vertex);
		/*auto lookup = indexMapping.find(vertex); 
		if (lookup != indexMapping.end()) 
		{ 
			indices.push_back(lookup->second); 
		}
		else { 
			
			indexMapping[vertex] = index;
			
		}
*/
	}

	void ProcessControlPoints(FbxMesh* mesh)
	{
		unsigned int count = mesh->GetControlPointsCount(); //제어점의 개수
		positions = new Vector3[count];

		for (unsigned int i = 0; i < count; ++i)
		{
			Vector3 position;

			position.x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]);
			position.y = static_cast<float>(mesh->GetControlPointAt(i).mData[1]);
			position.z = static_cast<float>(mesh->GetControlPointAt(i).mData[2]);
		}
	}

	Vector3 ReadNormal(const FbxMesh* mesh, int controlPointIndex, int vertexCounter)
	{
		if (mesh->GetElementNormalCount() < 1)
		{
			//printf("No normals!");
			return Vector3::zero;
		}

		const FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);
		Vector3 result;

		switch (vertexNormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(controlPointIndex).mData[2]);
				break;
			case FbxGeometryElement::eIndexToDirect:
				int index = vertexNormal->GetIndexArray().GetAt(controlPointIndex);
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
				break;
			}
			break;
		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
				break;
			case FbxGeometryElement::eIndexToDirect:
				int index = vertexNormal->GetIndexArray().GetAt(vertexCounter);
				result.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
				break;
			}
			break;
		}

		return result;
	}

	Vector3 ReadTangent(FbxMesh * mesh, int controlPointIndex, int vertexCounter)
	{
		if (mesh->GetElementTangentCount() < 1)
		{
			//printf("Invalid Tangent Number");
			return Vector3::zero;
		}

		FbxGeometryElementTangent* vertexTangent = mesh->GetElementTangent(0);

		Vector3 result;
		switch (vertexTangent->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[0]);
				result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[1]);
				result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(controlPointIndex).mData[2]);
				break;
			case FbxGeometryElement::eIndexToDirect:
				int index = vertexTangent->GetIndexArray().GetAt(controlPointIndex);
				result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
				break;
			}
			break;
		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[0]);
				result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[1]);
				result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(vertexCounter).mData[2]);
				break;
			case FbxGeometryElement::eIndexToDirect:
				int index = vertexTangent->GetIndexArray().GetAt(vertexCounter);
				result.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
				break;
			}
			break;
		}
		return result;
	}

	Vector3 ReadBinormal(FbxMesh * mesh, int controlPointIndex, int vertexCounter)
	{
		if (mesh->GetElementBinormalCount() < 1)
		{
			//printf("Invalid Binormal Number");
			return Vector3::zero;
		}

		FbxGeometryElementBinormal* vertexBinormal = mesh->GetElementBinormal(0);

		Vector3 result;
		switch (vertexBinormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexBinormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				result.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(controlPointIndex).mData[0]);
				result.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(controlPointIndex).mData[1]);
				result.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(controlPointIndex).mData[2]);
				break;
			case FbxGeometryElement::eIndexToDirect:
				int index = vertexBinormal->GetIndexArray().GetAt(controlPointIndex);
				result.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[2]);
				break;
			}
			break;
		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexBinormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				result.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(vertexCounter).mData[0]);
				result.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(vertexCounter).mData[1]);
				result.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(vertexCounter).mData[2]);
				break;
			case FbxGeometryElement::eIndexToDirect:
				int index = vertexBinormal->GetIndexArray().GetAt(vertexCounter);
				result.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[1]);
				result.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[2]);
				break;
			}
			break;
		}
		return result;
	}

	Vector2 ReadUV(FbxMesh * mesh, int controlPointIndex, int vertexCounter)
	{
		if (mesh->GetElementUVCount() < 1)
		{
			//printf("Invalid UV Number");
			return Vector2::zero;
		}

		FbxGeometryElementUV* vertexUV = mesh->GetElementUV(0);

		Vector2 result;
		switch (vertexUV->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				result.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(controlPointIndex).mData[0]);
				result.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(controlPointIndex).mData[1]);
				break;
			case FbxGeometryElement::eIndexToDirect:
				int index = vertexUV->GetIndexArray().GetAt(controlPointIndex);
				result.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[1]);
				break;
			}
			break;
		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
				result.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(vertexCounter).mData[0]);
				result.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(vertexCounter).mData[1]);
				break;
			case FbxGeometryElement::eIndexToDirect:
				int index = vertexUV->GetIndexArray().GetAt(vertexCounter);
				result.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[0]);
				result.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[1]);
				break;
			}
			break;
		}
		return result;
	}
};