#pragma once
#include<iostream>

// ���ļ�
void *openFile(FILE** _Stream,const char* FileName,const char* Mode);


// ��ȡ�ļ���С
size_t GetFileSize(FILE* stream);

// ��ȡ�ļ�����
void *ReadFileData(long FileSize, size_t elemensize, FILE *stream);