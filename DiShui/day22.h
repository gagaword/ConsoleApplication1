#pragma once

#include<windows.h>
#include<iostream>
#include<string.h>

#define DEBUG 0
#define LOG(FUN_NAME,VALUES) if ((DEBUG) == 1){std::cout << FUN_NAME << "---->" << std::hex << VALUES << std::endl;}
#define IMAGE_SIZEOF_Signature 0x4

/// <summary>
/// �÷�����ȡһ���ļ�������
/// </summary>
/// <param name="FilePath">�ļ���·��</param>
/// <param name="FileBuffer">�����ļ����ݵ�ָ���ָ��</param>
/// <returns>
/// ����0��ʾ��ȡʧ�ܣ������ֽڱ�ʾ��ȡ�ɹ���
/// </returns>
DWORD ReadFile(IN const char* FilePath, OUT LPVOID* FileData);


/// <summary>
/// �÷�������FileBufer��ImageBuffer��
/// </summary>
/// <param name="FileBuffer">FileBufferָ��</param>
/// <param name="ImageBuffer">ImageBufferָ��</param>
/// <returns>
/// ����0��ʾʧ�ܣ����򷵻ظ��ƵĴ�С
/// </returns>
DWORD CopyFileBufferToImageBuffer(IN LPVOID FileBuffer, OUT LPVOID* ImageBuffer);


/// <summary>
/// �÷�������ImageBuffer��NewBuffer�У�ʹ��NewBuffer���ݴ����ҿ�����
/// </summary>
/// <param name="ImageBuffer">ImageBufferָ��</param>
/// <param name="NewBuffer">NweBufferָ��</param>
/// <returns>
/// ����0��ʾ����ʧ�ܣ����߷��ظ��ƵĴ�С
/// </returns>
DWORD CopyImageBufferToNewBuffer(IN LPVOID ImageBuffer, OUT LPVOID* NewBuffer);


/// <summary>
/// �÷������ڴ��е�����д�뵽�ļ���
/// </summary>
/// <param name="pMemBuffer">�ڴ�����</param>
/// <param name="size">Ҫ���ƵĴ�С</param>
/// <param name="lpszFile">Ҫ�����ļ���·��</param>
/// <returns>
/// ����0��ʾд��ʧ�ܣ����򷵻ظ��ƵĴ�С
/// </returns>
DWORD MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT LPSTR lpszFile);


/// <summary>
/// �÷������ڴ�ƫ��תΪ�ļ�ƫ��
/// </summary>
/// <param name="FileBuffer">FileBufferָ��</param>
/// <param name="dwRva">�ڴ�ƫ��</param>
/// <returns>
/// ����0��ʾת��ʧ�ܣ����򷵻��ļ�ƫ��FOA
/// </returns>
DWORD RvaTOFileOffset(IN LPVOID FileBuffer, IN DWORD dwRva);