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
	printf("%d",k[0][0]);

}
int main()
{
	poniter();
	return 0;
}