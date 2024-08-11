#pragma once

#include<Windows.h>
#include<iostream>
#include<string.h>


DWORD ReadFile(IN const char* filepath, OUT LPVOID* fileBuffer);

DWORD AddShellCode(IN LPVOID filePath);

DWORD FwritrFile(IN LPVOID buffer, IN size_t size, OUT const char* filePath);


bool AddShellCodeInData(IN LPVOID filePath);

bool AddShellCodeRdata(IN LPVOID filePath);

bool AddSection(IN LPBYTE filePath);

/*!
 * @brief �������һ���ڲ����ShellCode
 * @param filePath �ļ�·��
 * @return 0��ʾʧ�ܣ����򷴷���
*/
bool ExpandSection(IN LPBYTE filePath);

/*!
 * @brief ��ӡ����Ŀ¼
 * @param filePath �ļ�·��
 * @return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
bool ImageData(IN LPBYTE filePath);

/*!
 * @brief �ϲ���
 * @param filePath  �ļ�·��
 * @return 0�ɹ���1ʧ��
*/
bool MergeSection(IN LPBYTE filePath);