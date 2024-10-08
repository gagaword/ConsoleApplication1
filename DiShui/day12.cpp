#include<iostream>

// 缓冲区溢出HelloWorld
void helloWorld()
{
	printf("HelloWorld\n");
}

void sub_100()
{
	int array[3] = { 1,2,3 };

	// 获取到sub_100函数地址
	array[5] = (int)helloWorld;

}

void Twoarray()
{
	// 一维数组
	//int array2[] = { 1,2,3,4,5 };

	// 二维数组
	int array[3][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};

	int array2[3][4] = {
		{1,2,},
		{5,6,},
		{9,10,}
	};

	int array3[][4] = {
		{1,2,3,4},
		{5,6,7,8}
	};


	// 二维数据的取值
	int arr[5][12] = {

	{1,2,1,4,5,6,7,8,9,1,2,3},

	{1,2,1,4,5,6,7,8,9,1,2,3},

	{1,2,1,4,5,6,7,8,9,1,2,3},

	{1,2,1,4,5,6,7,8,9,1,2,3},

	{1,2,1,4,5,6,7,8,9,1,2,3}

	};

	// 遍历二维数组
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			printf("%d  ", arr[i][j]);
		}
		printf("\n");
	}

	int n = 0;
	int k = 0;

	/*while (n < 5)
	{
		k = 0;
		while (k < 12)
		{
			printf("%d  ",arr[n][k]);
			++k;
		}
		printf("\n");
		++n;
	}*/

	// 假设现在有5个班，每个班10个人，设计一个二维数组存储这些人的年龄.
	int age[5][10] = {
		{11,22,33,44,55,66,77,88,99,100},
		{12,23,34,45,56,67,78,89,90,99},
		{11,22,33,44,55,66,77,88,99,100},
		{11,22,33,44,55,66,77,88,99,100},
		{11,22,33,44,55,66,77,88,99,100},
	};

	printf("------------------------------------\n");
	// 如果想知道第二个班的第6个人的年龄，应该如何获取？编译器该如何获取？
	int x = age[1][5];
	printf("x---->%d\n", x);

	// 编译器:age[1*10+5]
	// 打印所有班级，所有学生的年龄(每个班级打印一行).
	printf("------------------------------------\n");
	int i = 0, b = 0;
	while (i < 5)
	{
		b = 0;
		while (b < 10)
		{
			printf("%d ", age[i][b]);
			++b;
		}
		printf("\n");
		++i;
	}

	// 将第二个班级的超过20岁的学生的年龄修改为21岁.
	for (int i = 1; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (age[i][j] >= 20)
			{
				age[i][j] = 21;
			}
		}
	}

	printf("------------------------------------\n");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%d ", age[i][j]);
		}
		printf("\n");
	}

	// 打印出每个班级学生的年龄的和.
	printf("------------------------------------\n");
	int agesum = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			agesum += age[i][j];
		}
		printf("agesum---->%d\n", agesum);
		agesum = 0;
	}

	
	
}

void arraySort()
{
	/*
		数组一：[3,5,7,9,12,25,34,55]
		数组二：[4,7,9,11,13,16]
		将两个数组中所有数据进行从小到大的排序，存储到
		另一个数组中.
	*/
	printf("------------------------------------\n");

	int array1[] = { 3,5,7,9,12,25,34,55 };
	int array4[] = { 4,7,9,11,13,16 };
	int array5[20] = { 0 };

	int i = 0, j = 0, k = 0;

	// 合并两个数组
	while (i < sizeof(array1) / sizeof(array1[0]) && j < sizeof(array4) / sizeof(array4[0])) {
		if (array1[i] <= array4[j]) {
			array5[k++] = array1[i++];
		}
		else {
			array5[k++] = array4[j++];
		}
	}

	// 处理剩余的数据
	while (i < sizeof(array1) / sizeof(array1[0])) {
		array5[k++] = array1[i++];
	}
	while (j < sizeof(array4) / sizeof(array4[0])) {
		array5[k++] = array4[j++];
	}


	/*while (a < sizeof(array1) / sizeof(array1[0]))
	{
		array5[a] = array1[a];
		++a;
	}
	printf("a---->%d\n", a);

	while (j < sizeof(array4) / sizeof(array4[0]))
	{
		array5[a] = array4[j];
		++a;
		++j;
	}*/


	for (int i = 0; i < sizeof(array5) / sizeof(array5[0]); i++)
	{
		printf("%d ", array5[i]);
	}
}
int main()
{
	// 缓冲区溢出
	/*sub_100();*/

	//数组
	Twoarray();


	// 排序
	arraySort();
	return 0;
}