#include<iostream>

#include "Process.h"
#include<Windows.h>
#include<tchar.h>
#include<Psapi.h>
#include <tlhelp32.h>

HANDLE getProcessHandle(DWORD dwAccess, BOOL isHandle, DWORD processPid)
{
	if (dwAccess == NULL || isHandle == NULL || processPid == NULL)
	{
		return (HANDLE)-1;
	}
	HANDLE processHandle = OpenProcess(dwAccess, isHandle, processPid);
	if (processHandle == NULL)
	{
		std::cout << GetLastError() << std::endl;
	}
	else {
		return processHandle;
	}
}

void getALLProcessName()
{
    // ������̿��յľ��
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) return;

    // ����PROCESSENTRY32�ṹ�壬���ڴ洢������Ϣ
    PROCESSENTRY32 pe32;
    // ȷ���ṹ���С��ȷ���Ա����32λ��64λϵͳ
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // ����ϵͳ�е����н���
    if (Process32First(hProcessSnap, &pe32))
    {
        do
        {
            // ��ӡ����ID�ͽ�������
            std::wcout << L"Process ID: " << pe32.th32ProcessID << L", Name: " << pe32.szExeFile << std::endl;

        } while (Process32Next(hProcessSnap, &pe32));
    }

    // �رս��̿��վ��
    CloseHandle(hProcessSnap);
}

// ����һ�����������ܽ������ƣ�����ƥ����̵�PID
DWORD FindProcessIDByName(const std::wstring& processName)
{
    // ������̿��յľ��
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) return 0;

    // ����PROCESSENTRY32�ṹ�壬���ڴ洢������Ϣ
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // ����ϵͳ�е����н���
    if (Process32First(hProcessSnap, &pe32))
    {
        do
        {
            // �����������Ƿ�ƥ��
            if (_wcsicmp(pe32.szExeFile, processName.c_str()) == 0)
            {
                // ƥ��������ƣ����ؽ���ID
                CloseHandle(hProcessSnap); // �رս��̿��վ��
                return pe32.th32ProcessID;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    // û���ҵ�ƥ��Ľ��̣��رվ��������0
    CloseHandle(hProcessSnap);
    return 0;
}




