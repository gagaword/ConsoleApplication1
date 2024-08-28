#include "day26.h"
#include "My_day23.h"
#include "my_25.h"

using namespace std;

bool PrintBaseloc(LPCSTR filePath)
{
	if (!filePath)
	{
		return false;
	}

	LPVOID fileBuffer = nullptr;
	if (!ReadFile(filePath, &fileBuffer))
	{
		return false;
	}

	PEHeaders peheader{};
	if (!GetPeheadersInfo(fileBuffer, peheader))
	{
		return false;
	}

	if (peheader.optionalHeader == nullptr)
	{
		return false;
	}

	// �ض�λ��
	PIMAGE_BASE_RELOCATION pBASE_RELOCATION = (PIMAGE_BASE_RELOCATION)&peheader.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
	PIMAGE_BASE_RELOCATION PBASE = (PIMAGE_BASE_RELOCATION)((BYTE*)fileBuffer + RvaToFov(pBASE_RELOCATION->VirtualAddress, fileBuffer));
	// ����
	while (PBASE->VirtualAddress != 0)
	{
		// ��������
		DWORD BaseNumer = (PBASE->SizeOfBlock - (sizeof(DWORD) * 2)) / sizeof(WORD);
		// ��ʼλ��
		WORD* BaseAddress1 = (WORD*)((BYTE*)PBASE + sizeof(DWORD) * 2);
		cout << "*************" << hex << PBASE->VirtualAddress << "**************" << endl;
		for (size_t i = 0; i < BaseNumer; i++)
		{
			if (((*BaseAddress1 & 0xF000) >> 12) != IMAGE_REL_BASED_HIGHLOW)
			{
				break;
			}
			cout << "RVA: " << hex << uppercase << (PBASE->VirtualAddress + ((*BaseAddress1) & 0xFFF)) << "  ";
			cout << "Offset " << hex << uppercase << RvaToFov((PBASE->VirtualAddress + ((*BaseAddress1) & 0xFFF)), fileBuffer) << "  ";
			cout << "Type " << hex << uppercase << ((*BaseAddress1 & 0xF000) >> 12) << endl;
			BaseAddress1++;
		}
		
		// �ƶ�����һ���ض�λ��
		PBASE = (PIMAGE_BASE_RELOCATION)((DWORD)((BYTE*)PBASE + PBASE->SizeOfBlock));
	}
	return true;
}

bool MoveExport(LPCSTR filePath)
{
	if (!filePath)	return false;

	LPVOID fileBuffer = nullptr;
	DWORD readfileResu = ReadFile(filePath, &fileBuffer);
	if (!readfileResu) return false;

	PEHeaders peheader{};
	if (!GetPeheadersInfo(fileBuffer, peheader))
	{
		free(fileBuffer);
		return false;
	}

	// ������
	// ׷���ֽ�
	DWORD addByte = 0x1000;
	unsigned char* newBuffer = (unsigned char*)realloc(fileBuffer, readfileResu + addByte);
	if (!newBuffer)
	{
		free(fileBuffer);
		return false;
	}
	memset(newBuffer + readfileResu, 0, addByte);

	// ����PE��Ϣ
	PEHeaders newPehear{};

	if (!GetPeheadersInfo(newBuffer, newPehear))return false;
	if (newPehear.optionalHeader == nullptr) return false;

	// �½ڱ�λ��
	PIMAGE_SECTION_HEADER addSectionAddress = (PIMAGE_SECTION_HEADER)((BYTE*)newPehear.sectionHeader + (IMAGE_SIZEOF_SECTION_HEADER * newPehear.fileHeader->NumberOfSections));

	// �������ݵ��½ڱ�
	memcpy_s((char*)addSectionAddress, IMAGE_SIZEOF_SECTION_HEADER, (char*)newPehear.sectionHeader, IMAGE_SIZEOF_SECTION_HEADER);
	addSectionAddress->Characteristics |= IMAGE_SCN_MEM_EXECUTE;
	const char name[] = ".GaGa!!!";
	memcpy_s((char*)addSectionAddress->Name, IMAGE_SIZEOF_SHORT_NAME, (char*)name, sizeof(name) - 1);

	// �����ڱ��ֶ�
	DWORD newVirtualAddress = 0;
	DWORD newPointerAddress = 0;
	DWORD newSizeOfRawData = addByte;
	DWORD newVirtualSize = addByte;

	// ��ȡ�½ڱ��ֶ�
	for (size_t i = 0; i < newPehear.fileHeader->NumberOfSections; i++)
	{
		if (i == newPehear.fileHeader->NumberOfSections - 1)
		{
			newPointerAddress = newPehear.sectionHeader[i].PointerToRawData + newPehear.sectionHeader[i].SizeOfRawData;
			DWORD align = (((newPehear.sectionHeader[i].Misc.VirtualSize + newPehear.sectionHeader[i].VirtualAddress) + 0xFFF) / 0x1000) * 0x1000;
			newVirtualAddress = align;
			/*cout << hex << align << endl;
			cout << newPehear.sectionHeader[i].Name << endl;*/
			break;
		}
	}

	// ����PE�ֶ�
	newPehear.fileHeader->NumberOfSections += 0x1;
	newPehear.optionalHeader->SizeOfImage += 0x1000;

	// �����½ڱ��ֶ�
	addSectionAddress->VirtualAddress = newVirtualAddress;
	addSectionAddress->Misc.VirtualSize = newVirtualSize;
	addSectionAddress->SizeOfRawData = newSizeOfRawData;
	addSectionAddress->PointerToRawData = newPointerAddress;

	
	// ��������Ϣ
	DWORD exportAddressFOA = RvaToFov(newPehear.dataHeaders[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress, newBuffer);
	PIMAGE_EXPORT_DIRECTORY pEXPORT = (PIMAGE_EXPORT_DIRECTORY)(newBuffer + exportAddressFOA);
	cout << "������λ�ã�" <<  hex << exportAddressFOA << endl;

	// �½���ʼλ��
	DWORD* SectionAddress = (DWORD*)((BYTE*)newBuffer + readfileResu);
	cout << "�ڱ���ʼλ��FOA: " << hex << readfileResu << endl;

	// ���� AddressOfFunctions ���½�
	memcpy(SectionAddress, newBuffer + RvaToFov(pEXPORT->AddressOfFunctions, newBuffer), pEXPORT->NumberOfFunctions * sizeof(DWORD));

	// ���� AddressOfNameOrdinals ���½�
	WORD* Ordinals = (WORD*)((BYTE*)SectionAddress + pEXPORT->NumberOfFunctions * sizeof(DWORD));
	memcpy(Ordinals, newBuffer + RvaToFov(pEXPORT->AddressOfNameOrdinals, newBuffer), pEXPORT->NumberOfFunctions * sizeof(WORD));

	// ���� AddressOfNames ���½�
	DWORD* NamesAddress = (DWORD*)((BYTE*)Ordinals + pEXPORT->NumberOfFunctions * sizeof(WORD));	
	memcpy(NamesAddress, newBuffer + RvaToFov(pEXPORT->AddressOfNames, newBuffer), pEXPORT->NumberOfFunctions * sizeof(DWORD));

	// �������ֵ��½�
	BYTE* nameData = (BYTE*)((BYTE*)NamesAddress + pEXPORT->NumberOfFunctions * sizeof(DWORD));
	for (size_t i = 0; i < pEXPORT->NumberOfFunctions; i++)
	{
		const char* functionName = (const char*)((BYTE*)newBuffer + RvaToFov(NamesAddress[i], newBuffer));
		size_t nameLength = strlen(functionName) + 1;
		memcpy(nameData, functionName, nameLength);
		// ֱ�Ӹ���NamesAddress��ַ
		NamesAddress[i] = FoaToRva((DWORD)(nameData - newBuffer), newBuffer);
		nameData += nameLength;
	}

	// ����ģ�����Ƶ��½���
	DWORD* Module = (DWORD*)(nameData + pEXPORT->NumberOfFunctions);
	memcpy(Module, newBuffer + RvaToFov(pEXPORT->Name, newBuffer), pEXPORT->NumberOfFunctions * sizeof(DWORD));

	// ���Ƶ������½�
	PIMAGE_EXPORT_DIRECTORY NewExportAddress = (PIMAGE_EXPORT_DIRECTORY)(DWORD*)((BYTE*)nameData + pEXPORT->NumberOfFunctions * sizeof(DWORD));
	memcpy(NewExportAddress, pEXPORT, sizeof(IMAGE_EXPORT_DIRECTORY));

	// ���� IMAGE_EXPORT+DIRECTORY �ֶ�
	NewExportAddress->AddressOfFunctions = FoaToRva((DWORD)((BYTE*)SectionAddress - newBuffer), newBuffer);
	NewExportAddress->AddressOfNameOrdinals = FoaToRva((DWORD)((BYTE*)Ordinals - newBuffer), newBuffer);
	NewExportAddress->AddressOfNames = FoaToRva((DWORD)((BYTE*)NamesAddress - newBuffer), newBuffer);
	NewExportAddress->Name = FoaToRva((DWORD)((BYTE*)Module - newBuffer), newBuffer);

	// ���� IMAGE_DIRECTORY_ENTRY_EXPORT ָ���±��е��½ṹ
	newPehear.dataHeaders[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress = newVirtualAddress + (DWORD)((BYTE*)NewExportAddress - (BYTE*)SectionAddress);

	// д���ļ�
	if (!FwritrFile(newBuffer, readfileResu + addByte, filePath))
	{
		free(newBuffer);
		return false;
	}
	free(newBuffer);

	return true;
}

bool MoveBaseReloc(LPCSTR filePath)
{
	if (!filePath)	return false;
	LPVOID fileBuffer = nullptr;
	DWORD readfileResu = ReadFile(filePath, &fileBuffer);
	if (!readfileResu) return false;

	PEHeaders peheader{};
	if (!GetPeheadersInfo(fileBuffer, peheader))
	{
		free(fileBuffer);
		return false;
	}

	// ������
	// ׷���ֽ�
	DWORD addByte = 0x1000;
	unsigned char* newBuffer = (unsigned char*)realloc(fileBuffer, readfileResu + addByte);
	if (!newBuffer)
	{
		free(fileBuffer);
		return false;
	}
	memset(newBuffer + readfileResu, 0, addByte);

	// ����PE��Ϣ
	PEHeaders newPehear{};

	if (!GetPeheadersInfo(newBuffer, newPehear))return false;
	if (newPehear.optionalHeader == nullptr) return false;

	// �½ڱ����λ��
	PIMAGE_SECTION_HEADER addSectionAddress = (PIMAGE_SECTION_HEADER)((BYTE*)newPehear.sectionHeader + (IMAGE_SIZEOF_SECTION_HEADER * newPehear.fileHeader->NumberOfSections));

	// �������ݵ��½ڱ�
	memcpy_s((char*)addSectionAddress, IMAGE_SIZEOF_SECTION_HEADER, (char*)newPehear.sectionHeader, IMAGE_SIZEOF_SECTION_HEADER);
	addSectionAddress->Characteristics |= IMAGE_SCN_MEM_EXECUTE;
	const char name[] = ".GaGa!!!";
	memcpy_s((char*)addSectionAddress->Name, IMAGE_SIZEOF_SHORT_NAME, (char*)name, sizeof(name) - 1);

	// �����ڱ��ֶ�
	DWORD newVirtualAddress = 0;
	DWORD newPointerAddress = 0;
	DWORD newSizeOfRawData = addByte;
	DWORD newVirtualSize = addByte;

	// ��ȡ�½ڱ��ֶ�
	for (size_t i = 0; i < newPehear.fileHeader->NumberOfSections; i++)
	{
		if (i == newPehear.fileHeader->NumberOfSections - 1)
		{
			newPointerAddress = newPehear.sectionHeader[i].PointerToRawData + newPehear.sectionHeader[i].SizeOfRawData;
			DWORD align = (((newPehear.sectionHeader[i].Misc.VirtualSize + newPehear.sectionHeader[i].VirtualAddress) + 0xFFF) / 0x1000) * 0x1000;
			newVirtualAddress = align;
			/*cout << hex << align << endl;
			cout << newPehear.sectionHeader[i].Name << endl;*/
			break;
		}
	}

	// ����PE�ֶ�
	newPehear.fileHeader->NumberOfSections += 0x1;
	newPehear.optionalHeader->SizeOfImage += 0x1000;

	// �����½ڱ��ֶ�
	addSectionAddress->VirtualAddress = newVirtualAddress;
	addSectionAddress->Misc.VirtualSize = newVirtualSize;
	addSectionAddress->SizeOfRawData = newSizeOfRawData;
	addSectionAddress->PointerToRawData = newPointerAddress;

	// ****************************************************************

	// �ض�λ��λ��
	PIMAGE_BASE_RELOCATION pBASE_RELOCATION = (PIMAGE_BASE_RELOCATION)&newPehear.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
	// ����λ��
	PIMAGE_BASE_RELOCATION pBASE_DATA = (PIMAGE_BASE_RELOCATION)((BYTE*)newBuffer + RvaToFov(pBASE_RELOCATION->VirtualAddress, newBuffer));
	DWORD* dataAddress = (DWORD*)((BYTE*)newBuffer + RvaToFov(pBASE_RELOCATION->VirtualAddress, newBuffer));
	// ����
	DWORD DataNumer = 0;

	while (pBASE_DATA->VirtualAddress != 0)
	{
		DataNumer += pBASE_DATA->SizeOfBlock;
		pBASE_DATA = (PIMAGE_BASE_RELOCATION)((BYTE*)pBASE_DATA + pBASE_DATA->SizeOfBlock);
	}

	// �½ڱ�λ��
	DWORD* newSectionAddress = (DWORD*)((BYTE*)newBuffer + readfileResu);
	// ��������
	memcpy(newSectionAddress, dataAddress, DataNumer);
	
	
	// ����Ŀ¼��ʹ��ָ���µ��ض���λ��
	DWORD newAddress = FoaToRva(((BYTE*)newSectionAddress - newBuffer), newBuffer);
	newPehear.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress = newAddress;
	newPehear.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size = DataNumer;

	// �޸Ļ���ַ�������ض�λ��
	newPehear.optionalHeader->ImageBase += 0x1000;
	PIMAGE_BASE_RELOCATION pNewBASE_DATA = (PIMAGE_BASE_RELOCATION)((BYTE*)newBuffer + RvaToFov(pBASE_RELOCATION->VirtualAddress, newBuffer));

	while (pNewBASE_DATA->VirtualAddress != 0)
	{
		// ��������
		DWORD BaseNumer = (pNewBASE_DATA->SizeOfBlock - (sizeof(DWORD) * 2)) / sizeof(WORD);
		// ��ʼλ��
		WORD* BaseAddress1 = (WORD*)((BYTE*)pNewBASE_DATA + sizeof(DWORD) * 2);

		for (size_t i = 0; i < BaseNumer; i++)
		{
			WORD typeOffset = *BaseAddress1;
			DWORD type = (typeOffset & 0xF000) >> 12;
			DWORD offset = typeOffset & 0x0FFF;

			if (type != IMAGE_REL_BASED_HIGHLOW)
			{
				break;
			}

			// ������Ҫ��������������ַ
			DWORD rvaToPatch = pNewBASE_DATA->VirtualAddress + offset;

			// ��RVAת��Ϊ�ļ�ƫ�ƣ�FOA��
			DWORD fileOffsetToPatch = RvaToFov(rvaToPatch, newBuffer);

			// ��ȡҪ�������ڴ�λ��
			DWORD* patchLocation = (DWORD*)((BYTE*)newBuffer + fileOffsetToPatch);
			*patchLocation += 0x1000;
			BaseAddress1++;
		}

		// �ƶ�����һ���ض�λ��
		pNewBASE_DATA = (PIMAGE_BASE_RELOCATION)((BYTE*)pNewBASE_DATA + pNewBASE_DATA->SizeOfBlock);
	}

	if (!FwritrFile(newBuffer, (readfileResu + addByte), filePath))
	{
		return false;
	}

	free(newBuffer);
}

