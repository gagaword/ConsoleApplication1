#pragma once

#include<Windows.h>
#include<iostream>
#include<string.h>

/*!
 * @brief �÷�����ȡ�ļ�����.
 * @param filepath �ļ�·��.
 * @param fileBuffer ����ļ�����ָ���ָ��.
 * @return 0��ʾʧ�ܣ����߷��ض�ȡ�����ֽ���.
*/
DWORD ReadFile(IN LPCSTR filepath, OUT LPVOID* fileBuffer);

/*!
 * @brief �÷�����.text�����ShellCode.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
DWORD AddShellCode(IN LPCSTR filePath);

/*!
 * @brief �÷�����������д���ļ���.
 * @param buffer ������.
 * @param size   д���ֽ���.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����߷���1.
*/
DWORD FwritrFile(IN LPVOID buffer, IN size_t size, OUT LPCSTR filePath);

/*!
 * @brief �÷�����.data�����ShellCode.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool AddShellCodeInData(IN LPCSTR filePath);

/*!
 * @brief �÷�����.rdata�����ShellCode.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool AddShellCodeRdata(IN LPCSTR filePath);

/*!
 * @brief �÷�������һ���ڲ����ShellCode.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool AddSection(IN LPCSTR filePath);

/*!
 * @brief �������һ���ڲ����ShellCode.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool ExpandSection(IN LPCSTR filePath);

/*!
 * @brief ��ӡ����Ŀ¼.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool ImageData(IN LPCSTR filePath);

/*!
 * @brief �ϲ���.
 * @param filePath  �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool MergeSection(IN LPCSTR filePath);

//DWORD RVA_FOV(DWORD RVA, LPVOID fileBuffer);