#include<iostream>	

// �ṹ�嶨��
struct coord
{
	int x;
	int y;
	int h;
};


// �ṹ�嶨��
struct roleInfo
{
	int age;
	int sm;
	int mofa;
	int jy;
	char roleName[20];
};

// ȫ�ֱ���
roleInfo testRolr;

// �ṹ�帳ֵ
void roleInfoFuZhi()
{

	testRolr.age = 20;
	testRolr.mofa = 100;
	testRolr.jy = 200;
	testRolr.sm = 100;
	testRolr.roleName[0] = 1;
}

// �ṹ���ȡ
void readRoleInfo()
{
	printf("%d %d %d %d\n", testRolr.age, testRolr.mofa, testRolr.jy, testRolr.sm);
}
// �ṹ����Ϊ����ʱ���ݲ���
void testStructParr(coord cd)
{
	
}

// �ṹ����Ϊ����ֵ
coord testScructRet() 
{
	coord cd;
	cd.x = 10;
	cd.y = 20;
	cd.h = 30;
	return cd;
}


/*
	1������һ���ṹ��Gamer�����洢һ����Ϸ�еĽ�ɫ����Ϣ������Ѫֵ���ȼ����������Ϣ						
						
Ҫ��						
						
	(1) ���������Щ��Ϣ�������					
						
	(2) ����Щ�����������У�����Ҫ��һ����Ա�ǽṹ������					
*/
struct Gamer
{
	int hp;
	int gongJiLi;
	int yiDong;
	int grade;
	coord cord;
	char roleName[20];
};

Gamer gamer;

// 2������һ������������������ṹ�������ֵ.
void GamerInfo() 
{
	gamer.hp = 100;
	gamer.gongJiLi = 2000;
	gamer.yiDong = 300;
	gamer.grade = 20;
	gamer.roleName[0] = 'A';
	gamer.cord.x = 222;
	gamer.cord.y = 333;
	gamer.cord.h = 444;
}

//3������һ��������������ʾ����ṹ����������г�Ա��Ϣ.
void PrintfGamer()
{
	printf("%d %d %d %d %d %d %d %c", gamer.hp, gamer.gongJiLi, gamer.yiDong, gamer.grade, gamer.cord.x, gamer.cord.y, gamer.cord.h, gamer.roleName[0]);
}

int main()
{
	roleInfoFuZhi();
	readRoleInfo();

	// ���ݲ���
	coord cd;
	cd.x = 10;
	cd.y = 20;
	cd.h = 30;
	testStructParr(cd);

	// �ṹ����Ϊ����ֵ
	coord cd2 = testScructRet();


	GamerInfo();
	PrintfGamer();
	return 0;
}