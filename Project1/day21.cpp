#include<iostream>	
#include<stdio.h>
#include<Windows.h>

#define ConstfilePath "C:\\Users\\GaGa\\Desktop\\A.exe"

LPVOID ReadFile(const char* FilePath)
{
	// �жϲ���
	if (FilePath == NULL)
	{
		std::cout << "��������" << std::endl;
		return NULL;
	}

	// ���ļ�
	FILE* file = nullptr;
	errno_t isFile = fopen_s(&file, FilePath, "rb");
	if (isFile != 0)
	{
		std::cout << "���ļ�ʧ��" << std::endl;
		return NULL;
	}

	// �����ڴ�
	fseek(file,0,SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char* FileSpace = (unsigned char*)malloc(fileSize);
	if (FileSpace == NULL)
	{
		std::cout << "�����ڴ����" << std::endl;
		fclose(file);
		return NULL;
	}
	memset(FileSpace,0,fileSize);
	// ��ȡ����
	size_t ReadFileSize = fread_s(FileSpace, fileSize, 1, fileSize, file);
	if (ReadFileSize != fileSize)
	{
		std::cout << "��ȡ����ʧ��" << std::endl;
		fclose(file);
		free(FileSpace);
		return NULL;
	}
	fclose(file);
	std::cout << "�ļ��ֽ�:" << fileSize << std::endl;
	return FileSpace;
}

VOID PrintfNTData()
{
	LPVOID pFileBuffer = NULL;

	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS32 pNtHeader = nullptr;
	PIMAGE_FILE_HEADER pFileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionalHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;

	// FileData�����ļ���ָ��
	pFileBuffer = ReadFile(ConstfilePath);

	if (!pFileBuffer)
	{
		std::cout << "��ȡ����" << std::endl;
		return;
	}


	/*unsigned char* temp = (unsigned char*)pFileBuffer;
	for (size_t i = 0; i < 20; i++)
	{
		printf("%x ", *(temp++));
	}*/
	
	// �ж��Ƿ�PE�ļ�
	if (*((PWORD)pFileBuffer) == IMAGE_DOS_SIGNATURE)
	{
		std::cout << "����ЧMZ�ļ�" << std::endl;
	}
	else 
	{
		std::cout << "������ЧMZ�ļ�" << std::endl;
		free(pFileBuffer);
		return;
	}

	// ��ӡODSͷ
	std::cout << "*****************************DOS_HEADER*****************************" << std::endl;
	pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
	std::cout << std::hex << pDosHeader->e_magic << std::endl;
	std::cout << std::hex << pDosHeader->e_lfanew << std::endl;

	// ��ӡNTͷ,NTͷҪע�����DOS��lfanew.
	std::cout << "*****************************NT_HEADER******************************" << std::endl;
	pNtHeader = (PIMAGE_NT_HEADERS32)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
	std::cout << std::hex << pNtHeader->Signature << std::endl;

	if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
	{
		std::cout << "������ЧPE�ļ�" << std::endl;
		free(pFileBuffer);
		return;
	}
	else
	{
		std::cout << "��ЧPE�ļ�" << std::endl;
	}


	// ��ӡ��׼PEͷ
	std::cout << "*****************************FILE_HEADER****************************" << std::endl;
	pFileHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNtHeader)+ 0x4);
	std::cout << std::hex << "Machine:" << pFileHeader->Machine << std::endl;
	std::cout << std::hex << "NumberOfSections:" << pFileHeader->NumberOfSections << std::endl;
	std::cout << std::hex << "TimeDateStamp:" << pFileHeader->TimeDateStamp << std::endl;
	std::cout << std::hex << "SizeOfOptionalHeader:" << pFileHeader->SizeOfOptionalHeader << std::endl;
	std::cout << std::hex << "Characteristics:" << pFileHeader->Characteristics << std::endl;


	std::cout << "*****************************OPTIONAL_HEADER****************************" << std::endl;
	// ��ӡ��չPEͷ
	pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)(((DWORD)pFileHeader) + IMAGE_SIZEOF_FILE_HEADER);
	std::cout << std::hex << "Magic:" << pOptionalHeader->Magic << std::endl;
	std::cout << std::hex << "SizeOfCode:" << pOptionalHeader->SizeOfCode << std::endl;
	std::cout << std::hex << "SizeOfUninitializedData:" << pOptionalHeader->SizeOfUninitializedData << std::endl;
	std::cout << std::hex << "AddressOfEntryPoint:" << pOptionalHeader->AddressOfEntryPoint << std::endl;
	std::cout << std::hex << "BaseOfCode:" << pOptionalHeader->BaseOfCode << std::endl;
	std::cout << std::hex << "BaseOfData:" << pOptionalHeader->BaseOfData << std::endl;
	std::cout << std::hex << "ImageBase:" << pOptionalHeader->ImageBase << std::endl;
	std::cout << std::hex << "SectionAlignment:" << pOptionalHeader->SectionAlignment << std::endl;
	std::cout << std::hex << "FileAlignment:" << pOptionalHeader->FileAlignment << std::endl;
	std::cout << std::hex << "DllCharacteristics:" << pOptionalHeader->DllCharacteristics << std::endl;
	std::cout << std::hex << "SizeOfStackReserve:" << pOptionalHeader->SizeOfStackReserve << std::endl;
	std::cout << std::hex << "SizeOfStackCommit:" << pOptionalHeader->SizeOfStackCommit << std::endl;
	std::cout << std::hex << "SizeOfHeapReserve:" << pOptionalHeader->SizeOfHeapReserve << std::endl;
	std::cout << std::hex << "SizeOfHeapCommit:" << pOptionalHeader->SizeOfHeapCommit << std::endl;
	std::cout << std::hex << "LoaderFlags:" << pOptionalHeader->LoaderFlags << std::endl;
	std::cout << std::hex << "NumberOfRvaAndSizes:" << pOptionalHeader->NumberOfRvaAndSizes << std::endl;
	free(pFileBuffer);
	
}
int main()
{

	PrintfNTData();

	return 0;
}