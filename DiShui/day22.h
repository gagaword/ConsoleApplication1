#pragma once
#include<windows.h>
#include<iostream>
#include<string.h>

#define DEBUG 0
#define LOG(FUN_NAME,VALUES) if ((DEBUG) == 1){std::cout << FUN_NAME << "---->" << std::hex << VALUES << std::endl;}
#define IMAGE_SIZEOF_Signature 0x4

/*!
 * @brief �÷�����ȡһ���ļ�������
 * @param FilePath �ļ���·��
 * @param FileData �����ļ����ݵ�ָ���ָ��
 * @return ����0��ʾ��ȡʧ�ܣ������ֽڱ�ʾ��ȡ�ɹ���
*/
DWORD ReadFile22(IN LPCSTR FilePath, OUT LPVOID* FileData);

/*!
 * @brief �÷�������FileBufer��ImageBuffer��
 * @param FileBuffer FileBufferָ��
 * @param ImageBuffer ImageBufferָ��
 * @return 
*/
DWORD CopyFileBufferToImageBuffer(IN LPVOID FileBuffer, OUT LPVOID * ImageBuffer);

/*!
 * @brief �÷�������ImageBuffer��NewBuffer�У�ʹ��NewBuffer���ݴ����ҿ�����
 * @param ImageBuffer ImageBufferָ��
 * @param NewBuffer	  NweBufferָ��
 * @return  ����0��ʾ����ʧ�ܣ����߷��ظ��ƵĴ�С
*/
DWORD CopyImageBufferToNewBuffer(IN LPVOID ImageBuffer, OUT LPVOID* NewBuffer);

/*!
 * @brief �÷������ڴ��е�����д�뵽�ļ���
 * @param pMemBuffer �ڴ�����
 * @param size Ҫ���ƵĴ�С
 * @param lpszFile Ҫ�����ļ���·��
 * @return ����0��ʾд��ʧ�ܣ����򷵻ظ��ƵĴ�С
*/
DWORD MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile);


/*!
 * @brief �÷������ڴ�ƫ��תΪ�ļ�ƫ��
 * @param FileBuffer FileBufferָ��
 * @param dwRva �ڴ�ƫ��
 * @return ����0��ʾת��ʧ�ܣ����򷵻��ļ�ƫ��FOA
*/
DWORD RvaTOFileOffset(IN LPVOID FileBuffer, IN DWORD dwRva);