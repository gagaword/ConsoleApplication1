#pragma once

#include<Windows.h>
#include<iostream>
#include "my_25.h"



/*!
 * @brief �÷�����ӡ�ṩPE�ļ����ض�λ��
 * @param filePath �ļ�·��
 * @return 0��ʾʧ�ܣ������ӡ���ݲ�����1.
*/
bool PrintBaseloc(LPCSTR filePath);

/**
 * @brief �÷�����PE�ļ��еĵ������ƶ����µĽ���
 * @param filePath �ļ�·��
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool MoveExport(LPCSTR filePath);

/**
 * @brief �÷����ƶ��������½�
 * @param filePath �ļ�·��
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool MoveBaseReloc(LPCSTR filePath);



bool AddSectionAndExportTable(LPCSTR filePath);