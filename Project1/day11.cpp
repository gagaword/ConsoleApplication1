#include<iostream>
#include <vector>

// 8λ��������
void par8(char x, char a)
{

}

// 16λ��������
void par16(short a, short b)
{

}

// 32λ��������
void par32(int a, int b)
{

}

// ����32λ�ı�����δ洢
__int64 par64longlong()
{
	__int64 x = 0x12345678AAAAAAAA;
	return x;
}

//2��char arr[3] = {1,2,3};�� char arr[4] = {1,2,3,4};
// �ĸ�����ʡ�ռ䣬�ӷ����ĽǶ���˵����Ĺ۵�
void function2()
{
	//char arr[3] = { 1,2,3 };
	char arr2[4] = { 1,2,3,4 };
}
// �ֲ��������ڴ����
void parLocal()
{
	char s = 1;
	char b = 2;
}

// ����ķ���
int array()
{
	/*int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;*/
	int array[] = { 1,2,3,4,5,6,7 };

	return 0;
}

// 3���ҳ����渳ֵ���̵ķ�������
void Function()
{
	int x = 1;
	int y = 2;
	int r;
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };

	r = arr[1];
	r = arr[x];
	r = arr[x + y];
	r = arr[x * 2 + y];
}


/*
Ͱ����
2 4 6 5 3 1 2 7
0 0 0 0 0 0 0 0
0 1 2 3 4 5 6 7

Ͱ������Ҫʹ�õ���̬����
*/

void arraySort()
{
	int array[] = { 2,8,1,5,3,1,2,3 };
	int arrayLength = sizeof(array) / sizeof(array[0]);
	
	// �ҳ��������ֵ
	int bigNumber = array[0];
	for (int i = 1; i < arrayLength; i++)
	{
		if (array[i] > bigNumber){
			bigNumber = array[i];
		}
	}

	printf("%d\n", bigNumber);

	// ��̬�����ڴ�
	int* array2 = new int[bigNumber + 1]{0};

	//// ��̬�����ڴ�
	//int* array2 = (int*)malloc((bigNumber + 1) * sizeof(int));
	//if (array2 == NULL)
	//{
	//	printf("Memory allocation failed\n");
	//	return;
	//}
	//// �ڴ��ʼ��
	//for (int i = 0; i <= bigNumber; i++)
	//{
	//	array2[i] = 0;
	//}


	// Ͱ�����߼�ִ��
	for (int i = 0; i < arrayLength; i++)
	{
		array2[array[i]] += 1;
	}

	// ������롣��������
	/*for (int i = 0; i < 8; i++)
	{
		
		if (array2[i] == 1)
		{

			printf("%d ", i);
		}
		else if (array2[i] == 2)
		{
			printf("%d %d ", i, i);
		}
	}*/

	// ���
	for (int i = 0; i <= arrayLength; i++)
	{
		for (int j = 0; j < array2[i]; j++)
		{
			printf("%d ", i);
		}
	}


	// �ͷŶ�̬����
	delete[] array2;
}

int main()
{
	__int64 number = par64longlong();
	printf("%llx\n", number);

	char i = 'a';
	short b = 'b';
	int num = 12;


	array();

	// Ͱ����
	arraySort();

	// 8λ����
	par8(1,2);

	// 16λ����
	par16(2,4);

	// par32λ����
	par32(1,2);

	// �ֲ�����
	parLocal();

	// �ռ�����
	function2();

	// 3���ҳ����渳ֵ���̵ķ�������
	Function();
}

