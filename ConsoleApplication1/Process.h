#pragma once

#include<Windows.h>
#include<Psapi.h>


/*
******************************
��ȡָ������(PID)�ľ��
dwAccess:�����Ȩ�ޡ�
isHandle:�Ƿ�̳о����
processPid:����PID��
by:GaGa
date:2024.7.12
******************************
*/
HANDLE getProcessHandle(DWORD dwAccess, BOOL isHandle, DWORD processPid);


/*
******************************
��ȡָ�������PID
processName:�������ơ�
by:GaGa
date:2024.7.12
******************************
*/
DWORD FindProcessIDByName(const std::wstring& processName);

/*
******************************
�������н��̣�������������Լ�PID
by:GaGa
date:2024.7.12
******************************
*/
void getALLProcessName();


