#include"day22.h"

#define FILEPATH "D:\\PE\\PETool 1.0.0.5.exe"

int main()
{
    LPVOID FileBuffer = NULL;
    DWORD fileSize = ReadFile(FILEPATH, &FileBuffer);

    if (fileSize == 0 || FileBuffer == NULL) {
        std::cerr << "��ȡ�ļ�����" << std::endl;
        return 1;
    }

    std::cout << "��ȡ�ֽ���: " << fileSize << std::endl;

    LPVOID ImageBuffer = NULL;
    DWORD imageBufferSize = CopyFileBufferToImageBuffer(FileBuffer, &ImageBuffer);
    if (imageBufferSize == 0 || ImageBuffer == NULL) {
        std::cerr << "�����ļ���ImageBufferʧ��" << std::endl;
        free(FileBuffer);
        return 1;
    }

    std::cout << "���Ƴɹ�, �����ֽ���: " << imageBufferSize << std::endl;

    LPVOID NewBuffer = NULL;
    DWORD newBufferSize = CopyImageBufferToNewBuffer(ImageBuffer, &NewBuffer);
    if (newBufferSize == 0 || NewBuffer == NULL) {
        std::cerr << "����ImageBuffer��NewBufferʧ��" << std::endl;
        free(FileBuffer);
        free(ImageBuffer);
        return 1;
    }

    std::cout << "NewBuffer�����ֽ���: " << newBufferSize << std::endl;

    DWORD writeResult = MemeryTOFile(NewBuffer, newBufferSize, (LPSTR)"C:\\Users\\GaGa\\Desktop\\SSSSS_new.exe");
    if (writeResult == 0) {
        std::cerr << "д���ļ�ʧ��" << std::endl;
        free(FileBuffer);
        free(ImageBuffer);
        free(NewBuffer);
        return 1;
    }

    std::cout << "д��ɹ�, �ֽ���: " << writeResult << std::endl;

    DWORD fileOffset = RvaTOFileOffset(FileBuffer, 0x17000);
    if (fileOffset == 0) {
        std::cerr << "�����ļ�ƫ��ʧ��" << std::endl;
    }
    else {
        std::cout << "�ļ�ƫ��: " << std::hex << fileOffset << std::endl;
    }

    free(FileBuffer);
    free(ImageBuffer);
    free(NewBuffer);

    return 0;
}

//int main()
//{
//	LPVOID FileBuffer = NULL;
//	DWORD result = ReadFile(FILEPATH, &FileBuffer);	
//
//	unsigned char* temp = (unsigned char*)FileBuffer;
//	if (result == 0)
//	{
//		std::cout << "��ȡ����" << std::endl;
//	}
//	std::cout << "��ȡ�ֽ�---->" << result << std::endl;
//
//	LPVOID ImageBuffer = NULL;
//	DWORD CopyResult = CopyFileBufferToImageBuffer(FileBuffer, &ImageBuffer);
//	if (CopyResult == 0)
//	{
//		std::cout << "����ʧ��" << std::endl;
//		return 0;
//	}
//	unsigned char* temp2 = (unsigned char*)ImageBuffer;
//
//	std::cout << "���Ƴɹ�--->"  <<  CopyResult << std::endl;
//
//	
//
//	LPVOID NewBuffer = NULL;
//	DWORD CpoyNewBuffer = CopyImageBufferToNewBuffer(ImageBuffer,&NewBuffer);
//	if (CpoyNewBuffer == 0)
//	{
//		std::cout << "����ʧ��" << std::endl;
//		return 0;
//
//	}
//
//	std::cout << "�����ֽ�--->" << CpoyNewBuffer << std::endl;
//	
//	unsigned char* temp3 = (unsigned char*)NewBuffer;
//
//	DWORD MemeryResult =  MemeryTOFile(NewBuffer, 42496, (LPSTR)"C:\\Users\\GaGa\\Desktop\\new.exe");
//
//	if (MemeryResult == 0)
//	{
//		printf("д��ʧ��\n");
//		return 0;
//	}
//	std::cout << "д��ɹ�---->" << MemeryResult << std::endl;
//
//	DWORD FOAResult = RvaTOFileOffset(FileBuffer, 0x17000);
//	std::cout << "�ļ�ƫ��-->" << std::hex <<  FOAResult << std::endl;
//	return 0;
//}


