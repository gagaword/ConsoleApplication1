#include<iostream>

struct student
{
	int x;
	int y;
};

void lianxi()
{
	char a = 10;
	short b = 20;
	int c = 30;

	char* pa = &a;
	short* pb = &b;
	int* pc = &c;

	char** ppa = &pa;
	short** ppb = &pb;
	int** ppc = &pc;
}

//4����ɴ��룬ʵ������ֵ�Ļ���

void Function()
{
	/*int arr[] = { 1,2,3,4,5,6,7,8 };*/
	int arr[] = { 2,3,5,1,2,4,7,9,7 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int tempLength = 0;

	/*if (length % 2 !=0)
	{
		tempLength = length + 1;
	}
	else {
		tempLength = length;
	}*/

	/*printf("tempLength---->%d\n", tempLength);
	printf("length-------->%d\n", sizeof(arr) / sizeof(arr[0]));*/
	
	//..�˴���Ӵ��룬ʹ��ָ�룬�������ֵ����
	int* begin = (arr);
	int* end = (arr + (length - 1));

	/*printf("begin--------->%d\n", *(begin));
	printf("end----------->%d\n", *(end));*/

	int i = 0;
	/*while (i < (tempLength / 2))
	{
		int temp = *(begin);
		*(begin)= *(end);
		*(end )= temp;
		++begin;
		--end;
		++i;
	}*/

	while (begin < end)
	{
		int temp = *(begin);
		*(begin) = *(end);
		*(end) = temp;
		++begin;
		--end;
		++i;
	}
	printf("------------------------\n");

	int* p = arr;
	//��ӡ����ֵ�Ĵ����Ѿ�д�꣬����Ҫ�޸�				
	/*for (int k = 0; k < 5; k++)
	{
		printf("%d\n", *(p + k));
	}*/
	for (int k = 0; k < length; k++)
	{
		printf("%d ", *(p + k));
	}
}


void test()
{
	/*������
	int ss = 20;
	student aa = (student)ss;*/

	/*int* a = (int*)10;
	char* b = (char*)20;
	a = (int*)b;*/

	//int* i = (int*)10;
	//int** s = &i; // s�������i�ĵ�ַ
	//int* result = *(s); //*ȡ��s����i��ַ��ֵ�ŵ�result�У���ʱresult����ľ���10,
	////int resu = *(result); //result�������10����10��Ϊ��ַ���޷��ҵ���Ӧ���ڴ�ģ���������ᷢ���쳣��

	//int x = 100;
	//int* a = &x; // ȡx�ĵ�ַ���浽a��
	//int resu = *(a); //ȡa��ַָ������ݱ��浽resu�С�


	/*
	�������
	int** uuu = (int**)200;
	int* re = *(uuu);
	printf("%d\n", re);*/


	int** uuu = (int**)200;
	int*** ss = &(uuu);
	int** re = *(ss);
	printf("%p\n", re);
	short arry[5] = { 1,2,3,4,5 };


	//int* u = &arry[0]; // ȡ�����һ��Ԫ�صĵ�ַ
	// ��д
	short* u = arry; // u����ľ��������һ��Ԫ�صĵ�ַ
	for (int i = 0; i < sizeof(arry) / sizeof(arry[0]); i++)
	{
		//int result = *(u + i);
		printf("%d ", *(u + i));
	}
}
int main()
{
	
	//test();
	//lianxi();
	Function();
	return 0;
}