#include<iostream>

// __cdecl Ĭ�ϵ��ö�ջ
// __stdcall ��ƽջ
// __fastcall ���ٶ�ջ

void __cdecl function1(int a, int b, int c)
{
	if (a > 1 && b > 1 && c > 1)
	{
		printf("OK\n");
	}
	else
	{
		printf("Error\n");
	}
}


void sub_200(int a, int b, int c, int d)
{
	if (a > 1 || b > 1 || c > 1 || d > 1) {
		printf("OK\n");
	}
	else {
		printf("Error\n");
	}
}

void sub_300(int x, int y)
{

	// if����ִ��
	if (1)
	{
		printf("1\n");
	}
	if (2)
	{
		printf("2\n");
	}
	if (-1)
	{
		printf("3\n");
	}
	if (1>2)
	{
		printf("4\n");
	}
	if (0)
	{
		printf("5\n");
	}
	if (x=2)
	{
		printf("6\n");
	}
	if (x > y)
	{
		printf("7\n");
	}
	if (x == y)
	{
		printf("8\n");
	}
	if (x == 2)
	{
		printf("8\n");
	}
}

// ��Ŀ�����
// ��Ŀ������ڻ������if....else....
void function2(int a, int b)
{
	int data = a > b ? a : b;
}



int main()
{
	// С����ת������ͣ���������չ
	char a = 0xff;
	short b = a;

	// �޷������з���
	char temp2 = 1;
	unsigned int  temp1 = 0xFFFFFFFE;
	printf("%d",temp2 +  temp1);

	// �߼�����
	function1(1,2,3);
	sub_200(1,2,3,4);
	sub_300(1, 2);
	function2(1,2);
}