#include "my_head.h"

#define FALSE 0
#define TRUE 1
#define DEBUG 1
#define PRINTFLOGSTRING(FunName,VALUES) if((DEBUG) == 1){printf("%s-------->%s\n", FunName, VALUES);}
#define PRINTFLOG(FunName,VALUES) if((DEBUG) == 1){printf("%s-------->%x\n", FunName, VALUES);}

const char PE[] = {
	0x4D,0x5A
};

int openFile(FILE** _Stream, const char* FileName, const char* Mode)
{
	if (_Stream == NULL || FileName == NULL || Mode ==NULL)
	{
		PRINTFLOGSTRING(__func__, "��������");
		return FALSE;
	}
	errno_t result = fopen_s(_Stream, FileName, Mode);
	if (result != 0)
	{
		PRINTFLOGSTRING(__func__,"��ʧ��");
		return FALSE;
	}
	PRINTFLOG(__func__, *(_Stream));
	return TRUE;
}

size_t GetFileSize(FILE* stream)
{
	if (stream == NULL)
	{
		PRINTFLOGSTRING(__func__, "��������");
		return FALSE;
	}
	long FileSize = 0;
	fseek(stream,0,SEEK_END);
	FileSize = ftell(stream);
	fseek(stream, 0, SEEK_SET);
	PRINTFLOG(__func__, FileSize);
	return FileSize;
}

void* ReadFileData(long FileSize, size_t elemensize, FILE* stream)
{
	if (FileSize == NULL || elemensize == NULL || stream == NULL)
	{
		PRINTFLOGSTRING(__FUNCSIG__, "��������");
		return FALSE;
	}
	// �����ڴ�
	unsigned char* FileSpaceSize = (unsigned char*)malloc(FileSize);
	if (FileSpaceSize == NULL)
	{
		PRINTFLOGSTRING(__func__, "�����ڴ����");
	}

	// ��ʼ���ڴ�
	memset(FileSpaceSize, 0, FileSize);

	size_t result = fread_s(FileSpaceSize, FileSize, elemensize, FileSize, stream);
	if (result != FileSize)
	{
		PRINTFLOG(__func__, result);
		PRINTFLOGSTRING(__func__, "��ȡ����ʧ�ܣ�����");
		free(FileSpaceSize);
		return FALSE;
	}
	else
	{
		PRINTFLOGSTRING(__func__, "��ȡ�ɹ�!!!!");
		PRINTFLOG(__func__, result);
		return FileSpaceSize;
	}
}

int CheckPE(unsigned char* buuferFile)
{
	if (memcmp(buuferFile, PE, sizeof(PE)) == 0) {
		PRINTFLOGSTRING(__func__, "��PE�ļ�");
		return TRUE;
	}
	else {
		PRINTFLOGSTRING(__func__, "����PE�ļ�");
		return FALSE;
	}
	return 0;
}

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
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char* FileSpace = (unsigned char*)malloc(fileSize);
	if (FileSpace == NULL)
	{
		std::cout << "�����ڴ����" << std::endl;
		fclose(file);
		return NULL;
	}
	memset(FileSpace, 0, fileSize);
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