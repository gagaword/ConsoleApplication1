#include "day22.h"
#include<string.h>


/// <summary>
/// �÷�����ȡһ���ļ�������
/// </summary>
/// <param name="FilePath">�ļ���·��</param>
/// <param name="FileBuffer">�����ļ����ݵ�ָ���ָ��</param>
/// <returns>
/// ����0��ʾ��ȡʧ�ܣ������ֽڱ�ʾ��ȡ�ɹ���
/// </returns>
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

/// <summary>
/// �÷�������FileBufer��ImageBuffer��
/// </summary>
/// <param name="FileBuffer">FileBufferָ��</param>
/// <param name="ImageBuffer">ImageBufferָ��</param>
/// <returns>
/// ����0��ʾʧ�ܣ����򷵻ظ��ƵĴ�С
/// </returns>
//DWORD CopyFileBufferToImageBuffer(IN LPVOID FileBuffer, OUT LPVOID* ImageBuffer)
//{
//
//	 ���� FileBuffer PE �ֶ�
//	PIMAGE_DOS_HEADER pDOS = NULL;
//	PIMAGE_NT_HEADERS32 pNT = NULL;
//	PIMAGE_FILE_HEADER pFILE = NULL;
//	PIMAGE_OPTIONAL_HEADER32 pOPTIONAL = NULL;
//	PIMAGE_SECTION_HEADER pSECTION = NULL;
//
//	 DOSͷ
//	pDOS = (PIMAGE_DOS_HEADER)FileBuffer;
//	LOG(__func__, pDOS->e_magic);
//
//	 ���Ƶ����ݴ�С
//	uint64_t CopyDataSize = 0;
//
//	 ����ImageBuffer�ռ�
//	 ImageBuffer�Ŀռ��С��OPTIONAL.SizeOfImage�ֶ�
//	pOPTIONAL = (PIMAGE_OPTIONAL_HEADER32)((DWORD)FileBuffer + pDOS->e_lfanew + IMAGE_SIZEOF_FILE_HEADER + IMAGE_SIZEOF_Signature);
//
//	 ������Ϣ
//	LOG(__func__, pOPTIONAL->SizeOfImage);
//
//	*ImageBuffer = malloc(pOPTIONAL->SizeOfImage);
//	if (*ImageBuffer == NULL)
//	{
//		std::cout << "�ڴ�������" << std::endl;
//		return 0;
//	}
//
//	memset(*ImageBuffer, 0, pOPTIONAL->SizeOfImage);
//	 ����DOS,PE,�ڵ�ImageBuffer,��Щ�������ļ�����ʲô����ImageBuffer�о���ʲô����
//	 OPTIONAL�е� SizeOfHeaders �ֶξ�����Щ���ݵĴ�С��
//	for (int i = 0; i < pOPTIONAL->SizeOfHeaders; i++)
//	{
//		*((unsigned char*)*ImageBuffer + i) = *((unsigned char*)FileBuffer + i);
//	}
//	
//	if (DEBUG == 1)
//	{
//		// ������Ϣ
//		for (int i = 0; i < 0x28; i++)
//		{
//			printf("%02x ", *((unsigned char*)*ImageBuffer + i));
//		}
//	}
//	
//
//	printf("\n");
//	 ͨ���ڱ��е�VisualAddress�ֶμ���ýڱ����ڴ��е�ƫ�ƣ����и��ƣ����ƴ�СΪSizeOfRawData��
//	 �׽ڱ�λ��
//	pNT = (PIMAGE_NT_HEADERS32)((BYTE*)FileBuffer + pDOS->e_lfanew);
//	pFILE = &pNT->FileHeader;
//	pOPTIONAL = &pNT->OptionalHeader;
//	pSECTION = (PIMAGE_SECTION_HEADER)((BYTE*)pOPTIONAL + pFILE->SizeOfOptionalHeader);
//
//	 ��ʱ����
//	unsigned char* PIMAGE = (unsigned char*)*(ImageBuffer);
//	unsigned char* PFILE = (unsigned char*)FileBuffer;
//
//	 ���ƽڵ�ImageBase
//	for (int i = 0; i < pFILE->NumberOfSections; i++)
//	{
//		printf("���ļ�ƫ��---->%x\n", pSECTION[i].PointerToRawData);
//		printf("���ڴ�ƫ��---->%x\n", pSECTION[i].VirtualAddress);
//		CopyDataSize += pSECTION[i].SizeOfRawData;
//		if (pSECTION[i].PointerToRawData == 0)
//		{			
//			continue;
//		}
//	
//		for (int j = 0; j < pSECTION[i].SizeOfRawData; j++)
//		{
//			/* ����д������ʵ��һ�֣�ֻ����ȡ��һЩ����ʹ���׶�*/
//			*(PIMAGE + pSECTION[i].VirtualAddress + j) = *(PFILE + pSECTION[i].PointerToRawData + j);
//			*((unsigned char*)*ImageBuffer + pSECTION[i].VirtualAddress + j) = *((unsigned char*)FileBuffer + pSECTION[i].PointerToRawData + j);
//		}
//	}
//
//	if (DEBUG == 1)
//	{
//		// ������Ϣ
//		for (int j = 0; j < pSECTION[1].SizeOfRawData; j++)
//		{
//			printf("%02x  ", *((unsigned char*)*ImageBuffer + pSECTION[1].VirtualAddress + j));
//		}
//	}
//
//	CopyDataSize += pOPTIONAL->SizeOfHeaders;
//	return CopyDataSize;
//}


// ����GPT�Ż�
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


/// <summary>
/// �÷�������ImageBuffer��NewBuffer�У�ʹ��NewBuffer���ݴ����ҿ�����
/// </summary>
/// <param name="ImageBuffer">ImageBufferָ��</param>
/// <param name="NewBuffer">NweBufferָ��</param>
/// <returns>
/// ����0��ʾ����ʧ�ܣ����߷��ظ��ƵĴ�С
/// </returns>
/// 
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
	*NewBuffer = malloc(pOPTIONAL->SizeOfImage);
	if (*NewBuffer == NULL)
	{
		std::cout << "�ڴ�������" << std::endl;
		return 0;
	}
	memset(*NewBuffer, 0, pOPTIONAL->SizeOfImage);
	
	// ����Headers��NewBuffer�����ƴ�СSizeOfHeaders
	/*for (size_t i = 0; i < pOPTIONAL->SizeOfHeaders; i++)
	{
		*((char*)*NewBuffer + i) = *((char*)ImageBuffer + i);
	}*/
	memcpy(*NewBuffer,ImageBuffer,pOPTIONAL->SizeOfHeaders);
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
		memcpy(dest, src, pSECTION[i].SizeOfRawData);
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


/// <summary>
/// �÷������ڴ��е�����д�뵽�ļ���
/// </summary>
/// <param name="pMemBuffer">�ڴ�����</param>
/// <param name="size">Ҫ���ƵĴ�С</param>
/// <param name="lpszFile">Ҫ�����ļ���·��</param>
/// <returns>
/// ����0��ʾд��ʧ�ܣ����򷵻ظ��ƵĴ�С
/// </returns>
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

/// <summary>
/// �÷������ڴ�ƫ��תΪ�ļ�ƫ��
/// </summary>
/// <param name="FileBuffer">FileBufferָ��</param>
/// <param name="dwRva">�ڴ�ƫ��</param>
/// <returns>
/// ����0��ʾת��ʧ�ܣ����򷵻��ļ�ƫ��FOA
/// </returns>
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
