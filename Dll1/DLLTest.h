#pragma once

extern "C" __declspec(dllexport) int __stdcall add(int x, int y);

extern "C" __declspec(dllexport) int __stdcall sub(int x, int y);

extern "C" __declspec(dllexport) int __stdcall imul(int x, int y);

// ������
void  inti();

// ������
void  del();

extern "C" __declspec(dllexport) void ExportFunction();

// ���غ������ƶ��庯����������ͨCPP�ļ�һ��
//int sub(int x, int y );
