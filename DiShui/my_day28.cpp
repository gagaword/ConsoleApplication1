#include<iostream>
#include"day28.h"
#include<Windows.h>
// ��ʽ����
//extern "C" __declspec(dllexport) void ExportFunction();

typedef void (*LPTest)();
int main()
{
	//ExportFunction();
	LPTest function;

	// ����dll
	HMODULE dllAddress = LoadLibrary(L"D:\\Repos\\gagaword\\MyProject\\DiShui\\dll\\Dll1.dll");

	// ��ȡ������ַ
	function = (LPTest)GetProcAddress(dllAddress, "ExportFunction");

	// ���ú���
	function();

	// �ͷ�dll
	FreeLibrary(dllAddress);
	return 0;
}