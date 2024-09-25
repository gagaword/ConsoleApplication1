#include <iostream>
#include "day30.h"

using namespace std;


	void DateInfo::SetDay(int day)
	{
		this->day = day;
	}

	int DateInfo::GetDay()
	{
		return this->day;
	}

	void DateInfo::SetMoth(int moth)
	{
		this->moth = moth;
	}

	int DateInfo::GetMoth()
	{
		return this->moth;
	}

	void DateInfo::SetYear(int year)
	{
		this->year = year;
	}

	int DateInfo::Getyear()
	{
		return this->year;
	}


struct TimeInfo:DateInfo
{
	int hour;
	int Miunte;
	int Second;
	
	TimeInfo(int hour, int Miunte, int Second)
	{
		this->hour = hour;
		this->Miunte = Miunte;
		this->Second = Second;
	}
	TimeInfo()
	{
		this->hour = 14;
		this->Miunte = 2;
		this->Second = 33;
	}
	int Gethour()
	{
		return this->hour;
	}
	int GetMiunte()
	{
		return this->Miunte;
	}
	int GetSecond()
	{
		return this->Second;
	}
};
void Test()
{
	DateInfo dateInfo;
	TimeInfo timeInfo;

	DateInfo* p = &timeInfo;
	printf("%d\n", p->day);

	// �����޷�ͨ������ֱ�ӷ��������Ա
	//printf("%d", p->hour);

	// ����ָ���Լ���������������
	TimeInfo* pTime = &timeInfo;
	cout << pTime->day << endl;;
	cout << pTime->hour << endl;

	// ��Ϊ�̳���DateInfo�����Կ��Է��ʸ���ĳ�Ա�����ͳ�Ա����
	cout << pTime->GetDay() << endl;
}

struct Peront
{
	// ˽�л�
private:
	int age;
	// ���л�
public:
	int sex;

	Peront(int age, int sex)
	{
		this->age = age;
		this->sex = sex;
	}

	Peront()
	{
		this->age = 20;
		this->sex = 3000;
	}

	void SetAge(int age)
	{
		if (age >= 200)
		{
			cout << "����" << endl;
			_exit(0);
		}
		this->age = age;
	}

};

struct Student:Peront
{
	int id;
	Student(int id)
	{
		this->id = id;
	}
	Student()
	{
		this->id = 2024;
	}
};
void Test_4()
{
	Peront peront(100,200);
	Student student(3);

	Student* pStudent = &student;

	cout << pStudent->sex << endl;
	
	cout << pStudent->id << endl;
	
	// student �Ĵ�СΪ12��private��Ȼ��˽�л��ĵ����ǻᱻ�̳У�ֻ�ǲ��ܷ���
	cout << sizeof(student) << endl;

	// cout << pStudent->age << endl;
	// ͨ���������ʸ����˽�б���
	//pStudent->SetAge(200);
	

	// ��Ȼʹ����private�����Ʊ������ʣ������ǿ���ʹ��ָ����ͻ��������ƣ���ǰ���Ѿ�֪��˽�л��������ǻᱻ�̳�
	int* pPeront = (int*)&peront;
	int GetAge = *pPeront;
	cout << GetAge << endl;

	// ͨ�������ָ��Ҳ���Է��ʵ������˽�б���
	int* pStudent1 = (int*)&student;
	cout << *pStudent1 << endl;

}


struct X
{
	int a;
	int b;
};
struct Y :X
{
	int c;
	int d;
};
struct Z :Y
{
	int e;
	int f;
};

void Test_3()
{
	Z z;

	z.a = 1;
	z.b = 2;
	z.c = 3;
	z.d = 4;
	z.e = 5;
	z.f = 6;

	printf("%d\n", sizeof(z));

}
struct MyString 
{
	
	char* myString;

	MyString(char* myString)
	{
		this->myString = (char*)malloc(1024);
		strcpy_s(this->myString, 1024, myString);
	}

	MyString()
	{
		myString = (char*)malloc(1024);
	}


	// ��������
	~MyString()
	{
		free(myString);
		cout << "��������ִ��" << endl;
	}

	void SetString(char* myString)
	{
		strcpy_s(this->myString, 1024, myString);
	}
	void printString()
	{
		cout << myString << endl;
	}
	void AddendString(char* myString)
	{
		strcat_s(this->myString, 1024, myString);
	}

	int GetSize()
	{
		return strlen(myString);
	}
};

void Test_two()
{
	MyString mystring;
	mystring.SetString((char*)"ABCD");
	mystring.printString();
	mystring.AddendString((char*)"EF");
	mystring.printString();

	cout << mystring.GetSize() << endl;
}


class TestClass
{
public:
	int age;
	int sex;
	int id;

	TestClass(int age, int sex, int id)
	{
		this->age = age;
		this->sex = sex;
		this->id = id;
	}
	TestClass()
	{
		this->age = 0;
		this->sex = 0;
		this->id = 0;
	}

};

class MyClassTest:public TestClass
{
public:
	int carid;
	MyClassTest(int carid)
	{
		this->carid = carid;
	}
	MyClassTest()
	{
		this->carid = 0;
	}
	void PrintData()
	{
		cout << this->age << endl;
		cout << this->id << endl;
	}
};

void Test_5()
{
	TestClass testclass;
	testclass.age = 0;

	MyClassTest myclasstest;

	// ���ɷ���,�������������Ȩ�޿���
	myclasstest.id = 10;

	myclasstest.PrintData();

}

int main()
{
	//Test();
	//Test_two();
	//Test_3();
	//Test_4();
	Test_5();
	return 0;
}