#include<iostream>

/*
do....while...
while...
for....
*/


// ��������������ֵ��������ʹ�õ�����������ʹ�ñ���
void  function(int a, int c, int d, int e)
{
	// ����������
	int t = a;
	a = c;
	c = t;
	printf("%d|%d\n", a, c);

	// ���õ���������
	d = d + e;
	e = d - e;
	d = d - e;
	printf("%d|%d\n", d, e);

}

// ���������ֵ

int arrayBig()
{
	int number[] = { 3,2,1,5,6 };
	int bigNumber = number[0];
	int i = 1;
	while (i <= 4)
	{
		if (number[i] > bigNumber)
		{
			bigNumber = number[i];
		}
		++i;
	}
	return bigNumber;
}

// ������������֮��
int arrayAllSum()
{
	int number[] = { 2,1,3,4,5,6 };
	int i = 0;
	int sum = 0;
	while (i < 6)
	{
		sum = sum + number[i];
		++i;
	}
	return sum;
}
int main()
{
	function(1,2,1,2);

	int result = arrayBig();
	printf("%d\n", result);
	int result2 = arrayAllSum();
	printf("%d\n", result2);
	return 0;
}