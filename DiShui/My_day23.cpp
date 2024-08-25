#include "My_day23.h"
#include "day22.h"

#define AddByte 0x1000
#define DEBUG 1

#define align_1000(VALUE) VALUE = ((VALUE + 0xFFF) / 0x1000) * 0x1000

// MessageBoxA��ַ
void* MessageBoxA_address = &MessageBoxA;

// Ӳ����
BYTE ShellCode[] = { 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00 };
int ShellLength = sizeof(ShellCode) / sizeof(ShellCode[0]);

// PE��Ϣ
struct PEHeaders {
	PIMAGE_DOS_HEADER dosHeader;
	PIMAGE_NT_HEADERS32 ntHeaders;
	PIMAGE_FILE_HEADER fileHeader;
	PIMAGE_OPTIONAL_HEADER32 optionalHeader;
	PIMAGE_SECTION_HEADER sectionHeader;
};

// ��ȡPEͷ
bool GetPEHeaders(LPVOID fileBuffer, PEHeaders& headers) {
	if (fileBuffer == nullptr) {
		return false;
	}

	headers.dosHeader = (PIMAGE_DOS_HEADER)fileBuffer;
	if (headers.dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		return false;
	}

	headers.ntHeaders = (PIMAGE_NT_HEADERS32)((BYTE*)fileBuffer + headers.dosHeader->e_lfanew);
	if (headers.ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
		return false;
	}

	headers.fileHeader = &headers.ntHeaders->FileHeader;
	headers.optionalHeader = &headers.ntHeaders->OptionalHeader;
	headers.sectionHeader = IMAGE_FIRST_SECTION(headers.ntHeaders);

	return true;
}

// ��ȡ�ļ�
DWORD ReadFile(IN LPCSTR filepath, OUT LPVOID* fileBuffer)
{
	if (filepath == NULL)
	{
		std::cout << "��������" << std::endl;
		return 0;
	}
	std::cout << "���ļ�:" << filepath << std::endl;

	FILE* file = NULL;
	errno_t fileResult = fopen_s(&file, filepath, "rb");
	if (fileResult != 0)
	{
		std::cout << "���ļ�ʧ��" << std::endl;
		return 0;
	}

	// ��ȡ�ļ���С
	fseek(file,0,SEEK_END);
	long fileSize = ftell(file);
	fseek(file,0,SEEK_SET);

	printf("�ļ��ֽ�------> %X \n", fileSize);

	// ����ռ��С
	*fileBuffer = malloc(fileSize);
	if (*fileBuffer == NULL)
	{
		std::cout << "�ռ�������" << std::endl;
		fclose(file);
		return 0;
	}
	memset(*fileBuffer, 0, fileSize);

	// ��ȡ�ļ�
	size_t freadResult = fread_s(*fileBuffer, fileSize, 1, fileSize, file);
	if (freadResult != fileSize)
	{
		std::cout << "��ȡ�ļ�����" << std::endl;
		return 0;
	}
	printf("��ȡ�ֽ�------> %X \n", freadResult);
	return freadResult;
}

// ����ShellCode
DWORD AddShellCode(IN LPCSTR filePath)
{	
	std::cout << "MessageBoxExA_Address---->" << MessageBoxA_address << std::endl;

	if (filePath == NULL)
	{
		return 0;
	}

	// ��ȡ�ļ�
	LPVOID fileBuffer = NULL;
	DWORD ReadFileResult = ReadFile((char*)filePath, &fileBuffer);
	if (ReadFileResult == 0) return 0;
	
	
	// ��ȡPE��Ϣ
	PEHeaders peheader;
	if (!GetPEHeaders(fileBuffer,peheader))
	{
		std::cerr << "��ЧPE�ļ�" << std::endl;
		return false;
	}

	size_t NumberSections = peheader.fileHeader->NumberOfSections;
	size_t FileOffset = 0;
	size_t MemeryOffset = 0;
	size_t MiscSize = 0;
	errno_t SizeRawData = 0;

	// ��ȡ.text�ֶ�
	for (int i = 0; i < NumberSections; i++)
	{
		if (strcmp((const char*)peheader.sectionHeader[i].Name,".text") == 0)
		{
			FileOffset = peheader.sectionHeader[i].PointerToRawData;
			MemeryOffset = peheader.sectionHeader[i].VirtualAddress;
			MiscSize = peheader.sectionHeader[i].Misc.VirtualSize;
			SizeRawData = peheader.sectionHeader[i].SizeOfRawData;
			break;
		}
	}

	if (FileOffset == 0)
	{
		std::cerr << "δ�ҵ�.text" << std::endl;
		return 0;
	}
	if ((int)(SizeRawData - MiscSize) < ShellLength)
	{
		std::cerr << "text�հ�����ռ䲻��" << std::endl;
		return false;
	}
	std::cout << "FileOffset---->" << std::hex << FileOffset << std::endl;
	std::cout << "MemeryOffset---->" << std::hex << MemeryOffset << std::endl;
	std::cout << "MiscSize---->" << std::hex << MiscSize << std::endl;

	// �޸��������ַ
	peheader.ntHeaders->FileHeader.Characteristics |= IMAGE_FILE_RELOCS_STRIPPED;
	std::cerr << "�̶�����ַ�޸����" << std::endl;

	// OEP��ַ
	DWORD EntryPoin = peheader.optionalHeader->AddressOfEntryPoint + peheader.optionalHeader->ImageBase;
	
	// ���� E8 ��ת��ַ�� E9 ��ת��ַ
	DWORD E8FileOffset = ((FileOffset + MiscSize) + 0x8) + 0x5;
	DWORD E9FileOffset = E8FileOffset + 0x5;
	DWORD E8CALL = (DWORD_PTR)MessageBoxA_address - ((((E8FileOffset - FileOffset) + MemeryOffset)) + peheader.optionalHeader->ImageBase);
	DWORD E9JMP = EntryPoin - ((((E9FileOffset - FileOffset) + MemeryOffset)) + peheader.optionalHeader->ImageBase);
	std::cout << "E8FileOffset---->" << std::hex << E8FileOffset << std::endl;
	std::cout << "E9FileOffset---->" << std::hex << E9FileOffset << std::endl;
	std::cout << "EntryPoin------->" << std::hex << EntryPoin << std::endl;
	printf("E8CALL----> %X \nE9JMP-----> %X\n", E8CALL, E9JMP);
	
	// ����ShellCode
	*(PDWORD)(ShellCode + 9) = E8CALL;
	*(PDWORD)(ShellCode + 0xE) = E9JMP;
	
	// ȷ�� ShellCode ����λ��
	BYTE* address = ((BYTE*)fileBuffer + (FileOffset + MiscSize));
	printf("ShellCode����λ��-------->%p\n", address);
	// ����ShellCode��
	for (int i = 0; i < ShellLength; i++)
	{
		address[i] = ShellCode[i];
	}

	// ��ӡ�����Ӳ����
	std::cout << "*****************************************S����Ӳ����*****************************************" << std::endl;
	for (size_t i = 0; i < ShellLength; i++)
	{
		printf("%02X ", *(((BYTE*)fileBuffer + (FileOffset + MiscSize)) + i));
	}
	std::cout << "\n*****************************************E����Ӳ����*****************************************" << std::endl;

	// �޸�OEP,OEPʹ�õ�����Ե�ַ
	DWORD newOEP = (MiscSize + FileOffset) - FileOffset + MemeryOffset;
	std::cout << "newOEP----->" << std::hex << newOEP << std::endl;
	peheader.optionalHeader->AddressOfEntryPoint = newOEP;

	//����
	DWORD writeResult = FwritrFile(fileBuffer, ReadFileResult, (char*)filePath);
	if (writeResult != 0)
	{
		std::cout << "���̳ɹ�" << std::endl;
		return 1;
	}
}

// ��data�����ShellCode
bool AddShellCodeInData(IN LPCSTR filePath)
{
	std::cout << "MessageBoxExA_Address---->" << MessageBoxA_address << std::endl;

	if (filePath == NULL)
	{
		return 0;
	}

	// ��ȡ�ļ�
	LPVOID fileBuffer = NULL;
	DWORD ReadFileResult = ReadFile((char*)filePath, &fileBuffer);
	if (ReadFileResult == 0)
	{
		return 0;
	}

	// ��ȡPE��Ϣ
	PEHeaders peheader;
	if (!GetPEHeaders(fileBuffer, peheader))
	{
		std::cerr << "��ЧPE�ļ�" << std::endl;
		return false;
	}

	size_t NumberSections = peheader.fileHeader->NumberOfSections;
	size_t FileOffset = 0;
	size_t MemeryOffset = 0;
	size_t MiscSize = 0;
	errno_t SizeRawData = 0;
	
	
	// ��ȡ.data�ֶ�
	for (int i = 0; i < NumberSections; i++)
	{
		if (strcmp((const char*)peheader.sectionHeader[i].Name, ".data") == 0)
		{
			peheader.sectionHeader->Characteristics |= peheader.sectionHeader->Characteristics;
			FileOffset = peheader.sectionHeader[i].PointerToRawData;
			MemeryOffset = peheader.sectionHeader[i].VirtualAddress;
			MiscSize = peheader.sectionHeader[i].Misc.VirtualSize;
			SizeRawData = peheader.sectionHeader[i].SizeOfRawData;
			break;
		}
	}
	if (FileOffset == 0)
	{
		std::cerr << "δ�ҵ�.data" << std::endl;
		return 0;
	}
	if ((int)(SizeRawData - MiscSize) < ShellLength)
	{
		std::cerr << "data�հ�����ռ䲻��" << std::endl;
		return false;
	}
	std::cout << "FileOffset---->" << std::hex << FileOffset << std::endl;
	std::cout << "MemeryOffset---->" << std::hex << MemeryOffset << std::endl;
	std::cout << "MiscSize---->" << std::hex << MiscSize << std::endl;

	// �޸�Characteristics�ֶ�
	peheader.ntHeaders->FileHeader.Characteristics |= IMAGE_FILE_RELOCS_STRIPPED;
	std::cout << "Characteristics�Ѹ�Ϊ�̶���ַ" << std::endl;

	// OEP��ַ
	DWORD EntryPoin = peheader.optionalHeader->AddressOfEntryPoint + peheader.optionalHeader->ImageBase;

	// ���� E8 ��ת��ַ�� E9 ��ת��ַ
	DWORD E8FileOffset = ((FileOffset + MiscSize) + 0x8) + 0x5;
	DWORD E9FileOffset = E8FileOffset + 0x5;
	DWORD E8CALL = (DWORD_PTR)MessageBoxA_address - ((((E8FileOffset - FileOffset) + MemeryOffset)) + peheader.optionalHeader->ImageBase);
	DWORD E9JMP = EntryPoin - ((((E9FileOffset - FileOffset) + MemeryOffset)) + peheader.optionalHeader->ImageBase);
	std::cout << "E8FileOffset---->" << std::hex << E8FileOffset << std::endl;
	std::cout << "E9FileOffset---->" << std::hex << E9FileOffset << std::endl;
	std::cout << "EntryPoin------->" << std::hex << EntryPoin << std::endl;
	printf("E8CALL----> %X \nE9JMP-----> %X\n", E8CALL, E9JMP);

	// ����ShellCode
	*(PDWORD)(ShellCode + 9) = E8CALL;
	*(PDWORD)(ShellCode + 0xE) = E9JMP;

	// ȷ�� ShellCode ����λ��
	BYTE* address = ((BYTE*)fileBuffer + (FileOffset + MiscSize));
	// ����ShellCode��
	for (int i = 0; i < ShellLength; i++)
	{
		address[i] = ShellCode[i];
	}

	// ��ӡ�����Ӳ����
	std::cout << "*****************************************S����Ӳ����*****************************************" << std::endl;
	for (size_t i = 0; i < ShellLength; i++)
	{
		printf("%02X ", *(((BYTE*)fileBuffer + (FileOffset + MiscSize)) + i));
	}
	std::cout << "\n*****************************************E����Ӳ����*****************************************" << std::endl;

	// �޸�OEP,OEPʹ�õ�����Ե�ַ
	DWORD newOEP = (MiscSize + FileOffset) - FileOffset + MemeryOffset;
	std::cout << "newOEP----->" << std::hex << newOEP << std::endl;
	peheader.optionalHeader->AddressOfEntryPoint = newOEP;

	//����
	DWORD writeResult = FwritrFile(fileBuffer, ReadFileResult, (char*)filePath);
	if (writeResult != 0)
	{
		std::cout << "���̳ɹ�" << std::endl;
		return 1;
	}

	return true;
}

// ���ShellCode��Rdata��
bool AddShellCodeRdata(IN LPCSTR filePath)
{
	std::cout << "MessageBoxExA_Address---->" << MessageBoxA_address << std::endl;

	if (filePath == NULL)
	{
		return false;
	}

	// ��ȡ�ļ�
	LPVOID fileBuffer = NULL;
	DWORD ReadFileResult = ReadFile((char*)filePath, &fileBuffer);
	if (ReadFileResult == 0)
	{
		return false;
	}

	// ��ȡPE��Ϣ
	PEHeaders peheader;
	if (!GetPEHeaders(fileBuffer, peheader))
	{
		std::cerr << "��ЧPE�ļ�" << std::endl;
		return false;
	}

	size_t NumberSections = peheader.fileHeader->NumberOfSections;
	size_t FileOffset = 0;
	size_t MemeryOffset = 0;
	size_t MiscSize = 0;
	errno_t SizeRawData = 0;

	// ��ȡ.rdata�ֶ�
	for (int i = 0; i < NumberSections; i++)
	{
		if (strcmp((const char*)peheader.sectionHeader[i].Name, ".rdata") == 0)
		{
			peheader.sectionHeader[i].Characteristics |= peheader.sectionHeader->Characteristics;
			FileOffset = peheader.sectionHeader[i].PointerToRawData;
			MemeryOffset = peheader.sectionHeader[i].VirtualAddress;
			MiscSize = peheader.sectionHeader[i].Misc.VirtualSize;
			SizeRawData = peheader.sectionHeader[i].SizeOfRawData;
			break;
		}
	}
	if (FileOffset == 0)
	{
		std::cerr << "δ�ҵ�.rdata" << std::endl;
		return 0;
	}
	if ((int)(SizeRawData - MiscSize) < ShellLength)
	{
		std::cerr << "rdata�հ�����ռ䲻��" << std::endl;
		return false;
	}
	std::cout << "FileOffset---->" << std::hex << FileOffset << std::endl;
	std::cout << "MemeryOffset---->" << std::hex << MemeryOffset << std::endl;
	std::cout << "MiscSize---->" << std::hex << MiscSize << std::endl;

	// �޸�Characteristics�ֶ�
	peheader.ntHeaders->FileHeader.Characteristics |= IMAGE_FILE_RELOCS_STRIPPED;
	std::cout << "Characteristics�Ѹ�Ϊ�̶���ַ" << std::endl;

	// OEP��ַ
	DWORD EntryPoin = peheader.optionalHeader->AddressOfEntryPoint + peheader.optionalHeader->ImageBase;

	// ���� E8 ��ת��ַ�� E9 ��ת��ַ
	DWORD E8FileOffset = ((FileOffset + MiscSize) + 0x8) + 0x5;
	DWORD E9FileOffset = E8FileOffset + 0x5;
	DWORD E8CALL = (DWORD_PTR)MessageBoxA_address - ((((E8FileOffset - FileOffset) + MemeryOffset)) + peheader.optionalHeader->ImageBase);
	DWORD E9JMP = EntryPoin - ((((E9FileOffset - FileOffset) + MemeryOffset)) + peheader.optionalHeader->ImageBase);
	std::cout << "E8FileOffset---->" << std::hex << E8FileOffset << std::endl;
	std::cout << "E9FileOffset---->" << std::hex << E9FileOffset << std::endl;
	std::cout << "EntryPoin------->" << std::hex << EntryPoin << std::endl;
	printf("E8CALL----> %X \nE9JMP-----> %X\n", E8CALL, E9JMP);

	// ����ShellCode
	*(PDWORD)(ShellCode + 9) = E8CALL;
	*(PDWORD)(ShellCode + 0xE) = E9JMP;

	// ȷ�� ShellCode ����λ��
	BYTE* address = ((BYTE*)fileBuffer + FileOffset + MiscSize);
	// ����ShellCode��
	for (int i = 0; i < ShellLength; i++)
	{
		address[i] = ShellCode[i];
	}

	// ��ӡ�����Ӳ����
	std::cout << "*****************************************S����Ӳ����*****************************************" << std::endl;
	for (size_t i = 0; i < ShellLength; i++)
	{
		printf("%02X ", *(((BYTE*)fileBuffer + (FileOffset + MiscSize)) + i));
	}
	std::cout << "\n*****************************************E����Ӳ����*****************************************" << std::endl;

	// �޸�OEP,OEPʹ�õ�����Ե�ַ
	DWORD newOEP = (MiscSize + FileOffset) - FileOffset + MemeryOffset;
	std::cout << "newOEP----->" << std::hex << newOEP << std::endl;
	peheader.optionalHeader->AddressOfEntryPoint = newOEP;

	//����
	DWORD writeResult = FwritrFile(fileBuffer, ReadFileResult, (char*)filePath);
	if (writeResult != 0)
	{
		std::cout << "���̳ɹ�" << std::endl;
		return true;
	}

	return true;
}

// �÷�������һ���ڲ����ShellCode
bool AddSection(IN LPCSTR filePath)
{
	if (filePath == nullptr)
	{
		std::cerr << "Error: ��������" << std::endl;
		return false;
	}
	
	LPVOID fileBuffer = NULL;
	errno_t ReadFileResult = ReadFile((char*)filePath, &fileBuffer);
	if (ReadFileResult == 0) 
	{
		std::cerr << "Error: ��ȡ�ļ�ʧ��" << std::endl;
		return false;
	}

	if (DEBUG == 1) for (size_t i = 0; i < 0x20; i++) printf("%X ", *((BYTE*)fileBuffer + i));
	
	// ��ȡPE��Ϣ
	PEHeaders peheaders;
	bool PeResult = GetPEHeaders(fileBuffer, peheaders);
	if (PeResult == 0)
	{
		std::cerr << "Error: ��ȡPEͷ��Ϣʧ��" << std::endl;
		return false;
	}

	// �޸��������ַ
	peheaders.ntHeaders->FileHeader.Characteristics |= IMAGE_FILE_RELOCS_STRIPPED;
	std::cerr << "�̶�����ַ�޸����" << std::endl;
	
	// �ļ���С���ļ�β��������
	size_t fileSize = peheaders.optionalHeader->SizeOfHeaders;
	size_t NumberSection = peheaders.fileHeader->NumberOfSections;
	size_t FileOffset = 0, MemeryOffset = 0, MiscSize = 0;
	DWORD SizeRawData = 0;

	for (size_t i = 0; i < NumberSection; i++)
	{
		fileSize += peheaders.sectionHeader[i].SizeOfRawData;
		if (i == NumberSection - 1)
		{
			FileOffset = peheaders.sectionHeader[i].PointerToRawData;
			MemeryOffset = peheaders.sectionHeader[i].VirtualAddress;
			MiscSize = peheaders.sectionHeader[i].Misc.VirtualSize;
			SizeRawData = peheaders.sectionHeader[i].SizeOfRawData;
			std::cout << "Name---->" << peheaders.sectionHeader[i].Name << std::endl;
		}
	}
	
	printf("�ļ�ԭʼ��С------> %X \n", fileSize);
	if (fileSize < ReadFileResult)
	{
		std::cerr << "�ļ�β����δ֪���ݣ�Ϊ������ļ���ȫ����������" << std::endl;
		return 0;
	}

	// �����Ϣ
	unsigned char hexData[40] = {
		0x2E, 0x74, 0x65, 0x78, 0x74, 0x00, 0x00, 0x00,  0x9A, 0xBA, 0x01, 0x00,  0x00, 0x10, 0x00, 0x00,
		0x00, 0xC0, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x60
	};
	unsigned char Name[] = { 0x47,0x61, 0x47,0x61 };

	// ���·����ڴ��԰���׷�ӵ��ֽ�
	size_t newSize = fileSize + AddByte;
	printf("�ļ����´�С------> %X \n", newSize);

	unsigned char* newBuffer = (unsigned char*)realloc(fileBuffer, newSize);
	if (!newBuffer) {
		perror("�ڴ�������");
		return false;
	}
	memset(newBuffer + fileSize, 0, AddByte);

	// ����PE��Ϣ;
	PEHeaders newPeHeaders;
	if (!GetPEHeaders(newBuffer, newPeHeaders)) {
		std::cerr << "Error: ����PEͷ��Ϣʧ��" << std::endl;
		free(newBuffer);
		return false;
	}

	size_t newFileOffset = 0, newMemeryOffset = 0, newMiscSize = 0;
	DWORD newSizeRawData = 0;

	size_t newNumberSeciton = newPeHeaders.fileHeader->NumberOfSections;
	for (size_t i = 0; i < newNumberSeciton; i++)
	{
		if (i == newNumberSeciton - 1)
		{
			newFileOffset = newPeHeaders.sectionHeader[i].PointerToRawData;
			newMemeryOffset = newPeHeaders.sectionHeader[i].VirtualAddress;
			newMiscSize = newPeHeaders.sectionHeader[i].Misc.VirtualSize;
			newSizeRawData = newPeHeaders.sectionHeader[i].SizeOfRawData;
		}
	}

	if (DEBUG == 1)
	{
		std::cout << "newFileOffset----> " << std::hex << newFileOffset << std::endl;
		std::cout << "newMemeryOffset----> " << std::hex << newMemeryOffset << std::endl;
		std::cout << "newMiscSize-------> " << std::hex << newMiscSize << std::endl;
		std::cout << "newSizeRawData-------> " << std::hex << newSizeRawData << std::endl;
	}
	
	// �����ڱ�
	// ȷ��λ��
	DWORD addByte = AddByte;
	
	// �����ڴ�ƫ�ƺ��ļ�ƫ��
	DWORD VirtualAddress = newMiscSize + newMemeryOffset;
	if (VirtualAddress % (newPeHeaders.optionalHeader->SectionAlignment) != 0) align_1000(VirtualAddress);
	std::cout << "NewSection----> VirtualAddress----> " << std::hex << VirtualAddress << std::endl;
	DWORD PointerToRawData = newFileOffset + newSizeRawData;
	std::cout << "NewSection----> PointerToRawData--> " << std::hex << PointerToRawData << std::endl;

	// ����hexData
	memcpy_s(&hexData[1], sizeof(Name), Name, sizeof(Name));
	memcpy_s(&hexData[8], sizeof(addByte), &addByte, sizeof(addByte));
	memcpy_s(&hexData[12], sizeof(VirtualAddress), &VirtualAddress, sizeof(VirtualAddress));
	memcpy_s(&hexData[16],sizeof(addByte), &addByte,sizeof(addByte));
	memcpy_s(&hexData[20],sizeof(PointerToRawData), &PointerToRawData, sizeof(PointerToRawData));

	printf("********************************�ڱ���Ϣ*********************************\n");
	for (int i = 0; i < 0x28; i++)
	{
		printf("%02X ", hexData[i]);
	}
	printf("\n");

	// ����ڱ�
	DWORD address = (newPeHeaders.dosHeader->e_lfanew + 0x04 + IMAGE_SIZEOF_FILE_HEADER + newPeHeaders.fileHeader->SizeOfOptionalHeader + newPeHeaders.fileHeader->NumberOfSections * 0x28);
	BYTE* sectionAddres = (BYTE*)newBuffer + address;
	if (DEBUG == 1)
	{
		std::cout << "�����ڱ�ƫ��--------> " << address << std::endl;
		std::cout << "�����ڱ�λ��--------> " << (void*)sectionAddres << std::endl;
	}
	
	// ���ݲ���
	for (size_t i = 0; i < 0x28; i++)
	{
		sectionAddres[i] = hexData[i];
	}

	// �޸�PE��Ϣ
	newPeHeaders.fileHeader->NumberOfSections += 0x1;
	newPeHeaders.optionalHeader->SizeOfImage += 0x1000;

	// OEP��ַ
	DWORD EntryPoin = newPeHeaders.optionalHeader->AddressOfEntryPoint + newPeHeaders.optionalHeader->ImageBase;

	// ���� E8 ��ת��ַ�� E9 ��ת��ַ
	DWORD E8FileOffset = (PointerToRawData + 0x8) + 0x5;
	DWORD E9FileOffset = E8FileOffset + 0x5;
	DWORD E8CALL = (DWORD_PTR)MessageBoxA_address - ((((E8FileOffset - PointerToRawData) + VirtualAddress)) + newPeHeaders.optionalHeader->ImageBase);
	DWORD E9JMP = EntryPoin - ((((E9FileOffset - PointerToRawData) + VirtualAddress)) + newPeHeaders.optionalHeader->ImageBase);

	if (DEBUG == 1)
	{
		std::cout << "E8FileOffset----> " << std::hex << E8FileOffset << std::endl;
		std::cout << "E9FileOffset----> " << std::hex << E9FileOffset << std::endl;
		std::cout << "EntryPoin-------> " << std::hex << EntryPoin << std::endl;
		printf("E8CALL----> %X \nE9JMP-----> %X\n", E8CALL, E9JMP);
	}
	
	// ����ShellCode
	*(PDWORD)(ShellCode + 9) = E8CALL;
	*(PDWORD)(ShellCode + 0xE) = E9JMP;

	// ȷ�� ShellCode ����λ��
	BYTE* Newaddress = ((BYTE*)newBuffer + fileSize);
	// ����ShellCode��
	for (int i = 0; i < ShellLength; i++)
	{
		Newaddress[i] = ShellCode[i];
	}

	// ����OEP
	DWORD newOEP = (fileSize - PointerToRawData) + VirtualAddress;
	newPeHeaders.optionalHeader->AddressOfEntryPoint = newOEP;
	if (DEBUG == 1)
	{
		std::cerr << "fileSize--------> " << fileSize << std::endl;
		std::cout << "newOEP-----> " << std::hex << newOEP << std::endl;
	}
	

	// ����
	FwritrFile(newBuffer, newSize, (char*)filePath);
	free(newBuffer);
	return true;
}

// ��չ��
bool ExpandSection(IN LPCSTR filePath)
{
	if (filePath == NULL)
	{
		perror("Para Error");
		return false;
	}

	// ��ȡ�ļ�
	LPVOID fileBufer = nullptr;
	size_t readFileReuslt = ReadFile((char*)filePath, &fileBufer);
	if (readFileReuslt == 0)
	{
		perror("ReadFile Error");
		return false;
	}

	// PE��Ϣ
	PEHeaders peheader;
	if (!GetPEHeaders(fileBufer,peheader))
	{
		perror("PE Info Error");
		return false;
	}

	// �̶�����ַ
	peheader.fileHeader->Characteristics |= IMAGE_FILE_RELOCS_STRIPPED;
	if (DEBUG) std::cerr << "����ַ�ѹ̶�" << std::endl;


	// �ļ���ʵ��С,���һ��
	long FileSize = peheader.optionalHeader->SizeOfHeaders;
	size_t numberSection = peheader.fileHeader->NumberOfSections;

	//���һ���ֶ�����
	size_t FileOffset = 0, MemeryOffset = 0, MiscSize = 0;
	errno_t sizeData = 0;

	// ʹ��ѭ����ȡ�����һ��
	for (size_t i = 0; i < numberSection; i++)
	{
		FileSize += peheader.sectionHeader[i].SizeOfRawData;
		if (i == numberSection - 1)
		{
			FileOffset = peheader.sectionHeader[i].PointerToRawData;
			MemeryOffset = peheader.sectionHeader[i].VirtualAddress;
			MiscSize = peheader.sectionHeader[i].Misc.VirtualSize;
			sizeData = peheader.sectionHeader[i].SizeOfRawData;
			//std::cout << "SectionName-------> " << peheader.sectionHeader[i].Name << std::endl;
			break;
		}
	}
	if (DEBUG)
	{
		std::cout << "FileOffset--------> " << std::hex << FileOffset << std::endl;
		std::cout << "MemeryOffset------> " << std::hex << MemeryOffset << std::endl;
		std::cout << "MiscSize----------> " << std::hex << MiscSize << std::endl;
		std::cout << "sizeData----------> " << std::hex << sizeData << std::endl;
		std::cout << "FileSize----------> " << std::hex << FileSize << std::endl;
	}
	
	if (FileSize < readFileReuslt)
	{
		perror("ע��:ĩβ��β���ж�������,Ϊ�������ļ���ȫ������չ��");
		return false;
	}

	// ��β
	DWORD EndSectionAddress = FileOffset + sizeData;
	if(DEBUG) std::cout << "EndSectionAddress---->" << EndSectionAddress << std::endl;

	// ��չ0x200�ֽ�
	DWORD newBufferSize = readFileReuslt + 0x200;
	unsigned char* newBuffer = (unsigned char*)realloc(fileBufer, newBufferSize);
	if (newBuffer == NULL)
	{
		perror("malloc error");
		return false;
	}
	memset(newBuffer + readFileReuslt, 0, 0x200);

	// ����PE��Ϣ
	PEHeaders newPeheader;
	if (!GetPEHeaders(newBuffer, newPeheader))
	{
		return false;
	}

	//���һ���ֶ�����
	long newFileSize = newPeheader.optionalHeader->SizeOfHeaders;
	size_t newNumbersection = newPeheader.fileHeader->NumberOfSections;
	size_t newFileOffset = 0, newMemeryOffset = 0, newMiscSize = 0;
	errno_t newsizeData = 0;

	// ʹ��ѭ����ȡ�����һ��
	size_t j = 0;
	for ( j = 0; j < newNumbersection; j++)
	{
		newFileSize += newPeheader.sectionHeader[j].SizeOfRawData;
		if (j == numberSection - 1)
		{
			newFileOffset = newPeheader.sectionHeader[j].PointerToRawData;
			newMemeryOffset = newPeheader.sectionHeader[j].VirtualAddress;
			newMiscSize = newPeheader.sectionHeader[j].Misc.VirtualSize;
			newsizeData = newPeheader.sectionHeader[j].SizeOfRawData;
			//std::cout << "SectionName-------> " << peheader.sectionHeader[j].Name << std::endl;
			break;
		}
	}

	// �����ڱ�����
	newPeheader.sectionHeader[j].Characteristics |= newPeheader.sectionHeader->Characteristics;
	if (DEBUG) std::cout << "�ڱ��Ѹ�Ϊ��ִ��" << std::endl;
	
	newPeheader.sectionHeader[j].SizeOfRawData += 0x200;
	newPeheader.sectionHeader[j].Misc.VirtualSize += 0x200;
	newPeheader.optionalHeader->SizeOfImage += 0x200;

	// ShellCodeλ��
	BYTE* shellCodeAddress = (BYTE*)newBuffer + newFileSize;

	// ����E8 E9
	DWORD OepAddress = newPeheader.optionalHeader->AddressOfEntryPoint + newPeheader.optionalHeader->ImageBase;
	DWORD E8OFFSET = ((DWORD)EndSectionAddress + 0x8) + 0x5;
	DWORD E9OFFSET = E8OFFSET + 0x5;
	DWORD E8_VA = (((E8OFFSET - newFileOffset) + newMemeryOffset) + newPeheader.optionalHeader->ImageBase);
	DWORD E9_VA = (((E9OFFSET - newFileOffset) + newMemeryOffset) + newPeheader.optionalHeader->ImageBase);
	DWORD E8CALL = (DWORD)MessageBoxA_address - (((E8OFFSET - newFileOffset) + newMemeryOffset) + newPeheader.optionalHeader->ImageBase);
	DWORD E9JMP = OepAddress - (((E9OFFSET - newFileOffset) + newMemeryOffset) + newPeheader.optionalHeader->ImageBase);

	if (DEBUG)
	{
		std::cout << "E8_VA-------> " << std::hex << E8_VA << std::endl;
		std::cout << "E9_VA-------> " << std::hex << E9_VA << std::endl;
		std::cout << "E8OFFSET----> " << std::hex << E8OFFSET << std::endl;
		std::cout << "E9OFFSET----> " << std::hex << E9OFFSET << std::endl;
		std::cout << "OepAddress-------> " << std::hex << OepAddress << std::endl;
		printf("E8CALL----> %X \nE9JMP-----> %X\n", E8CALL, E9JMP);
	}
	

	// ����ShellCode
	*(LPDWORD)(ShellCode + 9) = E8CALL;
	*(LPDWORD)(ShellCode + 0xE) = E9JMP;

	// ���ShellCode
	for (size_t i = 0; i < ShellLength; i++)
	{
		shellCodeAddress[i] = ShellCode[i];
	}

	// ����OEP
	DWORD newOEP = (newFileSize - newFileOffset) + newMemeryOffset;
	newPeheader.optionalHeader->AddressOfEntryPoint = newOEP;
	if (DEBUG == 1)
	{
		std::cerr << "fileSize--------> " << newFileSize << std::endl;
		std::cout << "newOEP-----> " << std::hex << newOEP << std::endl;
	}
	

	// ����
	DWORD writeResult = FwritrFile(newBuffer, newBufferSize, (char*)filePath);

	return true;
}

// ��ӡ����Ŀ¼
bool ImageData(IN LPCSTR filePath)
{
	if (filePath == NULL)
	{
		perror("ParrError");
		return false;
	}

	// ��ȡ�ļ�
	LPVOID fileBuffer = NULL;
	DWORD readFileResult = ReadFile((char*)filePath, &fileBuffer);
	if (readFileResult == 0)	return false;

	// PE��Ϣ
	//_IMAGE_DATA_DIRECTORY
	PEHeaders peheader;
	if (!GetPEHeaders(fileBuffer, peheader))	return false;
	std::cout << "����Ŀ¼��С----> " << peheader.optionalHeader->NumberOfRvaAndSizes << std::endl;
	PIMAGE_DATA_DIRECTORY data = (PIMAGE_DATA_DIRECTORY)&peheader.optionalHeader->DataDirectory;
	std::cout << "********************RVA******************" << std::endl;
	for (size_t i = 0; i < peheader.optionalHeader->NumberOfRvaAndSizes; i++)
	{
		printf("%08X\n", (DWORD)data[i].VirtualAddress);
	}

	std::cout << "********************Size******************" << std::endl;
	for (size_t i = 0; i < peheader.optionalHeader->NumberOfRvaAndSizes; i++)
	{
		printf("%08X\n", data[i].Size);
	}
	return true;
}

// �ϲ���
bool MergeSection(IN LPCSTR filePath)
{
	if (filePath == NULL)	return false;

	LPVOID fileBuffer = nullptr;
	if (!ReadFile((char*)filePath, &fileBuffer))	return false;

	LPVOID ImageBuffer = nullptr;
	if (!CopyFileBufferToImageBuffer(fileBuffer, &ImageBuffer))	return false;

	PEHeaders peheader;
	if (!GetPEHeaders(ImageBuffer, peheader))	return false;
	
	DWORD VS = peheader.optionalHeader->SizeOfImage - peheader.sectionHeader->VirtualAddress;
	//DWORD S = peheader.optionalHeader->SizeOfImage - peheader.optionalHeader->SizeOfHeaders;
	//std::cout << "VS " << VS  << std::endl;
	DWORD SR = VS;

	peheader.sectionHeader->Misc.VirtualSize = VS;
	peheader.sectionHeader->SizeOfRawData = SR;
	peheader.sectionHeader->Characteristics |= 0xFFFFFFFF;
	peheader.fileHeader->NumberOfSections = 0x1;

	LPVOID newBuffer = NULL;
	if (!CopyImageBufferToNewBuffer(ImageBuffer, &newBuffer))	return false;

	FwritrFile(newBuffer, VS + peheader.optionalHeader->SizeOfHeaders, (char*)filePath);
	return true;
}

// �ļ���·��
LPCSTR newFilePathName(LPCSTR filepath)
{
	if (filepath == NULL)
	{
		return 0;
	}
	size_t len = strlen(filepath);
	char* newFilePath = (char*)malloc(len + 5);
	if (newFilePath == NULL)
	{
		return 0;
	}
	memset(newFilePath, 0, len + 5);
	strcpy_s(newFilePath, len + 5, filepath);
	char* newPath = strstr(newFilePath, ".dll");
	if (newPath != NULL) {
		strcpy_s(newPath, strlen("_new.dll") + 1, "_new.dll");
	}
	return newFilePath;
}

// д���ļ�
DWORD FwritrFile(IN LPVOID buffer, IN size_t size, OUT LPCSTR filePath)
{
	const char* newFilePath = newFilePathName(filePath);

	if (filePath == NULL || buffer == NULL || size == NULL)
	{
		return 0;
	}

	FILE* file = NULL;
	fopen_s(&file, newFilePath, "wb");

	if (file == NULL)
	{
		std::cout << "д���ļ�ʧ��" << std::endl;
		free((void*)newFilePath);
		return 0;
	}

	size_t result = fwrite((unsigned char*)buffer, 1, size, file);
	if (result == size)
	{
		std::cout << "д��ɹ�,д���ֽ���:" << std::hex << result << std::endl;
		std::cout << "д���ļ�λ��:" << newFilePath << std::endl;
	}

	fclose(file);
	free((void*)newFilePath);
	return result;
}