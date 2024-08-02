#include "my_head.h"

#define FALSE 0

void *openFile(FILE** _Stream, const char* FileName, const char* Mode)
{
	if (_Stream == NULL || FileName == NULL || Mode ==NULL)
	{
		std::cout << "��������" << std::endl;
		return FALSE;
	}
	errno_t result = fopen_s(_Stream, FileName, Mode);
	if (result != 0)
	{
		std::cout << "��ʧ��" << std::endl;
	}
}


size_t GetFileSize(FILE* stream)
{
	if (stream == NULL)
	{
		std::cout << "��������" << std::endl;
	}
	long FileSize = 0;
	fseek(stream,0,SEEK_END);
	FileSize = ftell(stream);
	fseek(stream, 0, SEEK_SET);
	return FileSize;
}

void* ReadFileData(long FileSize, size_t elemensize, FILE* stream)
{
	if (FileSize == NULL || elemensize == NULL || stream == NULL)
	{
		std::cout << "��������!!!!" << std::endl;
	}
	// �����ڴ�
	unsigned char* FileSpaceSize = (unsigned char*)malloc(FileSize);
	// ��ʼ���ڴ�
	memset(FileSpaceSize, 0, FileSize);

	size_t result = fread_s(FileSpaceSize, FileSize, elemensize, FileSize, stream);
	if (result != FileSize)
	{
		std::cout << "��ȡ�����ֽ�---->" << result << std::endl;
		std::cout << "��ȡ����ʧ�ܣ�����" << std::endl;
		free(FileSpaceSize);
		return FALSE;
	}
	else
	{
		std::cout << "��ȡ�����ֽ�---->" << result << std::endl;
	}
	return FileSpaceSize;
}
