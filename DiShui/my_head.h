#pragma once
#include<iostream>
#include<Windows.h>

// ���ļ�
int openFile(FILE** _Stream,const char* FileName,const char* Mode);

// ��ȡ�ļ���С
size_t GetFileSize(FILE* stream);

// ��ȡ�ļ�����
void *ReadFileData(long FileSize, size_t elemensize, FILE *stream);

// ����Ƿ�PE
int CheckPE(unsigned char* buuferFile);

// ��ȡ�ļ�
LPVOID ReadFile(const char* FilePath);