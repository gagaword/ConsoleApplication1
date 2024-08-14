#include "my_25.h"
#include "My_day23.h"

#define DEBUG 0

bool GetPeheadersInfo(LPVOID Buffer, PEHeaders &peheader)
{
	if (Buffer == NULL)
	{
		return false;
	}

	// DOS Header
	peheader.dosHeader = (PIMAGE_DOS_HEADER)Buffer;
	if (peheader.dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		perror("DOSͷǩ������");
		return false;
	}

	// NT Header
	peheader.ntHeaders = (PIMAGE_NT_HEADERS32)((BYTE*)Buffer + peheader.dosHeader->e_lfanew);
	if (peheader.ntHeaders->Signature != IMAGE_NT_SIGNATURE)
	{
		perror("NTͷǩ������");
		return false;
	}

	// FILE Header
	peheader.fileHeader = &peheader.ntHeaders->FileHeader;
	if (DEBUG)
	{
		std::cout << "FILE HEADER-----> " << std::hex << peheader.fileHeader->Machine << std::endl;
	}

	// OPTION Header
	peheader.optionalHeader = &peheader.ntHeaders->OptionalHeader;
	if (DEBUG)
	{
		std::cout << "OPTION HEADER-----> " << std::hex << peheader.optionalHeader->Magic << std::endl;
	}

	// SECTIOn Header
	peheader.sectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)peheader.optionalHeader + peheader.fileHeader->SizeOfOptionalHeader);
	if (DEBUG)
	{
		std::cout << "SECTION HEADER-----> " << std::hex << peheader.sectionHeader->SizeOfRawData << std::endl;
	}

	// DATA HEADER
	peheader.dataHeaders = (PIMAGE_DATA_DIRECTORY)&peheader.optionalHeader->DataDirectory;
	if (DEBUG)
	{
		std::cout << "Export VirtualAddress------> " << peheader.dataHeaders[0].VirtualAddress << std::endl;
	}
	return true;
}

bool PrintDataExport(LPCSTR filePath)
{

	if (!filePath)
	{
		perror("��������");
		return false;
	}
	// ��ȡ�ļ���FileBuffer
	LPVOID fileBuffer = NULL;
	DWORD readFileResult = ReadFile(filePath, &fileBuffer);

	if (!readFileResult)
	{
		return false;
	}

	// ��ȡPE��Ϣ
	PEHeaders peheader;
	bool GetPEInfo = GetPeheadersInfo(fileBuffer, peheader);
	

	if (!GetPEInfo)
	{
		return false;
	}

	// ������λ��
	// ͨ��PEHeaders��ȡ������λ��
	DWORD VA = 0;
	VA = peheader.dataHeaders->VirtualAddress;
	if (DEBUG)
	{
		std::cout << std::hex << "PEHeaders Data_Exports Address------>" << VA << std::endl;
	}

	// ͨ��OPTIONAL��ȡ��������
	//std::cout << "Optional Data_Exports Address------->"  <<  peheader.optionalHeader->DataDirectory[0].VirtualAddress << std::endl;
	
	// RVAתFOV
	DWORD FOV = RvaToFov(VA, fileBuffer);
	if (DEBUG)
	{
		std::cout << std::hex << "FOV-----> " << FOV << std::endl;
	}

	// ������
	PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)fileBuffer + FOV);
	
	std::cout << "**********************Export Info*******************************" << std::endl;

	std::cout << "ģ�����Ƶ�ַ-------------> " << std::hex << std::uppercase << pExport->Name << std::endl;
	std::cout << "��ַ---------------------> " << pExport->Base << std::endl;
	std::cout << "��������-----------------> " << pExport->NumberOfFunctions << std::endl;
	std::cout << "������������-------------> " << pExport->NumberOfNames << std::endl;
	std::cout << "������ַ-----------------> " << std::hex << std::uppercase << pExport->AddressOfFunctions << std::endl;
	std::cout << "�������Ƶ�ַ-------------> " << std::hex << std::uppercase << pExport->AddressOfNames << std::endl;
	std::cout << "����������ŵ�ַ---------> " << std::hex << std::uppercase << pExport->AddressOfNameOrdinals << std::endl;


	DWORD AddressNamesFov = RvaToFov(pExport->AddressOfNames, fileBuffer);
	DWORD NameFOV = RvaToFov(pExport->Name, fileBuffer);
	DWORD AddressFunction = RvaToFov(pExport->AddressOfFunctions, fileBuffer);
	DWORD AddressNameOrdinals = RvaToFov(pExport->AddressOfNameOrdinals, fileBuffer);

	std::cout << "����:�ļ�ƫ��----------> " << std::hex << std::uppercase<< NameFOV << std::endl;
	std::cout << "��������:�ļ�ƫ��------> " << std::hex << std::uppercase << AddressNamesFov << std::endl;
	std::cout << "������ַ:�ļ�ƫ��------> " << std::hex << std::uppercase << AddressFunction << std::endl;
	std::cout << "�������:�ļ�ƫ��------> " << std::hex << std::uppercase << AddressNameOrdinals << std::endl;


	std::cout << "*****************************Function Info*************************************" << std::endl;

	printf("�ļ�����---->%s\n", ((char*)fileBuffer + NameFOV));

	// ��ȡ��Ϣ
	DWORD* pNameArray = (DWORD*)((BYTE*)fileBuffer + AddressNamesFov);
	DWORD* pFunctionAddress = (DWORD*)((BYTE*)fileBuffer + AddressFunction);
	WORD* pNameOrdinals = (WORD*)((BYTE*)fileBuffer + AddressNameOrdinals);
	
	for (DWORD i = 0; i < pExport->NumberOfNames; i++) {
		std::cout << "********** Function:" << i << " ******************" << std::endl;
		DWORD functionNameFov = RvaToFov(pNameArray[i], fileBuffer);
		WORD functionOrdinal = pNameOrdinals[i];
		DWORD functionAddresss = pFunctionAddress[i];
		DWORD functionFOV = RvaToFov(pFunctionAddress[i], fileBuffer);
		std::cout << "Function FOV: " << std::hex << std::uppercase <<  functionFOV << std::endl;
		std::cout << "Function RVA: " << std::hex << std::uppercase << functionAddresss << std::endl;
		printf("Function Name: %s\nFunction Ordinal: %d\n", (char*)fileBuffer + functionNameFov, functionOrdinal);
	}

	return true;
}

DWORD RvaToFov(DWORD RVA, LPVOID fileBuffer)
{
	if (RVA == NULL || fileBuffer == nullptr)
	{
		return 0;
	}

	PEHeaders peheader;
	if (!GetPeheadersInfo(fileBuffer, peheader))
	{
		return 0;
	}
	
	// ȷ��RVA���ĸ���
	size_t numberSection = peheader.fileHeader->NumberOfSections;
	DWORD VA = 0, PR = 0;
	DWORD FOA = 0;
	size_t is = 0;
	for (size_t i = 0; i < numberSection; i++)
	{
		if (RVA >= peheader.sectionHeader[i].VirtualAddress && RVA <= peheader.sectionHeader[i + 1].VirtualAddress)
		{
			VA = peheader.sectionHeader[i].VirtualAddress;
			PR = peheader.sectionHeader[i].PointerToRawData;
			is = 1;
			break;
		}
	}

	if (DEBUG)
	{
		std::cout << "VA------> " << VA << "\nPA------> " << PR << std::endl;
	}

	// ����FOA
	if (is)
	{
		FOA = (RVA - VA) + PR;
		return FOA;

	}
	return 0;
}

DWORD algin(DWORD value, DWORD alginValue)
{
	if (alginValue == 0)
	{
		return value;
	}
	return (value + alginValue - 1) / alginValue * alginValue;
}
