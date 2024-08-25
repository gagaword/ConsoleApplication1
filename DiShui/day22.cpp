#include "day22.h"
#include<string.h>

DWORD ReadFile22(IN LPCSTR FilePath, OUT LPVOID* FileData)
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

	if (FileBuffer == NULL)
	{
		return 0;
	}
	
	// ���� FileBuffer PE �ֶ�
	PIMAGE_DOS_HEADER pDOS = (PIMAGE_DOS_HEADER)FileBuffer;
	if (pDOS->e_magic != IMAGE_DOS_SIGNATURE) {
		std::cerr << "��Ч�� DOS ǩ��" << std::endl;
		return 0;
	}

	PIMAGE_NT_HEADERS32 pNT = (PIMAGE_NT_HEADERS32)((BYTE*)FileBuffer + pDOS->e_lfanew);
	if (pNT->Signature != IMAGE_NT_SIGNATURE) {
		std::cerr << "��Ч�� NT ǩ��" << std::endl;
		return 0;
	}

	PIMAGE_OPTIONAL_HEADER32 pOPTIONAL = &pNT->OptionalHeader;
	PIMAGE_FILE_HEADER pFILE = &pNT->FileHeader;
	PIMAGE_SECTION_HEADER pSECTION = (PIMAGE_SECTION_HEADER)((BYTE*)pOPTIONAL + pFILE->SizeOfOptionalHeader);

	// ���� ImageBuffer �ռ�
	*ImageBuffer = malloc(pOPTIONAL->SizeOfImage);
	if (*ImageBuffer == NULL) {
		std::cerr << "�ڴ�������" << std::endl;
		return 0;
	}

	// ��� ImageBuffer
	memset(*ImageBuffer, 0, pOPTIONAL->SizeOfImage);

	// ���� DOS ͷ�� PE ͷ�� ImageBuffer
	memcpy(*ImageBuffer, FileBuffer, pOPTIONAL->SizeOfHeaders);
	uint64_t CopyData = pOPTIONAL->SizeOfHeaders;

	// ���ƽڵ� ImageBuffer
	for (int i = 0; i < pFILE->NumberOfSections; i++) {
		if (pSECTION[i].SizeOfRawData == 0) {
			continue;
		}

		void* dest = (BYTE*)*ImageBuffer + pSECTION[i].VirtualAddress;
		void* src = (BYTE*)FileBuffer + pSECTION[i].PointerToRawData;

		memcpy(dest, src, pSECTION[i].SizeOfRawData);
		CopyData += pSECTION[i].SizeOfRawData;
	}

	return CopyData;
}

DWORD CopyImageBufferToNewBuffer(IN LPVOID ImageBuffer, OUT LPVOID* NewBuffer)
{
	// ע��NewBuffer��ָ�����ͣ����ݵĲ�����NewBufferָ�������
	// Ҫ�������������Ҫ��NewBuffer���н����á�
	// �����ж�
	if (ImageBuffer == NULL)
	{
		std::cout << "��������" << std::endl;
		return 0;
	}

	// ���� ImageBuffer �� PE�ֶ�
	PIMAGE_DOS_HEADER pDOS = NULL;
	PIMAGE_NT_HEADERS32 pNT = NULL;
	PIMAGE_FILE_HEADER pFILE = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOPTIONAL = NULL;
	PIMAGE_SECTION_HEADER pSECTION = NULL;

	// DOSͷ
	pDOS = (PIMAGE_DOS_HEADER)ImageBuffer;
	// NTͷ
	pNT = (PIMAGE_NT_HEADERS32)((BYTE*)ImageBuffer + pDOS->e_lfanew);
	// PEͷ
	pFILE = &pNT->FileHeader;
	// ��չPEͷ
	pOPTIONAL = &pNT->OptionalHeader;
	// �ڱ�
	pSECTION = (PIMAGE_SECTION_HEADER)((BYTE*)pOPTIONAL + pFILE->SizeOfOptionalHeader);


	// ImageBuffer��ͨ���ļ���������������
	// �ڰ��������Ż�ȥ����NweBuffer������
	// ͨ���ڱ�ṹ�ֶν�������
	// �����ļ���С�ֽڸ�NewBuffer
	// ����DOS + PE + �ڱ�NewBuffer

	
	// NewBuffer����ռ�
	// ����ռ���ѿռ��׵�ַ��*NewBuffer������*NewBuffer������ǿռ�ĵ�ַ����Ҫ�ٴν�����ȡֵ��
	*NewBuffer = malloc(pOPTIONAL->SizeOfHeaders + pOPTIONAL->SizeOfImage);
	if (*NewBuffer == NULL)
	{
		std::cout << "�ڴ�������" << std::endl;
		return 0;
	}
	memset(*NewBuffer, 0, pOPTIONAL->SizeOfHeaders + pOPTIONAL->SizeOfImage);

	std::cout << std::hex << pSECTION->Misc.VirtualSize << std::endl;
	
	// ����Headers��NewBuffer�����ƴ�СSizeOfHeaders
	/*for (size_t i = 0; i < pOPTIONAL->SizeOfHeaders; i++)
	{
		*((char*)*NewBuffer + i) = *((char*)ImageBuffer + i);
	}*/
	memcpy(*NewBuffer, ImageBuffer, pOPTIONAL->SizeOfHeaders);
	uint64_t CopyData = pOPTIONAL->SizeOfHeaders;

	// ���ƽڵ�NewBuffer�����ƴ�СΪSizeOfRawData, �ļ�ƫ��ΪPointerToRawData,����ΪFILE->NumberOfSections.
	// �ڴ�ƫ��Ϊ VirtualAddress
	for (int i = 0; i < pFILE->NumberOfSections; i++)
	{
		if (pSECTION[i].PointerToRawData == 0)
		{
			continue;
		}

		void* dest = (BYTE*)*NewBuffer + pSECTION[i].PointerToRawData;
		void* src = (BYTE*)ImageBuffer + pSECTION[i].VirtualAddress;
		memcpy(dest, src, pSECTION[i].Misc.VirtualSize);
		CopyData += pSECTION[i].SizeOfRawData;
		/*for (int j = 0; j < pSECTION[i].SizeOfRawData; j++)
		{
			*((unsigned char*)*NewBuffer + pSECTION[i].PointerToRawData + j) = *((unsigned char*)ImageBuffer + pSECTION[i].VirtualAddress + j);
		}*/
	}

	// ������Ϣ
	if (DEBUG == 1)
	{
		for (int j = 0; j < pSECTION[1].SizeOfRawData; j++)
		{
			printf("%02x  ", *((unsigned char*)*NewBuffer + pSECTION[1].PointerToRawData + j));
		}
	}
	return CopyData;
}

DWORD MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile)
{
	
	FILE* pFile = NULL;
	fopen_s(&pFile, lpszFile, "wb");
	if (pFile == NULL)
	{
		std::cout << "д���ļ�ʧ��" << std::endl;
		return 0;
	}
	size_t result = fwrite((unsigned char*)pMemBuffer, 1, size, pFile);
	if (result == size)
	{
		return result;
	}
	return 0;
}

DWORD RvaTOFileOffset(IN LPVOID FileBuffer, IN DWORD dwRva)
{
	// ��ȡ PE �ṹ������Ϣ
	PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)FileBuffer;
	PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)((BYTE*)FileBuffer + pDOSHeader->e_lfanew);

	// ԭ������������ȡ���ڱ�ͷ�����ˣ�ԭ��΢���ṩ�˰���
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNTHeaders);
	DWORD sectionCount = pNTHeaders->FileHeader.NumberOfSections;
	DWORD FileOffset = 0;

	for (size_t i = 0; i < sectionCount; i++)
	{
		if (pSectionHeader[i].PointerToRawData == 0)
		{
			continue;
		}
		if ((pSectionHeader[i].VirtualAddress) <= dwRva && (pSectionHeader[i].VirtualAddress + pSectionHeader[i].Misc.VirtualSize) >= dwRva)
		{
			FileOffset = ((dwRva - pSectionHeader[i].VirtualAddress) + pSectionHeader[i].PointerToRawData);
			return FileOffset;
		}
	}
	return 0;
}
