#include<iostream>
#include"day28.h"

// ��ʽ����
extern "C" __declspec(dllexport) void ExportFunction();
int main()
{
	ExportFunction();
	return 0;
}