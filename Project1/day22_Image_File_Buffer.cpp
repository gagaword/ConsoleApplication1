#include"day22.h"

#define FILEPATH "C:\\Users\\GaGa\\Desktop\\A.exe"

int main()
{
	LPVOID FileData = NULL;
	DWORD result = ReadFile(FILEPATH, &FileData);	

	unsigned char* temp = (unsigned char*)FileData;
	if (result == 0)
	{
		std::cout << "��ȡ����" << std::endl;
	}
	
	LPVOID ImageBuffer = NULL;
	DWORD CopyResult = CopyFileBufferToImageBuffer(FileData, &ImageBuffer);

	return 0;
}