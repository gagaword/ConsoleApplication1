#include<iostream>	
#include<Windows.h>


/*
	1������һ��unsiged char ���ͣ�ͨ������Ϊ��3��5��7λ��ֵ,��ֵʱ����
	Ӱ�쵽����λԭ����ֵ.
	(ʹ��λ����ָ����磺& | ! ^ << >>��)

	2���ж�ĳ��λ��ֵ�Ƿ�Ϊ1.
	(ʹ��λ����ָ����磺& | ! ^ << >>��)

	3����ȡ��7��6��5λ��ֵ����ʮ������ʾ(unsigned).
	(ʹ��λ����ָ����磺& | ! ^ << >>��)
*/

// ��ȡָ����Χ��λֵ
unsigned int extractBits(unsigned char data, int start, int end) {
	// ����mask
	unsigned int mask = (1 << (end - start + 1)) - 1;
	printf("����---->%#x\n", mask);
	return (data >> start) & mask;
}

int main()
{
	// 0000 0000
	unsigned char x = 0;

	// �޸ĵ�3λΪ1,0000 0100
	x = 4 | x;
	printf("%x\n", x);

	// �ڸ�Ϊ0
	x = x & 0;
	printf("%x\n", x);

	x = 0;
	x = 4 ^ x;
	printf("%x\n", x);
	x = 0;

	// ����û��Ҫ��
	// 0000 0010
	x = 2 ^ x;
	x = x << 1;
	printf("%x\n", x);
	x = 0;

	// �޸ĵ�4λΪ1,0000 0100


	// �޸ĵ�5λΪ1,0000 0100
	// 0001 0000
	x = 16 | x;
	printf("%x\n", x);

	x = 0;
	x = 16 ^ x;
	printf("%x\n", x);

	// ��Ϊ0
	x = x & 0;
	printf("%x\n", x);

	x = 0;


	// �޸ĵ�7λΪ1,0000 0100 0100 0000
	x = 64 | x;
	printf("%x\n", x);

	x = 0;
	x = 64 ^ x;
	printf("%x\n", x);

	// ��Ϊ0
	x = x & 0;
	printf("%x\n", x);

	x = 0;

	// �ж�ĳ��λ���Ƿ���1��
	// �����жϵ��ĸ�λ���Ƿ���1
	// 0000 0000
	unsigned char data = 1;
	int values = data & 8;
	int result = 0;
	if (values != 1)
	{
		//result = MessageBoxA(NULL,"1�ĵ��ĸ�λ�ò���1","��Ϣ", MB_OK);
		printf("%d�ĵ��ĸ�λ�ò���1",data);
	}
	printf("%d\n", result);

	// ��ȡ��7��6��5λ��ֵ����ʮ������ʾ(unsigned).
	// 0111 0000
	// 1010 0101
	
	unsigned char data1 = 0x70;
	int res = data1 >> 4;
	printf("%d\n", res);
	
	unsigned char data2 = 0xA5;
	int aa = (data2 >> 4) & 2;
	printf("%d\n", aa);

	// ͨ�ú�����ʹ�����������ȡ��ֵ
	int sssss = extractBits(data2,4,6);
	printf("%d\n", sssss);
	return 0;
}