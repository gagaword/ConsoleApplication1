#include<iostream>
#include"day28.h"
#include<Windows.h>

#define filePath "C:\\Users\\GaGa\\Desktop\\jinshan2007_CrackMe\\CrackMe.exe"
#define DllName "Dll1.dll"
#define FuncName "ExportFunction"

// ��ʽ����
//extern "C" __declspec(dllexport) void ExportFunction();

// ��������ָ��
typedef void (*LPTest)();

int main()
{
	MovImportAndInjectionDll(filePath, DllName, FuncName);

	//ExportFunction();
	//LPTest function;
	//// ����dll
	//HMODULE dllAddress = LoadLibrary(L"D:\\Repos\\gagaword\\MyProject\\DiShui\\dll\\Dll1.dll");
	//if (dllAddress == 0)	return 0;
	//// ��ȡ������ַ
	//function = (LPTest)GetProcAddress(dllAddress, "ExportFunction");
	//// ���ú���
	//function();
	//// �ͷ�dll
	//FreeLibrary(dllAddress);
	return 0;
}