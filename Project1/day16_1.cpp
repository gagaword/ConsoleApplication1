#include<iostream>


// ָ������
void pointerArray()
{
	// int���ͣ��洢5��int���͵�����
	int array[] = { 1,2,3,4,5 };
	int arrayLength = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < arrayLength; i++)
	{
		printf("%d ", *(array + i));
	}

	printf("\n--------------------------------------\n");

	// int���͵�ָ�룬�洢����int���͵�ָ��(����һϯ������һϯ��......)
	int a = 10, b = 20, c = 30, d = 40, e = 50;
	int* arr[] = { &a, &b, &c, &d, &e}; // �洢����a,b,c,d,e�ĵ�ַ����Щ��ַ�ֱ�ָ����10��20��30��40��50
	int arrLength = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < arrLength; i++)
	{
		printf("%p---->%p---->%d ", (arr + i), *(arr + i), *(*(arr + i)));
	}
	printf("\n--------------------------------------\n");

	// ��õ�ָ�����飺
	// p1�Ѿ���charָ���ˣ�����Ҫʹ��ȡֵ��&�ˡ�
	char* p1 = (char*)"if";
	char* p2 = (char*)"for";
	char* p3 = (char*)"while";
	char* p4 = (char*)"switch";
	
	char* keyword[] = { p1,p2,p3,p4 };
	// keyword������Ѿ�����Щ�ַ����ĵ�ַ�ˣ�ͨ��*[keyword[i]]ȡ�������ַ��������ַ���
	// �мǲ�����ͨ��*[keyword[i]]ȥȡֵ����Ϊ���ʱ��ȡ�������ַ��������ܻ�����ڴ��޷����ʡ�
	// �����������Ǹ�int��ͬ�ľ��ǣ�int����ͨ����������ȥ��ָ��������еĸ�ֵ���Żᵼ����������ַ
	// �������char��ֱ�Ӱ��ַ����ĵ�ַ�ŵ���ָ������������ֻ����һ���ַ��
	// p1������ֱ��ָ�����ַ���"if"�ٰ����p1�����ݷŵ�keyword��
	for (int i = 0; i < sizeof(keyword) / sizeof(keyword[0]); i++)
	{
		printf("%p---->%s\n", keyword[i], (keyword[i]));
	}

	printf("\n--------------------------------------\n");

	// ����������Ǹ��ǵȼ۵�
	char* keyword2[] =
	{
		(char*)"if",
		(char*)"for",
		(char*)"while",
		(char*)"switch"
	};
	for (int i = 0; i < 4; i++)
	{
		printf("%p---->%s\n", keyword2[i],keyword2[i]);
	}

}

// ����ṹ��
typedef struct Student
{
	int x;
	int y;
}stu;

// �ṹ��ָ��
void structArry()
{
	stu* s1;
	s1 = (stu*)20; // s1�������0x00000014�����ַ(20-->0x14)
	printf("s1----->%p\n", s1);

	s1++; // 28
	printf("s1++--->%p\n", s1);

	stu s2;
	s2.x = 10;
	s2.y = 20;
	printf("\n--------------------------------------\n");

	// ptrS2������s2�ĵ�ַ,���ǽṹ���һ����Ա�ĵ�ַ
	stu* ptrS2 = &s2;
	printf("%d\n", ptrS2->x);
	printf("%d\n", ptrS2->y);
}

int main()
{
	pointerArray();
	printf("\n--------------------------------------\n");

	structArry();
	return 0;
}