#include "day28.h"

using namespace std;
/**
 * @brief �÷���ͨ�������ע��DLL
 * @param filePath ע��Ŀ��
 * @param InjectionDll Ҫע���DLL
 * @param functionName DLL�е�����������
 * @return 
*/

bool MovImportAndInjectionDll(LPCSTR filePath, LPCSTR InjectionDll, LPCSTR functionName)
{
	if (!filePath || !InjectionDll || !functionName) return false;
	
	// �ƶ������
	LPVOID fileBuffer = nullptr;
	DWORD fileSize = ReadFile(filePath, &fileBuffer);

	cout << "�ļ���С: " << hex << uppercase << fileSize << endl;

	if (fileSize == 0)		return false;
	
	PEHeaders peheaders;
	if (!GetPeheadersInfo(fileBuffer,peheaders))	return false;
	
	// �������һ���ڣ�0x1000
	DWORD addByte = fileSize + 0x1000;
	unsigned char* NewFileBuffer = (unsigned char*)realloc(fileBuffer, addByte);
	memset(NewFileBuffer + fileSize , 0, 0x1000);

	// ����PE��Ϣ
	PEHeaders newPeheaders;
	if (!GetPeheadersInfo(NewFileBuffer, newPeheaders))
	{
		return false;
	}

	for (size_t i = 0; i < newPeheaders.fileHeader->NumberOfSections; i++)
	{
		if (i == newPeheaders.fileHeader->NumberOfSections - 1)
		{
			newPeheaders.sectionHeader[i].Misc.VirtualSize += 0x1000;
			newPeheaders.sectionHeader[i].SizeOfRawData += 0x1000;
		}
	}
	// sizeOfImageҲҪ����0x1000����������޷�������
	newPeheaders.optionalHeader->SizeOfImage += 0x1000;

	// �ƶ��������չ��

	// ��չ��λ��
	BYTE* addSectionAddress = (BYTE*)NewFileBuffer + fileSize;
	// �����λ��
	PIMAGE_IMPORT_DESCRIPTOR importAddress = (PIMAGE_IMPORT_DESCRIPTOR)(DWORD*)((BYTE*)NewFileBuffer + *(DWORD*)newPeheaders.importSection);
	BYTE* copyImportAddress = (BYTE*)NewFileBuffer + *(DWORD*)newPeheaders.importSection;

	while (importAddress->OriginalFirstThunk != 0 && importAddress->FirstThunk != 0)
	{
		// ���� IMAGE_IMPORT_DESCRIPTOR �ṹ��
		memcpy(addSectionAddress, copyImportAddress, sizeof(IMAGE_IMPORT_DESCRIPTOR));
		// ���µ�ַ
		addSectionAddress += sizeof(IMAGE_IMPORT_DESCRIPTOR);
		copyImportAddress += sizeof(IMAGE_IMPORT_DESCRIPTOR);
		importAddress++;
	}

	// ׷��IMAGE_IMPORT_BY_NAME�ṹ
	// ǰ�����ֽ�Ϊ0x00
	BYTE* addImportBy_Name_two = (BYTE*)((BYTE*)NewFileBuffer + fileSize + 0x200);
	
	BYTE* addImportBy_Name = (BYTE*)((BYTE*)NewFileBuffer + fileSize + 0x202);
	size_t bufferSize = strlen(functionName) + 1;
	strcpy_s(((char*)addImportBy_Name), bufferSize, functionName);

	// IMAGE_IMPORT_BY_NAME��RVA
	DWORD IMAGE_IMPORT_BY_NAME_RVA = addImportBy_Name_two - NewFileBuffer;
	cout << IMAGE_IMPORT_BY_NAME_RVA << endl;

	// INT
	BYTE* addImportData_INT = (BYTE*)((BYTE*)NewFileBuffer + fileSize + 0x100);
	memcpy(addImportData_INT, &IMAGE_IMPORT_BY_NAME_RVA, sizeof(DWORD));

	// IAT
	BYTE* addImportData_IAT = addImportData_INT + 0x8;
	memcpy(addImportData_IAT, &IMAGE_IMPORT_BY_NAME_RVA, sizeof(DWORD));

	// �������������
	// ���������λ��
	BYTE* EndImportAddress = addSectionAddress;

	DWORD address_INT = addImportData_INT - NewFileBuffer;
	DWORD address_IAT = addImportData_IAT - NewFileBuffer;

	memcpy(EndImportAddress, &address_INT, sizeof(DWORD));
	memcpy(EndImportAddress + 0x10, &address_IAT, sizeof(DWORD));

	// DLL�����ַ���
	BYTE* DllNameAddress = (BYTE*)((BYTE*)NewFileBuffer + fileSize + 0x150);
	int DllNameSize = strlen(InjectionDll) + 1;
	strcpy_s(((char*)DllNameAddress), DllNameSize, InjectionDll);

	// ��������RVA���µ����
	DWORD NameRVA = DllNameAddress - NewFileBuffer;
	memcpy(EndImportAddress + 0xc, &NameRVA, sizeof(DWORD));

	// �޸�Ŀ¼���е�����RVAָ���µĵ�����ַ
	DWORD ImportRva = FoaToRva(fileSize, NewFileBuffer);
	newPeheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = ImportRva;

	// д���ļ�
	DWORD writeSize = FwritrFile(NewFileBuffer, addByte, filePath);

	
	return false;
}
