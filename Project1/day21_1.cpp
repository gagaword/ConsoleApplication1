#include<iostream>
#include<Windows.h>
#include<string.h>
#include "my_head.h"

#define FilePath "C:\\Users\\GaGa\\Desktop\\A.exe"
#define VOID void


LPVOID readfile(const char* filepath)
{
	unsigned char* FileData = (unsigned char*)ReadFile(filepath);
	if (!FileData)
	{
		std::cout << "��ȡ��������" << std::endl;
		return NULL;
	}
	else
	{
		std::cout << "��ȡ�ɹ�" << std::endl;
		return FileData;
	}
}

VOID PrintfSECTION()
{
	LPVOID pFileBuffer = NULL;

	PIMAGE_DOS_HEADER pPIMAGE_DOS = nullptr;
	PIMAGE_NT_HEADERS32 pIMAGE_NT = nullptr;
	PIMAGE_FILE_HEADER pIMAGE_FILE = nullptr;
	PIMAGE_OPTIONAL_HEADER32 pIMAGE_OPTIONAL = nullptr;
	PIMAGE_SECTION_HEADER pSECTION = nullptr;

	// ��ȡ�ļ�
	pFileBuffer = readfile(FilePath);

	// �ж�MZͷ
	pPIMAGE_DOS = (PIMAGE_DOS_HEADER)pFileBuffer;
	if (*((PWORD)pPIMAGE_DOS) == IMAGE_DOS_SIGNATURE)
	{
		std::cout << "��MZͷ" << std::endl;
	}

	// �ж�PEͷ
	pIMAGE_NT = (PIMAGE_NT_HEADERS32)((DWORD)pFileBuffer + pPIMAGE_DOS->e_lfanew);

	if (*(PWORD)(pIMAGE_NT) == IMAGE_NT_SIGNATURE)
	{
		std::cout << "��PEͷ" << std::endl;
	}
	
	// �ڱ�
	pIMAGE_FILE = &pIMAGE_NT->FileHeader;
	// ��ѡͷ��ƫ�����ǽ������ļ�ͷ֮���
	pIMAGE_OPTIONAL = &pIMAGE_NT->OptionalHeader;
	printf("%p\n", pIMAGE_OPTIONAL);

	// �ڱ�����ڿ�ѡͷ֮��
	pSECTION = (PIMAGE_SECTION_HEADER)((BYTE*)pIMAGE_OPTIONAL + pIMAGE_FILE->SizeOfOptionalHeader);

	unsigned char SECTION_NAME[9] = { 0 };

	// �����ڱ�����
	for (int i = 0; i < pIMAGE_FILE->NumberOfSections; i++)
	{
		// ʹ��strncpy_s���ƽ����Ʋ�ȷ����null��β
		// _TRUNCATE ((size_t)-1)
		strncpy_s((char*)SECTION_NAME, sizeof(SECTION_NAME), (const char*)pSECTION[i].Name, _TRUNCATE);
		std::cout << SECTION_NAME << std::endl;
		//printf("Section Name: %s\n", SECTION_NAME);
	}

	printf("****************************Misc.VirtualSize******************************************\n");
	// ��ӡ��ͷ��Misc�ֶΣ��ڴ��д�С
	for (int i = 0; i < pIMAGE_FILE->NumberOfSections; i++) {
		// ͨ�����������Misc�ֶ�
		// Misc��һ�������壬����ͨ����ͬ�ĳ�Ա��������Ϣ
		printf("%08x\n", pSECTION[i].Misc.VirtualSize);

		//std::cout << "Misc: " << std::hex <<  pSECTION[i].Misc.VirtualSize << std::endl;
	}
	printf("*****************************SizeOfRawData********************************************\n");

	// ��ӡ���ļ��д�С
	for (int i = 0; i < pIMAGE_FILE->NumberOfSections; i++) {
		// ͨ�����������Misc�ֶ�
		// Misc��һ�������壬����ͨ����ͬ�ĳ�Ա��������Ϣ
		printf("%08x\n", pSECTION[i].SizeOfRawData);
		//std::cout << "SizeOfRawData: " << std::hex << pSECTION[i].SizeOfRawData << std::endl;
	}
	printf("******************************PointerToRawData****************************************\n");

	// ��ӡ���ļ���ƫ��
	for (int i = 0; i < pIMAGE_FILE->NumberOfSections; i++) {
		// ͨ�����������Misc�ֶ�
		// Misc��һ�������壬����ͨ����ͬ�ĳ�Ա��������Ϣ
		printf("%08x\n", pSECTION[i].PointerToRawData);
		//std::cout << "PointerToRawData: " << std::hex << pSECTION[i].PointerToRawData << std::endl;
	}
	printf("*******************************Characteristics****************************************\n");

	// ��ӡ������
	for (int i = 0; i < pIMAGE_FILE->NumberOfSections; i++) {
		// ͨ�����������Misc�ֶ�
		// Misc��һ�������壬����ͨ����ͬ�ĳ�Ա��������Ϣ
		std::cout << std::hex << pSECTION[i].Characteristics << std::endl;
	}
	// �׽ڱ�+IMAGE_SIZEOF_SECTION_HEADER������һ���ڱ�
	/*pSECTION = (PIMAGE_SECTION_HEADER)((BYTE*)pSECTION + IMAGE_SIZEOF_SECTION_HEADER);
	printf("%s\n", pSECTION->Name);*/

}
int main()
{
	PrintfSECTION();
	return 0;
}