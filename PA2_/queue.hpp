#pragma once
#include <iostream>
using namespace std;

#define OK 0
#define QERROR -1
#define QOVERFLOW -2
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
	int QueueLength();		//��ȡ���г���
	Status EnQueue(QElemType e);		//��Ԫ�����
	Status DeQueue(QElemType& e);		//����Ԫ�س���
	Status GetHead(QElemType& e);		//��ȡ����Ԫ��
	Status ClearQueue();	//��ն���
	bool QueueEmpty();		//�ж϶����Ƿ�Ϊ��
	Status PrintQueue(ostream& out);	//�Ӷ�����һ���Ԫ��
};

template <class QElemType>
SqQueue <QElemType>::SqQueue(int maxqsize)
{
	MAXQSIZE = maxqsize + 1;  //��һ��λ�����������Ϳ�
	base = new(nothrow) QElemType[MAXQSIZE];
	if (!base)
		exit(QOVERFLOW);
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
		return QERROR;
	base[rear] = e;
	rear = (rear + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::DeQueue(QElemType& e)
{
	if (front == rear)
		return QERROR;
	e = base[front];
	front = (front + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::GetHead(QElemType& e)
{
	if (front == rear)
		return QERROR;
	e = base[front];
	return OK;
}

template <class QElemType>
bool SqQueue <QElemType>::QueueEmpty()
{
	return front == rear;
}

template <class QElemType>
Status SqQueue<QElemType>::PrintQueue(ostream& out)
{
	if (front == rear) {
		out << "Queue is Empty." << endl;
		return QERROR;
	}

	for (int i = front; i != rear; i = (i + 1) % MAXQSIZE)
		out << base[i] << " ";
	out << endl;
	return OK;
}