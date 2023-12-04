#pragma once
#include <iostream>
using namespace std;

typedef int Status;
#define LOVERFLOW -2
#define ERROR -1
#define OK	0

/* ����ڵ� */
template <class LElemType>
class LNode {
public:
	LElemType data;		//��ŵ�����
	LNode* next;	    //ֱ�Ӻ�̵�ָ��
};

/* ����ʽʵ�ֵ�ջ */
template <class LElemType>
struct LinkStack {
private:
	LNode<LElemType>* head;			//�����ͷָ��
public:
	LinkStack();					//�����ջ
	~LinkStack();					//�������е�ջ
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
LinkStack<LElemType>::LinkStack()
{
	head = new(nothrow) LNode<LElemType>;		//ͷ���Ľ���
	if (!head)
		exit(LOVERFLOW);
	head->next = NULL;
}

/**
 * @brief ջ������
 * @tparam LElemType ջ��Ԫ������
*/
template <class LElemType>
LinkStack<LElemType>::~LinkStack()
{
	LNode<LElemType>* p = head, * q;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
}

/**
 * @brief ջ�����
 * @tparam LElemType ջ��Ԫ������
*/
template <class LElemType>
Status LinkStack<LElemType>::ClearStack()
{
	LNode<LElemType>* p = head->next, q;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
	head->next = NULL;	//ͷ���ָ���
}

/**
 * @brief ȡջ��Ԫ��
 * @tparam LElemType ջ��Ԫ������
 * @param e ȡ��ջ��Ԫ��ֵ
*/
template <class LElemType>
Status LinkStack<LElemType>::Top(LElemType& e)
{
	if (!head->next)
		return ERROR;
	e = head->next->data;
	return OK;
}

/**
 * @brief ����ջ��Ԫ��
 * @tparam LElemType ջ��Ԫ������
 * @param e ������ջ��Ԫ��
*/
template <class LElemType>
Status LinkStack<LElemType>::Pop(LElemType& e)
{
	if (!head->next)
		return ERROR;
	LNode<LElemType>* p;
	p = head->next;
	e = p->data;
	head->next = p->next;
	delete p;
	return OK;
}

/**
 * @brief ��Ԫ����ջ
 * @tparam LElemType ջ��Ԫ������
 * @param e ��ջ��Ԫ��
*/
template <class LElemType>
Status LinkStack<LElemType>::Push(LElemType e)
{
	LNode<LElemType>* q;
	q = new(nothrow) LNode<LElemType>;
	if (!q)
		exit(LOVERFLOW);
	q->data = e;
	q->next = head->next;
	head->next = q;
	return OK;
}

/**
 * @brief ջ�Ƿ�Ϊ��
 * @tparam LElemType ջ��Ԫ������
*/
template <class LElemType>
bool LinkStack<LElemType> ::StackEmpty()
{
	return head->next == NULL;
}