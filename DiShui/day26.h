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
 * @brief �÷����ƶ��������ƶ����µĽ���
 * @param filePath �ļ�·��
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool MoveExport(LPCSTR filePath);

/**
 * @brief �÷����ƶ��ض�λ���½�
 * @param filePath �ļ�·��
 * @return 0��ʾʧ�ܣ����򷵻�1.
*/
bool MoveBaseReloc(LPCSTR filePath);
