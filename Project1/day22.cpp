#include "day22.h"
#include<string.h>

#define DEBUG 1
#define LOG(FUN_NAME,VALUES) if ((DEBUG) == 1){std::cout << FUN_NAME << "---->" << std::hex << VALUES << std::endl;}
#define IMAGE_SIZEOF_Signature 0x4
DWORD ReadFile(IN const char* FilePath, OUT LPVOID* FileData)
{
	if (FilePath == NULL)
	{
		std::cout << "��������" << std::endl;
		return 0;
	}
	// ���ļ�
	FILE* pFile = NULL;
	errno_t FopenResult = fopen_s(&pFile, FilePath,"rb");
	if (FopenResult != 0)
	{
		std::cout << "���ļ�ʧ��" << std::endl;
		return 0;
	}

	// ��ȡ�ļ���С
	fseek(pFile, 0, SEEK_END);
	long FileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	LOG(__func__, pFile);

	// �����ڴ�ռ�
	*FileData = malloc(FileSize);
	if (*FileData == NULL)
	{
		std::cout << "�ڴ�������" << std::endl;
		fclose(pFile);
		return 0;
	}
	memset(*FileData, 0, FileSize);

	// ��ȡ�ļ�����
	size_t FreadResult = fread_s(*FileData, FileSize, 1 ,FileSize, pFile);
	if (FreadResult != FileSize)
	{
		std::cout << "��ȡ����" << std::endl;
		fclose(pFile);
		free(*FileData);
		return 0;
	}
	LOG(__func__, FreadResult);
	fclose(pFile);
	return FreadResult;
}


DWORD CopyFileBufferToImageBuffer(IN LPVOID FileBuffer, OUT LPVOID* ImageBuffer)
{
	// ��ȡImageBuffer�� PE ��Ҫ���ֶ�
	PIMAGE_DOS_HEADER pDOS = NULL;
	PIMAGE_NT_HEADERS32 pNT = NULL;
	PIMAGE_FILE_HEADER pFILE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOPTIONAL = NULL;
	PIMAGE_SECTION_HEADER pSECTION = NULL;

	// DOSͷ
	pDOS = (PIMAGE_DOS_HEADER)FileBuffer;
	LOG(__func__, pDOS->e_magic);

	// ����ImageBuffer�ռ�
	// ImageBuffer�Ŀռ��С��OPTIONAL.SizeOfImage�ֶ�
	pOPTIONAL = (PIMAGE_OPTIONAL_HEADER32)((DWORD)FileBuffer + pDOS->e_lfanew + IMAGE_SIZEOF_FILE_HEADER + IMAGE_SIZEOF_Signature);

	// ������Ϣ
	printf("SizeOfImage--->%#x\n", pOPTIONAL->SizeOfImage);

	*ImageBuffer = malloc(pOPTIONAL->SizeOfImage);
	if (*ImageBuffer == NULL)
	{
		std::cout << "�ڴ�������" << std::endl;
		return 0;
	}

	memset(*ImageBuffer, 0, pOPTIONAL->SizeOfImage);

	// ����DOS,PE,�ڵ�ImageBuffer,��Щ�������ļ�����ʲô����ImageBuffer�о���ʲô����
	// OPTIONAL�е� SizeOfHeaders �ֶξ�����Щ���ݵĴ�С��
	for (int i = 0; i < pOPTIONAL->SizeOfHeaders; i++)
	{
		*((unsigned char*)*ImageBuffer + i) = *((unsigned char*)FileBuffer + i);
	}

	// ������Ϣ
	for (int i = 0; i < 0x28; i++)
	{
		printf("%02x ", *((unsigned char*)*ImageBuffer + i));
	}

	printf("\n");
	// ͨ���ڱ��е�VisualAddress�ֶμ���ýڱ����ڴ��е�ƫ�ƣ����и��ƣ����ƴ�СΪSizeOfRawData��
	// �׽ڱ�λ��
	pNT = (PIMAGE_NT_HEADERS32)((BYTE*)FileBuffer + pDOS->e_lfanew);
	pFILE = &pNT->FileHeader;
	pOPTIONAL = &pNT->OptionalHeader;
	pSECTION = (PIMAGE_SECTION_HEADER)((BYTE*)pOPTIONAL + pFILE->SizeOfOptionalHeader);

	// ���ƽڵ�ImageBase
	for (int i = 0; i < pFILE->NumberOfSections; i++)
	{
		printf("���ļ�ƫ��---->%x\n", pSECTION[i].PointerToRawData);
		if (pSECTION[i].PointerToRawData == 0)
		{			
			continue;
		}
		for (int j = 0; j < pSECTION[i].SizeOfRawData; j++)
		{
			// ������������
			*((unsigned char*)*ImageBuffer + pSECTION[i].VirtualAddress + j) = *((unsigned char*)FileBuffer + pSECTION[i].PointerToRawData + j);
		}
	}

	// ������Ϣ
	/*for (int j = 0; j < pSECTION[2].SizeOfRawData; j++)
	{
		*((unsigned char*)*ImageBuffer + pSECTION[2].VirtualAddress + j) = *((unsigned char*)FileBuffer + pSECTION[2].PointerToRawData + j);
		printf("%02x  ", *((unsigned char*)*ImageBuffer + pSECTION[2].VirtualAddress + j));
	}*/
	
	return 0;
}
