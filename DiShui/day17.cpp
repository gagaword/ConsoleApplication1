#include<iostream>

void poniter()
{
	// һ��ָ��
	int x = 10;
	int* p = &x; // p�����x�ĵ�ַ
	printf("%p %d\n", p, *p);

	// ����ָ��
	int a = 30;
	int* aP = &a; // aP������a�ĵ�ַ
	int** aPP = &aP; // aPP������aP�ĵ�ַ
	// *aPPȡ������aP��������ݣ���aP��������ݾ���a�ĵ�ַ��������Ҫ��ȡֵһ��
	// aPP�������aP�ĵ�ַ��������aP��������ݡ�
	// 
	printf("aPP--->%p *aPP--->%p *(*(aPP))--->%d\n", aPP, *aPP,*(*(aPP)));

	// ����ָ��
	int b = 40;
	int* bP = &b;
	int** bPP = &bP;
	int*** bPPP = &bPP;

	printf("---------------------\n");
	printf("b--->%p\n", &b);
	printf("bP-->%p\n", &bP);
	printf("bPP->%p\n", &bPP);
	printf("---------------------\n");

	// bPPP-->bPP�ĵ�ַ
	printf("bPPP---->%p\n", bPPP);

	// *bPPP--->bPP�ĵ�ַ--->bP�ĵ�ַ
	printf("*bPPP--->%p\n", *bPPP);

	// *bPPP--->bP�ĵ�ַ+*---->b�ĵ�ַ
	printf("*(*(bPP)):%p\n", *(*(bPPP)));
	
	// b�ĵ�ַ---->40
	printf("*(*(*bPPP)):%d\n", *(*(*bPPP)));
	printf("---------------------\n");
	printf("---------------------\n");

	// *�ķ������[]�Ĺ�ϵ
	int v = 20;
	int* m = &v;
	int** k = &m;
	int*** s = &k;
	printf("%p\n", m);

	printf("%d\n", *m);
	printf("%d\n", *(m + 0));
	printf("%d\n", m[0]);

	printf("---------------------\n");

	printf("%d\n", *(*k));
	printf("%d\n", *(*k + 0));
	printf("%d\n",k[0][0]);

	printf("%p\n", *(k + 2));
	printf("%p\n", k[2]);

	printf("---------------------\n");
	printf("%d\n", *(*(*s)));
	printf("%d\n", *(*(*s + 0)));
	printf("%d\n", s[0][0][0]);

	printf("---------------------\n");

	// ����ָ��
	int ar[] = { 1,2,3,4,5 };
	// �����ִ�����ʵ��ʹ����Ч��һ�����������ǵ������ǲ�ͬ�ģ�&ar��ȡar�ĵ�ַ���������飬��arֻ�Ǳ�ʾȡ�����׸�Ԫ�صĵ�ַ
	int(*array)[5] = (int(*)[5]) & ar;
	//int(*array)[5] = (int(*)[5])ar;

	// �����д���Ҳ��֤��ar�ĵ�ַ���������׸�Ԫ�صĵ�ַ
	printf("ar�ĵ�ַ:%p\n", &ar);
	printf("ar[0]�ĵ�ַ:%p\n", &ar[0]);
	printf("ar[1]�ĵ�ַ:%p\n", &ar[1]);


	// array��*array�����ֵ��һ���ģ�����ar����Ԫ�ص��׵�ַ��������ʵ��ȡֵ��ʱ����Ҫͨ��**ȡֵ
	// ���￴������*array��һ����ֵ����ʵ����array�������ar�ĵ�ַ����ar�ĵ�ַ������������Ԫ�ص��׵�ַ
	// ��*array��ȡar��ַָ������ݵĵ�ַ(��������Ԫ�ص��׵�ַ�ˣ����Ǳ���)��
	printf("arra���������:%p\n", array); 
	// ��ʱarray������Ԫ���׵�ַ�����һ��ȡֵ����ȡ�����Ԫ��
	printf("������array������:%p\n", *array);

	printf("%d\n", *(*(array) + 1));
	printf("*(array)[1]--->%d\n", (*array)[1]);
	printf("*(array) + 1):%d\n", *(*(array) + 4));
	printf("%d\n", sizeof(array));

	//array++; // ��4
	printf("%p\n", array);

	// ͨ������ָ���ȡ������Ԫ��
	printf("%d\n", *((*(array) + 2) + 1));

	// array[0]��ȡ��������Ԫ�ص�ַ��ͨ��[1]ƫ��ȡ��ֵ
	// ֻ��ͨ��array[0]��ȡ����Ԫ�ص�ַ�������1�Ļ�arrayָ��ľͲ�����������ˡ�
	printf("%d\n", array[0][1]);
	printf("%d\n", array[0][2]);

	int arra[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	int(*arrP)[2] = (int(*)[2]) & arra;

	printf("arra[2]:%p\n", &arra[2]);
	printf("(arrP + 1):%p\n", arrP + 1);

	printf("%d\n", *(*(arrP + 0) + 2));
	printf("%d\n", *(*(arrP + 1) + 1)); // 4
	
	printf("%d\n", *(*(arrP + 3) + 4)); // 11

	/*int xx = (*(arrP + 1)[2]);
	int ss = arrP[1][2];*/

	printf("*(arrP + 1)[2]->%d\n", (*(arrP + 1)[2]));

	// ��*(p+1)[2] �Ƿ�һ������p[1][2]�أ� ͨ������������֤��
	//printf("%d\n", arrP[1][2]);
	printf("%d\n", *(arrP + 1)[2]);

	printf("%p\n", &arra[6]);
	printf("%p\n", (arrP + 1)[2]);

	// ʹ������ָ�����һ��һά����
	int data[] = { 12,123,6,45,1,2,3123,2313,5,6,6,7,8 };
	int(*dataP)[1] = (int(*)[1]) & data;
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
	{
		//printf("%d ", *(*(dataP++)));
		printf("%d ", (*(dataP)[i]));
	}
}
int main()
{
	poniter();
	return 0;
}