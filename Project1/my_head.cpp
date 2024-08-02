#include "my_head.h"

#define FALSE 0
#define TRUE 1
#define DEBUG 1
#define PRINTFLOGSTRING(VALUES) if((DEBUG) == 1){printf("%s\n",VALUES);}
#define PRINTFLOG(VALUES) if((DEBUG) == 1){printf("VALUES--->%x\n",VALUES);}


const char PE[] = {
	0x4D,0x5A
};

void *openFile(FILE** _Stream, const char* FileName, const char* Mode)
{
	if (_Stream == NULL || FileName == NULL || Mode ==NULL)
	{
		PRINTFLOGSTRING("��������");
		return FALSE;
	}
	errno_t result = fopen_s(_Stream, FileName, Mode);
	if (result != 0)
	{
		PRINTFLOGSTRING("��ʧ��");
		return FALSE;
	}
	PRINTFLOG(*_Stream);
}


size_t GetFileSize(FILE* stream)
{
	if (stream == NULL)
	{
		PRINTFLOGSTRING("��������");
		return FALSE;
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
		PRINTFLOGSTRING("��������");
		return FALSE;
	}
	// �����ڴ�
	unsigned char* FileSpaceSize = (unsigned char*)malloc(FileSize);
	// ��ʼ���ڴ�
	memset(FileSpaceSize, 0, FileSize);

	size_t result = fread_s(FileSpaceSize, FileSize, elemensize, FileSize, stream);
	if (result != FileSize)
	{
		PRINTFLOG(result);
		PRINTFLOGSTRING("��ȡ����ʧ�ܣ�����");
		free(FileSpaceSize);
		return FALSE;
	}
	else
	{
		PRINTFLOG(result);
	}
	return FileSpaceSize;
}

int CheckPE(unsigned char* buuferFile)
{
	if (memcmp(buuferFile, PE, sizeof(PE)) == 0) {
		PRINTFLOGSTRING("��PE�ļ�");
		return TRUE;
	}
	else {
		PRINTFLOGSTRING("����PE�ļ�");
		return FALSE;
	}
	return 0;
}
