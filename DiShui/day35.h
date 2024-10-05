#pragma once
#include <iostream>
#include <Windows.h>


#define SUCCESS           			 1 // �ɹ�	
#define ERROR_MY            		-1 // ʧ��	
#define MALLOC_ERROR				-2 // �����ڴ�ʧ��	
#define INDEX_ERROR		 			-3 // �����������	

using namespace std;

// Vector��ʵ��
template<class T_ELE>
class Vector
{
public:
	Vector();
	Vector(DWORD dwSize);
	~Vector();

public:
	DWORD	at(DWORD dwIndex, OUT T_ELE* pEle);					//���ݸ����������õ�Ԫ��				
	DWORD   push_back(T_ELE Element);							//��Ԫ�ش洢���������һ��λ��				
	VOID	pop_back();											//ɾ�����һ��Ԫ��				
	DWORD	insert(DWORD dwIndex, T_ELE Element);				//��ָ��λ������һ��Ԫ��				
	DWORD	capacity();											//�����ڲ����ݵ�����£����ܴ洢����Ԫ��				
	VOID	clear();											//�������Ԫ��				
	BOOL	empty();											//�ж�Vector�Ƿ�Ϊ�� ����trueʱΪ��				
	VOID	erase(DWORD dwIndex);								//ɾ��ָ��Ԫ��				
	DWORD	size();												//����VectorԪ�������Ĵ�С				

private:
	BOOL	expand();
private:
	DWORD  m_dwIndex;						//��һ����������	
	DWORD  m_dwIncrement;					//ÿ�����ݵĴ�С	
	DWORD  m_dwLen;							//��ǰ�����ĳ���	
	DWORD  m_dwInitSize;					//Ĭ�ϳ�ʼ����С	
	T_ELE* m_pVector;						//����ָ��	


};

// �޲ι��캯��
template<class T_ELE>
Vector<T_ELE>::Vector() :m_dwInitSize(100), m_dwIncrement(5) 
{

	m_pVector = new T_ELE[m_dwInitSize];
	memset(m_pVector, 0, m_dwInitSize * sizeof(T_ELE));
	m_dwLen = m_dwInitSize;
	m_dwInitSize = m_dwInitSize * sizeof(T_ELE);
	m_dwIndex = 0;}

// �вι��캯��
template<class T_ELE>
Vector<T_ELE>::Vector(DWORD dwSize) : m_dwIncrement(5)
{

	m_pVector = new T_ELE[dwSize];
	memset(m_pVector, 0, sizeof(T_ELE) * dwSize);
	m_dwLen = dwSize;
	m_dwInitSize = sizeof(T_ELE) * dwSize;
	m_dwIndex = 0;
}

// ��������
template<class T_ELE>
Vector<T_ELE>::~Vector()
{
	delete[] m_pVector;
	m_pVector = nullptr;
}

template<class T_ELE>
BOOL Vector<T_ELE>::expand()
{
	DWORD expand_len = m_dwLen + m_dwIncrement;
	T_ELE* temp = nullptr;
	temp = new T_ELE[expand_len];
	memset(temp, 0, sizeof(T_ELE) * expand_len);
	memcpy(temp, m_pVector, sizeof(T_ELE) * m_dwLen);
	delete[] m_pVector;
	m_pVector = temp;
	m_dwLen = expand_len;
	m_dwInitSize = sizeof(T_ELE) * expand_len;
	return 0;
}

template<class T_ELE>
DWORD Vector<T_ELE>::at(DWORD dwIndex, OUT T_ELE* pEle)
{
	if (dwIndex > m_dwIndex)
	{
		cout << "����ֵ����Ԫ�ز����ڣ�����" << endl;
		return ERROR_MY;
	}
	*pEle = *(&m_pVector[dwIndex]);
}

template<class T_ELE>
DWORD Vector<T_ELE>::push_back(T_ELE Element)
{
	if (m_dwIndex >= m_dwLen)
	{
		expand();
	}
	memcpy(&m_pVector[m_dwIndex], &Element, sizeof(Element));
	m_dwIndex++;
	return 0;
}

template<class T_ELE>
VOID Vector<T_ELE>::pop_back()
{
	memset(&m_pVector[--m_dwIndex], 0, sizeof(T_ELE));

}

template<class T_ELE>
DWORD Vector<T_ELE>::insert(DWORD dwIndex, T_ELE Element)
{
	if (dwIndex < m_dwIndex)
	{
		cout << "��λ����������" << endl;
		return ERROR_MY;
	}
	memcpy(&m_pVector[dwIndex], &Element, sizeof(Element));

	return SUCCESS;
}

template<class T_ELE>
DWORD Vector<T_ELE>::capacity()
{
	return (m_dwLen - m_dwIndex) - 1;
}


template<class T_ELE>
BOOL Vector<T_ELE>::empty()
{
	
	bool isEmpty;
	int temp = 0;
	while (true)
	{
		if (*m_pVector != 0)
		{
			break;
		}
		m_pVector++;
		temp++;
	}
	
	if (temp == m_dwLen)
	{
		isEmpty =  true;

	}
	else
	{
		isEmpty = false;
	}
	return isEmpty;
}

template<class T_ELE>
VOID Vector<T_ELE>::erase(DWORD dwIndex)
{
	if (dwIndex >= m_dwIndex)
	{
		throw std::runtime_error("��������Ԫ�ز�����");
	
	}
	memcpy(&m_pVector[dwIndex], &m_pVector[dwIndex + 1], m_dwInitSize - sizeof(T_ELE));
}

template<class T_ELE>
DWORD Vector<T_ELE>::size()
{
	DWORD temp = 0;
	while (true)
	{
		if (*m_pVector != 0)
		{
			temp++;
		}
		else
		{
			break;
		}
		m_pVector++;
	}
	return sizeof(T_ELE) * temp;
}


template<class T_ELE>
void Vector<T_ELE>::clear()
{
	memset(m_pVector, 0, m_dwInitSize);
	m_dwIndex = 0;
}
