#include<iostream>	

// �㺯�������ñ��������ɻ����
// ���ʵ�������������


int __declspec(naked) sumTwo(int a, int b)
{
	// �������
	__asm 
	{
		// ����ԭʼջ��
		push ebp

		// ������ջ�ռ�
		mov ebp,esp
		sub esp,0x40

		// ����ԭʼ�Ĵ�����Ϣ
		push edi
		push esi
		push ebx

		//����ջ�ռ�
		lea edi,dword ptr ds:[ebp - 0x40]
		mov eax,0xcccccccc
		mov ecx,0x10
		rep stosd

		// �����巽��ִ��
		mov eax,dword ptr ds:[ebp+0x8]
		add eax,dword ptr ds:[ebp+0xc]

		// �ָ�ԭʼ�Ĵ�����Ϣ
		pop ebx
		pop esi
		pop edi

		// �ָ���ջ
		mov esp,ebp
		pop ebp
		ret
	}
}
int main()
{
	// �����㺯��
	int result =  sumTwo(1,2);
	std::cout << result << std::endl;
}