#include "day28.h"


using namespace std;
/**
 * @brief �÷���ͨ�������ע��DLL
 * @param filePath ע��Ŀ��
 * @param InjectionDll Ҫע���DLL
 * @param functionName DLL�е�����������
 * @return 
*/

unsigned int align_up(unsigned int value, unsigned int alignment) {
	return (value + alignment - 1) & ~(alignment - 1);

}

bool MovImportAndInjectionDll(LPCSTR filePath, LPCSTR InjectionDll, LPCSTR functionName)
{
	
	if (!filePath || !InjectionDll || !functionName)return false;
	

	// ��ȡ����
	LPVOID fileBuffer = nullptr;
	DWORD ReadFileSize = ReadFile(filePath, &fileBuffer);
	if (!ReadFileSize)return false;
	

	// PE��Ϣ
	PEHeaders peheaders;
	if (!GetPeheadersInfo(fileBuffer, peheaders)) return false;
	
	// ������С
	DWORD importSize = peheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;

	// ׷��0x200�ֽ�
	DWORD addByte = importSize + 0x100;
	BYTE* NewFileBuffer = (BYTE*)realloc(fileBuffer, ReadFileSize + addByte);
	memset(ReadFileSize + NewFileBuffer, 0, addByte);

	// ����PE��Ϣ
	PEHeaders newPeheaders;
	if (!GetPeheadersInfo(NewFileBuffer, newPeheaders))
	{
		return false;
	}

	// �������Ϣ
	PIMAGE_IMPORT_DESCRIPTOR importAddress = (PIMAGE_IMPORT_DESCRIPTOR)(DWORD*)((BYTE*)NewFileBuffer + RvaToFoa(newPeheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, NewFileBuffer));

	// ��ȡ���������Ϣ
	DWORD SectionAlign = newPeheaders.optionalHeader->SectionAlignment;
	DWORD FileAlign = newPeheaders.optionalHeader->FileAlignment;

	// ��ȡ��һ���ڵ�VirtualAddress��PointerToRawData
	PIMAGE_SECTION_HEADER LastSection = newPeheaders.sectionHeader + (newPeheaders.fileHeader->NumberOfSections - 1);

	// �����ڱ�
	// ȷ��λ��
	PIMAGE_SECTION_HEADER EndSectionAddress = (PIMAGE_SECTION_HEADER)((BYTE*)newPeheaders.sectionHeader + (newPeheaders.fileHeader->NumberOfSections * IMAGE_SIZEOF_SECTION_HEADER));

	// �ڱ�ͷ
	PIMAGE_SECTION_HEADER StratSectionAddress = IMAGE_FIRST_SECTION(newPeheaders.ntHeaders);

	// ���ƽ����ݵ��½ڱ�
	memcpy_s((BYTE*)EndSectionAddress, IMAGE_SIZEOF_SECTION_HEADER, (BYTE*)StratSectionAddress, IMAGE_SIZEOF_SECTION_HEADER);
	const char name[] = ".GaGa!!!";
	memcpy_s((BYTE*)EndSectionAddress->Name, IMAGE_SIZEOF_SHORT_NAME, (BYTE*)name, sizeof(name) - 1);

	// ����PE�ֶ�
	newPeheaders.fileHeader->NumberOfSections += 0x1;
	newPeheaders.optionalHeader->SizeOfImage += addByte;

	// �����ڱ�����
	EndSectionAddress->Misc.VirtualSize = addByte;
	EndSectionAddress->SizeOfRawData = addByte;
	EndSectionAddress->VirtualAddress = align_up(LastSection->VirtualAddress + LastSection->Misc.VirtualSize, SectionAlign);
	EndSectionAddress->PointerToRawData = align_up(LastSection->PointerToRawData + LastSection->SizeOfRawData, FileAlign);
	EndSectionAddress->Characteristics = IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;


	// �ƶ�������½�
	BYTE* NewSectionAddress = (BYTE*)NewFileBuffer + ReadFileSize;
	memcpy(NewSectionAddress,(BYTE*)importAddress, importSize);

	// ���������
	PIMAGE_IMPORT_DESCRIPTOR NewEndSectionAddress = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD*)((BYTE*)NewFileBuffer + ReadFileSize + importSize - sizeof(_IMAGE_IMPORT_DESCRIPTOR)));
	// ����ͷ�������Ϣ���µ����
	memcpy(NewEndSectionAddress, (BYTE*)importAddress, sizeof(_IMAGE_IMPORT_DESCRIPTOR));

	// ����DLL����
	BYTE* DllNameAddress = (BYTE*)NewEndSectionAddress + sizeof(_IMAGE_IMPORT_DESCRIPTOR) * 2;
	DWORD NameSize = strlen(InjectionDll) + 1;
	strcpy_s((char*)DllNameAddress, NameSize, InjectionDll);

	// ����RVA
	DWORD NameRva = FoaToRva(DllNameAddress - NewFileBuffer, NewFileBuffer);
	NewEndSectionAddress->Name = NameRva;

	// ����һ��BY_NAME
	PIMAGE_IMPORT_BY_NAME By_NameAddress = (PIMAGE_IMPORT_BY_NAME)((DWORD*)((BYTE*)DllNameAddress + NameSize));
	memset(By_NameAddress, 0, 0x2);
	DWORD FuncNameSize = strlen(functionName) + 0x1;
	strcpy_s((char*)By_NameAddress + 0x2, FuncNameSize, functionName);

	DWORD By_Name_RVA = FoaToRva((BYTE*)By_NameAddress - NewFileBuffer, NewFileBuffer);

	// ����һ������Ϊ8��INT��IAT
	BYTE* IntAndIatAddress = (BYTE*)By_NameAddress + FuncNameSize + 0x2;
	*(DWORD*)IntAndIatAddress = By_Name_RVA;

	// IAT
	// ��Ϊ��DWORD*���ͣ����Լ�0x2������ڼ���0x8
	BYTE* IatAddress = IntAndIatAddress + 0x8;
	*((DWORD*)IatAddress) = By_Name_RVA;

	// �޸��µ�����INT��IAT
	DWORD INT_RVA = FoaToRva(IntAndIatAddress - NewFileBuffer, NewFileBuffer);
	DWORD IAT_RVA = FoaToRva(IatAddress - NewFileBuffer, NewFileBuffer);
	NewEndSectionAddress->OriginalFirstThunk = INT_RVA;
	NewEndSectionAddress->FirstThunk = IAT_RVA;

	// ����Ŀ¼��
	DWORD NewSectionRva = FoaToRva(NewSectionAddress - NewFileBuffer, NewFileBuffer);
	newPeheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = NewSectionRva;
	newPeheaders.optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size += sizeof(_IMAGE_IMPORT_DESCRIPTOR);


	// ����
	FwritrFile(NewFileBuffer, ReadFileSize + addByte, filePath);

	return false;
}
