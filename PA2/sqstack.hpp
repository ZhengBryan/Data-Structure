#pragma once
#include <iostream>
using namespace std;

#define STACK_INIT_SIZE 100000
#define STACKINCREMENT 10

typedef int Status;
#define SOVERFLOW -2
#define ERROR -1
#define OK	0

/* ˳���ʽʵ�ֵ�ջ */
template <class LElemType>
struct SqStack {
private:
	LElemType* base;
	LElemType* top;
	int stacksize;
public:
	SqStack();					//�����ջ
	~SqStack();					//�������е�ջ
	Status ClearStack();		//������ջ�ÿ�ջ
	Status Top(LElemType& e);	//ȡջ��Ԫ��
	Status Pop(LElemType& e);	//����ջ��Ԫ��
	Status Push(LElemType e);	//��Ԫ����ջ
	bool StackEmpty();			//�Ƿ�Ϊ��ջ
};

/**
 * @brief �����ջ
 * @tparam LElemType ջ��Ԫ������
*/
template <class LElemType>
SqStack<LElemType>::SqStack()
{
	base = new(nothrow) LElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
}

/**
 * @brief ջ������
 * @tparam LElemType ջ��Ԫ������
*/
template <class LElemType>
SqStack<LElemType>::~SqStack()
{
	if (base)
		delete base;
	stacksize = 0;
}

/**
 * @brief ջ�����
 * @tparam LElemType ջ��Ԫ������
*/
template <class LElemType>
Status SqStack<LElemType>::ClearStack()
{
	//������ԭ�пռ�
	if (base)
		delete base;
	//��������
	base = new(nothrow) LElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
	return OK;
}

/**
 * @brief ȡջ��Ԫ��
 * @tparam LElemType ջ��Ԫ������
 * @param e ȡ��ջ��Ԫ��ֵ
*/
template <class LElemType>
Status SqStack<LElemType>::Top(LElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(top - 1);
	return OK;
}

/**
 * @brief ����ջ��Ԫ��
 * @tparam LElemType ջ��Ԫ������
 * @param e ������ջ��Ԫ��
*/
template <class LElemType>
Status SqStack<LElemType>::Pop(LElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(--top);
	return OK;
}

/**
 * @brief ��Ԫ����ջ
 * @tparam LElemType ջ��Ԫ������
 * @param e ��ջ��Ԫ��
*/
template <class LElemType>
Status SqStack<LElemType>::Push(LElemType e)
{
	if (top - base >= stacksize) {
		LElemType* newbase = new(nothrow) LElemType[stacksize + STACKINCREMENT];
		if (!newbase)
			exit(SOVERFLOW);
		memcpy(newbase, base, sizeof(LElemType) * stacksize);
		delete base;
		base = newbase;
		top = base + stacksize;
		stacksize += STACKINCREMENT;
	}
	*top = e;
	top++;
	return OK;
}

/**
 * @brief ջ�Ƿ�Ϊ��
 * @tparam LElemType ջ��Ԫ������
*/
template <class LElemType>
bool SqStack<LElemType> ::StackEmpty()
{
	return base == top;
}