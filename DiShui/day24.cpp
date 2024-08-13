#include<iostream>
#include<Windows.h>
#include "dll/DLLTest.h"
#include "Lib/framework.h"

//extern "C" __declspec(dllimport) int __stdcall add(int x, int y);

typedef int(__stdcall* pAdd)(int, int);

int main()
{
	// ��ʽ����
	//printf("%d\n", add(1, 3));
	
	// ��ʽ����
	HINSTANCE hMoudle = LoadLibrary(L"Dll1.dll");
	printf("%p\n", hMoudle);

	if (hMoudle == NULL)
	{
		std::cout << "����" << std::endl;
		return 0;
	}

	pAdd padd = (pAdd)GetProcAddress(hMoudle, "_add@8");

	if (padd == nullptr)
	{
		std::cout << padd << std::endl;
		return 0;
	}

	printf("%p\n", padd);
	printf("%d\n", padd(2, 1));

	return 0;
}