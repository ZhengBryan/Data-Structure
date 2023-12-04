#pragma once
#include <iostream>
using namespace std;

#define OK 0
#define ERROR -1
#define OVER_FLOW -2

typedef int Status;

template <class QElemType>
class SqQueue {
private:
	QElemType* base;
	int MAXQSIZE;
	int front;
	int rear;
public:
	SqQueue(int maxqsize);		//�����ն��У����캯����
	~SqQueue();					//���ٶ��У�����������
	int QueueLength();		    //��ȡ���г���
	Status EnQueue(QElemType e);		//��Ԫ�����
	Status DeQueue(QElemType& e);		//����Ԫ�س���
	Status GetHead(QElemType& e);		//��ȡ����Ԫ��
	Status ClearQueue();	//��ն���
	bool QueueEmpty();		//�ж϶����Ƿ�Ϊ��
};

template <class QElemType>
SqQueue <QElemType>::SqQueue(int maxqsize)
{
	MAXQSIZE = maxqsize + 1;  //��һ��λ�����������Ϳ�
	base = new(nothrow) QElemType[MAXQSIZE];
	if (!base)
		exit(OVER_FLOW);
	front = rear = 0;
}

template <class QElemType>
SqQueue <QElemType>::~SqQueue()
{
	if (base)
		delete base;
	front = rear = 0;
}

template <class QElemType>
Status SqQueue <QElemType>::ClearQueue()
{
	front = rear = 0;
	return OK;
}

template <class QElemType>
int SqQueue <QElemType> ::QueueLength()
{
	return (rear - front + MAXQSIZE) % MAXQSIZE;
}

template <class QElemType>
Status SqQueue <QElemType> ::EnQueue(QElemType e)
{
	if ((rear + 1) % MAXQSIZE == front)
		return ERROR;
	base[rear] = e;
	rear = (rear + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::DeQueue(QElemType& e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	front = (front + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::GetHead(QElemType& e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	return OK;
}

template <class QElemType>
bool SqQueue <QElemType>::QueueEmpty()
{
	return front == rear;
}
