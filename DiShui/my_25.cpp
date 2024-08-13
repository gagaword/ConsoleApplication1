#include "my_25.h"
#include "My_day23.h"

bool GetPeheadersInfo(LPVOID Buffer, PEHeaders peheader)
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

	// FILE Header
	peheader.fileHeader = &peheader.ntHeaders->FileHeader;

	// OPTION Header
	peheader.optionalHeader = &peheader.ntHeaders->OptionalHeader;

	// SECTIOn Header
	peheader.sectionHeader = (PIMAGE_SECTION_HEADER)((BYTE*)peheader.optionalHeader + peheader.fileHeader->SizeOfOptionalHeader);

	return false;
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
	return false;
}
