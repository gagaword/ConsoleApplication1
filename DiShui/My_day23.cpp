#include "My_day23.h"

// MessageBoxA��ַ
void* MessageBoxA_address = &MessageBoxA;

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
DWORD ReadFile(IN const char* filepath, OUT LPVOID* fileBuffer)
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

	std::cout << "�ļ��ֽ�:" << fileSize << std::endl;

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
	std::cout << "��ȡ�ֽ�:" << freadResult << std::endl;
	return freadResult;
}


// ����ShellCode
DWORD AddShellCode(IN LPVOID filePath)
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
	if (!GetPEHeaders(fileBuffer,peheader))
	{
		std::cerr << "��ЧPE�ļ�" << std::endl;
		return false;
	}

	size_t NumberSections = peheader.fileHeader->NumberOfSections;
	size_t FileOffset = 0;
	size_t MemeryOffset = 0;
	size_t MiscSize = 0;

	// �޸�Characteristics�ֶ�
	peheader.ntHeaders->FileHeader.Characteristics |= IMAGE_FILE_RELOCS_STRIPPED;
	std::cout << "Characteristics�޸����" << std::endl;

	// ��ȡ.text�ֶ�
	for (int i = 0; i < NumberSections; i++)
	{
		if (strcmp((const char*)peheader.sectionHeader[i].Name,".text") == 0)
		{
			FileOffset = peheader.sectionHeader[i].PointerToRawData;
			MemeryOffset = peheader.sectionHeader[i].VirtualAddress;
			MiscSize = peheader.sectionHeader[i].Misc.VirtualSize;
			break;
		}
	}
	if (FileOffset == 0)
	{
		std::cerr << "δ�ҵ�.text" << std::endl;
		return 0;
	}

	std::cout << "FileOffset---->" << std::hex << FileOffset << std::endl;
	std::cout << "MemeryOffset---->" << std::hex << MemeryOffset << std::endl;
	std::cout << "MiscSize---->" << std::hex << MiscSize << std::endl;

	// OEP��ַ
	DWORD EntryPoin = peheader.optionalHeader->AddressOfEntryPoint + peheader.optionalHeader->ImageBase;
	
	// Ӳ����
	char ShellCode[] = { 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00 };
	int ShellLength = sizeof(ShellCode) / sizeof(ShellCode[0]);

	// ���� E8 ��ת��ַ�� E9 ��ת��ַ
	DWORD E8FileOffset = ((FileOffset + MiscSize) + 0x8) + 0x5;
	DWORD E9FileOffset = E8FileOffset + 0x5;
	DWORD E8CALL = (DWORD_PTR)MessageBoxA_address - ((((E8FileOffset - FileOffset) + MemeryOffset)) + peheader.optionalHeader->ImageBase);
	DWORD E9JMP = EntryPoin - ((((E9FileOffset - FileOffset) + MemeryOffset)) + peheader.optionalHeader->ImageBase);
	std::cout << "E8FileOffset---->" << std::hex << E8FileOffset << std::endl;
	std::cout << "E9FileOffset---->" << std::hex << E9FileOffset << std::endl;
	std::cout << "EntryPoin------->" << std::hex << EntryPoin << std::endl;
	printf("E8CALL----> %X \nE9JMP-----> %X\n", E8CALL, E9JMP);
	

	// ��E8CALL��ÿ���ֽ������ӵ�ShellCode��ĩβ
	ShellCode[9] = (E8CALL >> 0) & 0xFF; 
	ShellCode[10] = (E8CALL >> 8) & 0xFF;
	ShellCode[11] = (E8CALL >> 16) & 0xFF;
	ShellCode[12] = (E8CALL >> 24) & 0xFF;
	
	// ��E9JMp��ÿ���ֽ������ӵ�ShellCode��ĩβ
	ShellCode[14] = (E9JMP >> 0) & 0xFF; 
	ShellCode[15] = (E9JMP >> 8) & 0xFF; 
	ShellCode[16] = (E9JMP >> 16) & 0xFF;
	ShellCode[17] = (E9JMP >> 24) & 0xFF;


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
}

// ·��������
const char* newFilePathName(const char* filepath)
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
	char* newPath = strstr(newFilePath, ".exe");
	if (newPath != NULL) {
		strcpy_s(newPath, strlen("_new.exe") + 1, "_new.exe");
	}
	return newFilePath;
}

// д��Ӳ��
DWORD FwritrFile(IN LPVOID buffer, IN size_t size, OUT const char* filePath)
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
		std::cout << "д��ɹ�,д���ֽ���:" << std::dec <<  result << std::endl;
		std::cout << "д���ļ�λ��:" << newFilePath << std::endl;
	}

	fclose(file);
	free((void*)newFilePath);
	return result;
}
