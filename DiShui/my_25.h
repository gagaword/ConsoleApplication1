#pragma once

#include <Windows.h>
#include <iostream>

// PE��Ϣ�ṹ
struct PEHeaders {
	PIMAGE_DOS_HEADER dosHeader;
	PIMAGE_NT_HEADERS32 ntHeaders;
	PIMAGE_FILE_HEADER fileHeader;
	PIMAGE_OPTIONAL_HEADER32 optionalHeader;
	PIMAGE_SECTION_HEADER sectionHeader;
	PIMAGE_DATA_DIRECTORY dataHeaders;
};


/*!
 * @brief �÷������ڻ�ȡ����ͷ.
 * @param Buffer ����PE��ʽ��������.
 * @param peheader PEheaders�ṹ
 * @return 0��ʾʧ��,���򷵻�1.
*/
bool GetPeheadersInfo(LPVOID Buffer, PEHeaders &peheader);

/*!
 * @brief �÷�����ӡ�ṩ�ļ��ĵ���������.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool PrintDataExport(LPCSTR filePath);

/*!
 * @brief �÷��������ṩ�ĺ�����Ŵ�ӡ��������Ϣ,������Ŵ�0��ʼ
 * @param serial �������
 * @param filePath �ļ�·��
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
DWORD FunctionSerialToInfo(DWORD serial, LPCSTR filePath);

/*!
 * @brief �÷���ͨ���������ƻ�ȡ������Ϣ
 * @param funName ��������
 * @return 0��ʾʧ�ܣ����򷵻ط�����ַ.
*/
DWORD FunctionNameToInfo(LPCSTR funName, LPCSTR filePath);

/*!
 * @brief �÷�����RVAתΪFOV
 * @param RVA RVA
 * @param fileBuffer ����PE�ļ�������������
 * @return 0��ʾʧ�ܣ�����FOV
*/
DWORD RvaToFov(DWORD RVA, LPVOID fileBuffer);

/*!
 * @brief �÷����� value �� alginValue ����
 * @param value Ŀ��ֵ
 * @param alginValue ����ֵ
 * @return 0ʧ�ܣ����򷵻ض�����ֵ
*/
DWORD algin(DWORD value, DWORD alginValue);
