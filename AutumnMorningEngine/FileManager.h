#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <string>
#include <map>
#include <stdlib.h>
#include <iostream>
#include "FbxLoader.h"
using namespace std;
struct FolderData
{
	string path;
	string parentsPath;
	map <int, int> types;
	map <int, string> mChildPath;
};

struct ModelData
{
	string path;
	string AllPath;
	int type;
};

class FileManager
{
public:
	map<string, FolderData> folders;
	map<string, ModelData> Fbxs;
	map<string, ModelData> Objs;
	char * AssetsRoot;
	char * AllFIle;
	char * SelectFolderPath;
private:
	
	FileManager()
	{
		AssetsRoot = ".\\Assets\\";
		AllFIle = "*.*";
	}
	~FileManager()
	{
		if (NULL != SelectFolderPath)
		{
			delete SelectFolderPath;
			SelectFolderPath = 0;
		}
		if (NULL != AssetsRoot)
		{
			delete AssetsRoot;
			AssetsRoot = 0;
		}
		if (NULL != AllFIle)
		{
			delete AllFIle;
			AllFIle = 0;
		}
		
	}
public:
	static FileManager* Getsingleton()
	{
		static FileManager* instance_ = new FileManager();
		return instance_;
	}
	void initialize()
	{
		FindFolder(".\\Assets", ".\\Assets");
		SetSeletPath(".\\Assets");
	}
	void FindFolder(const char * path, const char* parents)
	{
		FolderData folder;
		_finddata_t fd;
		long handle;
		int result = 1;
		char FilePath[_MAX_PATH] = "";
		sprintf(FilePath, "%s\\%s", path, AllFIle);
		folder.path = path;
		folder.parentsPath = parents;
		handle = _findfirst(FilePath, &fd);
		if (handle == -1)
		{
			printf("There were no files.\n");
			return;
		}

		// . 과 .. 파일을 넘어가기위해서 
		result = _findnext(handle, &fd);
		result = _findnext(handle, &fd);
		int Count = 0;
		while (result != -1)
		{
			char cFilePath[_MAX_PATH] = "";
			sprintf(cFilePath, "%s\\%s", path, fd.name);
			folder.types.insert(make_pair(Count,isFileOrDir(cFilePath)));
			folder.mChildPath.insert(make_pair(Count, fd.name));
			Count++;
			result = _findnext(handle, &fd);
		}
		folders.insert(make_pair(path, folder));
		
		_findclose(handle);
		for (auto it = folder.mChildPath.begin(); it != folder.mChildPath.end(); it++) {
			//cout << "type : " << folder.types[it->first] << " " << "value : " << it->second << '\n';
			if (folder.types[it->first] == 0)
			{
				char cFilePath[_MAX_PATH] = "";
				sprintf(cFilePath, "%s\\%s", path, it->second.c_str());
				FindFolder(cFilePath,path);
				//printf("\n");
			}

			if (folder.types[it->first] == 1)
			{

			}
		}
	}

	//void FindFiles(char * centerPath)
	//{
	//	_finddata_t fd;
	//	long handle;
	//	int result = 1;
	//	
	//	char FilePath[_MAX_PATH] = "", *AllFilePath = "";
	//	size_t my_len = strlen(centerPath);
	//	if (my_len > 0)
	//	{
	//		sprintf(FilePath, "%s\\%s", centerPath, AllFIle);
	//	}
	//	else
	//	{
	//		sprintf(FilePath, "%s%s", AssetsRoot, AllFIle);
	//	}
	//	
	//	handle = _findfirst(FilePath, &fd);  //현재 Path 내 모든 파일을 찾는다.

	//	if (handle == -1)
	//	{
	//		printf("There were no files.\n");
	//		return;
	//	}
	//	char cFilePath[_MAX_PATH] = "";
	//	// . 과 .. 파일을 넘어가기위해서 
	//	result = _findnext(handle, &fd);
	//	result = _findnext(handle, &fd);
	//	while (result != -1)
	//	{
	//		if (my_len > 0)
	//		{
	//			sprintf(cFilePath, "%s\\%s", centerPath, fd.name);
	//		}
	//		else
	//		{
	//			sprintf(cFilePath, "%s%s", AssetsRoot, fd.name);
	//		}

	//		//int c = isFileOrDir(cFilePath);
	//		////printf("%s\n", cFilePath);
	//		////CoreManager::Getsingleton()->AddContextItem(fd.name, c);
	//		//switch (c)
	//		//{
	//		//case 0:
	//		//	printf("{\n");
	//		//	FindFiles(cFilePath);
	//		//	printf("}\n");
	//		//	break;
	//		//case 1:
	//		//	printf("OBJ \n");
	//		//	break;
	//		//case 2:
	//		//	printf("FBX \n");
	//		//	break;
	//		//case 3:
	//		//	printf("txt \n");
	//		//	break;
	//		//case 4:
	//		//	printf("Just File \n");
	//		//	break;
	//		//}
	//		result = _findnext(handle, &fd);
	//	}
	//	_findclose(handle);
	//}

	int isFileOrDir(char * s)
	{
		_finddatai64_t c_file;
		intptr_t hFile;
		int result;
		char  drive[_MAX_PATH];
		char  dir[_MAX_PATH];
		char  fname[_MAX_PATH];
		char  ext[_MAX_PATH];
		char fullpath[_MAX_PATH];
		_fullpath(fullpath, s, _MAX_PATH);

		if ((hFile = _findfirsti64(s, &c_file)) == -1L)
			result = -1; // 파일 또는 디렉토리가 없으면 -1 반환
		else
			if (c_file.attrib & _A_SUBDIR)
			{
				result = 0; // 디렉토리면 0 반환
			}
			else
			{
				_splitpath(fullpath, drive, dir, fname, ext);
				string str = ext;

				if (str == ".obj" || str == ".OBJ")
				{
					result = 1;
				}
				else if (str == ".fbx" || str == ".FBX")
				{
					result = 2;
				}
				else if (str == ".txt")
				{
					result = 3;
				}
				else if (str == "")
				{
					result = 4;
				}
				else
				{
					// 그밖의 경우는 "존재하는 파일"이기에 1 반환
					// 이미지 만들기 전이니까 그냥 1.. 
					result = 1;
				}
			}
		_findclose(hFile);
		return result;
	}

	void ChangePath(const char * folder)
	{
		char* copyPath;
		copyPath = new char[strlen(SelectFolderPath) + 1];
		strcpy(copyPath, SelectFolderPath);
		char * copyfolder;
		copyfolder = new char[strlen(folder) + 1];
		strcpy(copyfolder, folder);
		SelectFolderPath = new char[strlen(SelectFolderPath) + strlen(folder) + 2];
		sprintf(SelectFolderPath, "%s\\%s", copyPath, copyfolder);
		printf("%s", SelectFolderPath);
	}

	void SetSeletPath(const char * path)
	{
		char* copyPath;
		copyPath = new char[strlen(path) + 1];
		strcpy(copyPath, path);
		SelectFolderPath = copyPath;
	}

	FolderData GetSeletFolder()
	{
		return folders[SelectFolderPath];
	}
};