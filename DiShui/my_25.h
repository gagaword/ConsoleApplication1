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
};

/*!
 * @brief �÷������ڻ�ȡ����ͷ.
 * @param Buffer ����PE��ʽ��������.
 * @param peheader PEheaders�ṹ
 * @return 0��ʾʧ��,���򷵻�1.
*/
bool GetPeheadersInfo(LPVOID Buffer, PEHeaders peheader);

/*!
 * @brief �÷�����ӡ�ṩ�ļ��ĵ���������.
 * @param filePath �ļ�·��.
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool PrintDataExport(LPCSTR filePath);
