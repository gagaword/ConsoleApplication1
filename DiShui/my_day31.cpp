#include <iostream>
#include <Windows.h>

using namespace std;


void Hello()
{
	printf("HelloWorld\n");
}

// ���̳��޺�������(��ӡSub������麯����)
struct Base
{
public:
	virtual void Function_1()
	{
		printf("Base:Function_1...\n");
	}
	virtual void Function_2()
	{
		printf("Base:Function_2...\n");
	}
	virtual void Function_3()
	{
		printf("Base:Function_3...\n");
	}
};

struct Sub:Base
{
public:
	virtual void Function_4()
	{
		printf("Sub:Function_4...\n");
	}
	virtual void Function_5()
	{
		printf("Sub:Function_5...\n");
	}
	virtual void Function_6()
	{
		printf("Sub:Function_6...\n");
	}
};

// �麯��-��ӵ�����ֱ�ӵ���
struct Persont
{
	int x;
	int y;

	Persont()
	{
		this->x = 1;
		this->y = 2;
	}

	// ��ͨ����
	void PuTongFunc()
	{
		printf("PuTongFunc()....\n");
	}

	// �麯��
	virtual void virtualFunction_1()
	{
		printf("virtualFunction_1().....\n");
	}
};

// ���̳��к�������(��ӡSub������麯����)
struct Base1
{
public:
	virtual void Function_1()
	{
		printf("Base:Function_1...\n");
	}
	virtual void Function_2()
	{
		printf("Base:Function_2...\n");
	}
	virtual void Function_3()
	{
		printf("Base:Function_3...\n");
	}
};
struct Sub1 :Base1
{
public:
	virtual void Function_1()
	{
		printf("Sub:Function_1...\n");
	}
	virtual void Function_2()
	{
		printf("Sub:Function_2...\n");
	}
	virtual void Function_6()
	{
		printf("Sub:Function_6...\n");
	}
};


void Test_Persont()
{
	Persont persont;

	// �������
	persont.PuTongFunc();
	//persont.virtualFunction_1();

	// ָ�����
	Persont* pPersont = &persont;
	pPersont->PuTongFunc();
	pPersont->virtualFunction_1();
	cout << sizeof(persont) << endl;

	// ͨ������ָ������麯��
	typedef void(*FuncTion)(void);
	FuncTion fPn;
	fPn = (FuncTion)*((int*)*(int*)&persont);
	fPn();


}

// ��ӡsub���麯����
void Test_Sub()
{
	Sub sub;
	Sub* pSub = &sub;
	pSub->Function_1();
	
	typedef void(*FuncTion)(void);
	FuncTion fPn;

	// �����޸��麯����ַ������������
	// ��ȡĿ�꺯����ַ
	DWORD FuncAddress = (DWORD)&Hello;
	cout << hex << uppercase << FuncAddress << endl;
	fPn = (FuncTion)FuncAddress;
	fPn();


	for (int i = 0; i < 6; i++)
	{
		fPn = (FuncTion) * (((int*)*(int*)&sub) + i);
		// �麯����ַ
		cout << hex << uppercase << *(int*)(((int*)*(int*)&sub) + i) << endl;
		fPn();
	}

}

void Test_Sub1()
{
	Sub1 sub1;
	Sub1* pSub = &sub1;

	pSub->Function_1();
	pSub->Function_2();
	pSub->Function_3();
	pSub->Function_6();

	typedef void(*FuncTion)(void);
	FuncTion fPn;

	for (int i = 0; i < 4; i++)
	{
		fPn = (FuncTion) * (((int*)*(int*)&sub1) + i);
		// �麯����ַ
		cout << hex << uppercase << *(int*)(((int*)*(int*)&sub1) + i) << endl;
		fPn();
	}
}
int main()
{
	//Test_Persont();
	Test_Sub();
	//Test_Sub1();
	return 0;
}