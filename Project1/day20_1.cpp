#include<iostream>
#include "my_head.h"

#define notepadPath "C:\\Users\\GaGa\\Desktop\\eee.exe"

const char PE[] = {
	0x4D,0x5A
};

int main()
{
	// ͨ���ඨ���һ���ļ�
	FILE* file = nullptr;
	openFile(&file, notepadPath, "rb");
	std::cout << file << std::endl;

	// ��ȡ�ļ���С
	long fileSize = GetFileSize(file);
	std::cout << fileSize << std::endl;

	// ��ȡ�ļ�����
	unsigned char* result = (unsigned char*)ReadFileData(fileSize,1,file);

	// ʹ����ʱָ��ָ��result�����ı�resultָ���λ�á�
	unsigned char* temp = result;

	// ʹ��memcmp����Ƿ���PE�ļ�
	if (memcmp(result, PE, sizeof(PE)) == 0) {
		std::cout << "��PE�ļ�" << std::endl;
	}
	else {
		std::cout << "����PE�ļ�" << std::endl;
	}

	free(result);
	return 0;
}