#pragma once

#include<windows.h>
#include<iostream>
#include<string.h>

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
/// <param name="FileBuffer">FileBuffer</param>
/// <param name="ImageBuffer">ImageBuffer</param>
/// <returns>
/// ����0��ʾʧ�ܣ����򷵻ظ��ƵĴ�С
/// </returns>
DWORD CopyFileBufferToImageBuffer(IN LPVOID FileBuffer, OUT LPVOID* ImageBuffer);