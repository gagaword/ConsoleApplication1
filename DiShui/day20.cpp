#include<iostream>	
#include<stdio.h>
#include<Windows.h>

#define DEBUG 1
//#define notepadPath "C:\\Windows\\system32\\notepad.exe"
#define notepadPath "C:\\Users\\GaGa\\Desktop\\eee.exe"


#define PRINTFLOG(DE,dest) if ((DE) == 1){ printf("%x\n",(dest));}
#define FALSE 0;

//constexpr auto notepadPath = "C:\\Windows\\system32\\notepad.exe";

/*
	errno_t fopen_s(
		FILE** pFile,
		const char *filename,
		const char *mode
);
*/

int main()
{
	// notepad�����������ָ���ļ�ָ���ָ��
	// ˵���˾��Ƕ���ָ��

	FILE* notepad = NULL;

	// ���ļ�
	errno_t err = fopen_s(&notepad, notepadPath, "rb");

	if (err == 0) {
		printf("notepda���������:%p\n", notepad);
	}
	else {
		printf("Failed to open file: %s\n", notepadPath);
	}

	// ����notepadָ��ָ���ļ�β
	fseek(notepad,0, SEEK_END);
	long ftellResult =  ftell(notepad);

	// ��ӡ��ftellResult�Ľ��
	PRINTFLOG(DEBUG, ftellResult);

	// ����notepadָ��ָ���ļ�ͷ����ͨ��ftell��ȡ���ļ���С���ٰ�notepadָ��ָ���ļ�ͷ����Ȼ����Ķ�ȡ�����
	fseek(notepad, 0, SEEK_SET);

	/*if (DEBUG == 1)
	{
		printf("%d", ftellResult);
	}*/

	
	// �����ڴ�ռ�
	unsigned char* notepadSpace = (unsigned char*)malloc(ftellResult);
	if (notepadSpace == NULL)
	{
		printf("Space Error");
		free(notepad);
		return FALSE;
	}

	// ��ȡ���ݣ�fread_s���ض�ȡ�����ֽ������������ֵ������ftellResult����ô��ʾ��ȡ������ȡʧ��
	size_t readNotepad = fread_s(notepadSpace, ftellResult, 1, ftellResult,notepad);
	if (readNotepad != ftellResult)
	{
		printf("read notepad.exe error\n");
		return FALSE;
	}

	// �ر��ļ�
	fclose(notepad);

	// ��ӡ��ַ
	printf("Addres---->%p\n", notepadSpace);

	unsigned char* temp = notepadSpace; // ʹ��һ����ʱָ��������
	int count = 0;

	for (int i = 0; i < 200; i++) 
	{
		printf("%-4x ", *(temp++));
		count++;
		if (count == 16)
		{
			printf("\n");
			count = 0;
		}
	}

	printf("\n--------------------\n");
	// �ͷ��ڴ�
	//free(notepadSpace);

	// ��Ŀ���ļ�
	FILE* dest = NULL;
	errno_t destExe = fopen_s(&dest, "test1.exe", "wb");
	// д��Ŀ���ļ�
	size_t destNumber = fwrite(notepadSpace, 1, ftellResult, dest);
	printf("%x\n", destNumber);
	fclose(dest);
	free(notepadSpace);

	return 0;
}
