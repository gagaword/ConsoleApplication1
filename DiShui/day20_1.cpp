#include<iostream>
#include "my_head.h"

#define notepadPath "C:\\Users\\GaGa\\Desktop\\eee.exe"

int main()
{
	// ͨ���ඨ���һ���ļ�
	FILE* file = nullptr;
	openFile(&file, notepadPath, "rb");


	// ��ȡ�ļ���С
	long fileSize = GetFileSize(file);

	// ��ȡ�ļ�����
	unsigned char* result = (unsigned char*)ReadFileData(fileSize,1,file);

	// ʹ����ʱָ��ָ��result�����ı�resultָ���λ�á�
	unsigned char* temp = result;

	// ʹ��memcmp����Ƿ���PE�ļ�
	CheckPE(result);

	free(result);
	return 0;
}