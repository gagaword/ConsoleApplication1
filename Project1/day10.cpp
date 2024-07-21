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

// do...while
int arrayBig2()
{
	int number[] = { 3,2,1,5,6 };
	int bigNumber = number[0];
	int i = 0;

	do
	{
		if (number[i] > bigNumber)
		{
			bigNumber = number[i];
		}
		++i;
	} while (i <= 4);
	//printf("\nbigNumber--->%d\n", bigNumber);
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

//do...while...
int arrayAllSum2()
{
	int number[] = { 2,1,3,4,5,6 };
	int i = 0;
	int sum = 0;
	do
	{
		sum = sum + number[i];
		++i;
	} while (i < 6);
	return sum;	
}



// ��ӡ����������Ԫ��
void printfArrayALL()
{
	int array[] = { 12,3,5,6,68,9,00 };
	int i = 0;
	while (i < 7)
	{
		printf("%d\n", array[i]);
		++i;
	}
}
// do...while...
void printfArrayALL2()
{
	int array[] = { 12,33,44,1,22,9 };
	int i = 0;
	do
	{
		printf("%d ", array[i]);
		++i;
	} while (i < 6);
}

// �������ȳ�������ͬλ�õ�ֵ��ӣ��洢����һ���ȳ�������
void array3()
{
	int array1[] = { 2,3,4,5 };
	int array2[] = { 1,3,4,6 };
	int array3[4] = { 0,0,0,0 };
	int i = 0;
	while (i < 4)
	{
		array3[i] = array1[i] + array2[i];
		printf("%d ", array3[i]);
		++i;
	}
}

void array32() 
{
	int array1[] = { 2,3,4,5 };
	int array2[] = { 1,3,4,6 };
	int array3[4] = { 0,0,0,0 };
	int i = 0;
	do
	{
		array3[i] = array1[i] + array2[i];
		printf("%d ", array3[i]);
		++i;
	} while (i < 4);
}

// �����������������1�����򷵻�0
int function2(int x)
{
	int num = 2;
	while (num <= x)
	{
		if (x % num == 0)
		{
			return 0;
		}
		++num;
	}
	return 1;
}

int function3(int x)
{
	int num = 2;
	
	do
	{
		if (x % num ==0)
		{
			return 0;
		}
		++num;
	} while (num < x);
	return 1;
}

// ð������
void bubbleShort1()
{
	int array[] = { 2,4,1,5,6,7 };
	int i = 0, j = 0, t = 0, k = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 5)
		{
			if (array[j] > array[j + 1])
			{
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
			++j;
		}
		++i;
	}

	while (k < 6)
	{
		printf("%d ", array[k]);
		++k;
	}
}


// ð������do...while
void bubbleSort()
{
	int array[] = { 2,4,1,5,6,7 };
	int i = 0, j = 0, t = 0, k = 0;
	do
	{
		j = 0;
		do
		{
			if (array[j] > array[j + 1])
			{
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
			++j;
		} while (j < 5);
		++i;
	} while (i < 6);

	while (k < 6)
	{
		printf("%d ", array[k]);
		++k;
	}
}

// �ж������Ƿ�Գ�
int array4()
{
	int array[] = { 1, 2, 3,3, 2, 1 };
	int i = 0;
	int begin = 0;
	int end = 5;
	while (begin < end)
	{
		if (array[begin] != array[end])
		{
			return 0;
		}
		begin++;
		end--;
		
	}
	return 1;
}

int main()
{
	function(1,2,1,2);

	int result = arrayBig();
	printf("%d\n", result);
	int result2 = arrayAllSum();
	printf("%d\n", result2);

	printfArrayALL();

	array3();

	int result3 = function2(5);
	printf("%d\n", result3);


	bubbleShort1();


	int bignumber = arrayBig2();
	printf("bignumber----->%d\n", bignumber);

	int allsum = arrayAllSum2();
	printf("%d\n", allsum);


	printfArrayALL2();

	printf("\n");

	array32();

	printf("\n");

	int result4 = function3(9);
	printf("function3--->%d\n", result4);


	bubbleSort();

	printf("\n");
	int result5 = array4();
	printf("result5--->%d", result5);
	return 0;
}