#include<iostream>	

// ����ָ��
// ����ָ����ָ�뺯����ͬ��ָ�뺯������������������ص���һ��ָ������
// ������ָ���ʾ���ָ��ָ��һ���������׵�ַ��
// ��C�����У�������Ҳ��ȫ�ֱ�����������Ǻ�����ִ�еĴ��룬��Щ�ɳ�ΪӲ���롣
// ����ָ��Ķ��壺
// ����ָ��ָ��ĺ������ͺͲ����뱾ָ��һ�£���һ�µ�����¿���ʡ��ǿ������ת��
// ����ָ���Ӧ�ã�
// �Ѻ����ŵ���������

int x = 20;

int addSum(int x, int y)
{
	return x + y;
}


unsigned char fun[] = {
	0x55,
	0x8B, 0xEC,
	0x83, 0xEC, 0x40,
	0x53,
	0x56,
	0x57,
	0x8D, 0x7D, 0xC0,
	0xB9, 0x10, 0x00, 0x00, 0x00,
	0xB8, 0xCC, 0xCC, 0xCC, 0xCC,
	0xF3, 0xAB,
	0x8B, 0x45, 0x08,
	0x03, 0x45, 0x0C,
	0x5F,
	0x5E,
	0x5B,
	0x8B, 0xE5,
	0x5D,
	0xC3,
};


int main()
{
	// ��ʱpָ����addSum���׵�ַ
	int(*p)(int, int) = (int(__cdecl *)(int,int)) & addSum;
	int(*xx)(int) = (int(__cdecl *)(int))10;

	int result = p(2, 3);
	printf("%d\n", result);

	printf("%p\n", &addSum);	// 00961226
	printf("%p\n", p);			// 00961226
	printf("%d\n", x);


	int(*funP)(int, int) = (int(__cdecl *)(int,int))&fun;
	int ss = funP(2, 3);
	printf("ss--->%d\n", ss);

	/*
	* Ϊ����ָ�����������Fun������ָ��������int(*)(int,int)
	* Fun���������ͣ�p�Ǳ�������
	typedef int (*Fun)(int, int);
	Fun p = (int (*)(int, int)) & fun;
	int xx = p(2, 3);
	printf("%d\n", xx);*/
	return 0;
}