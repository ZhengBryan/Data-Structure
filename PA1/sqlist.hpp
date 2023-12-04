#pragma once
#include <iostream>
#include <cstring>
#define LIST_INIT_SIZE	50
#define LISTINCREMENT	10
typedef int Status;
#define LOVERFLOW	-1
#define ERROR		-2
#define OK			0
using namespace std;

template <class SqList_ElemType>
/* ˳��� */
class SqList {
	SqList_ElemType* base;		//ͷָ��
	int	length;					//��
	int	listsize;				//����ı�ռ�
public:
	//˳���Ľ���
	SqList();
	//˳��������
	~SqList();
	//���ص��ں� Ŀ�����ڸ���˳���ʱ������ǳ���� ��ֹ����delete
	const SqList& operator=(const SqList& that);
	//���
	int ListLength();
	//����Ԫ��
	Status ListInsert(int i, SqList_ElemType e);
	//ȡ����Ԫ��
	Status GetElem(int i, SqList_ElemType& e);
	//����Ԫ���Ƿ���˳�����
	bool IsInList(const SqList_ElemType& e);
};


/**
 * @brief ˳���Ľ���
 * @tparam SqList_ElemType ˳���Ԫ��
*/
template <class SqList_ElemType>
SqList<SqList_ElemType>::SqList()
{
	this->base = new(nothrow) SqList_ElemType[LIST_INIT_SIZE];
	if (!this->base)
		exit(LOVERFLOW);
	this->length = 0;
	this->listsize = LIST_INIT_SIZE;
}


/**
 * @brief ˳��������
 * @tparam SqList_ElemType ˳���Ԫ��
*/
template <class SqList_ElemType>
SqList<SqList_ElemType>::~SqList()
{
	if (this->base)
		delete[] this->base;
	this->base = NULL;
	this->length = 0;
	this->listsize = 0;

}


/**
 * @brief ���ص��ں� Ŀ�����ڸ������Ա�ʱ������ǳ���� ��ֹ����delete
 * @tparam SqList_ElemType ˳���Ԫ��
 * @param that ��ֵ����һ��˳���
 * @return ��ֵ����
*/
template <class SqList_ElemType>
const SqList<SqList_ElemType>& SqList<SqList_ElemType>::SqList::operator=(const SqList<SqList_ElemType>& that)
{
	length = that.length;
	listsize = that.listsize;
	base = new(nothrow) SqList_ElemType[listsize];
	if (!base)
		exit(LOVERFLOW);
	memcpy(base, that.base, listsize * sizeof(SqList_ElemType));
	return *this;
}


/**
 * @brief ��˳����
 * @tparam SqList_ElemType ˳���Ԫ��
 * @return ��
*/
template <class SqList_ElemType>
int SqList<SqList_ElemType>::ListLength()
{
	return this->length;
}


/**
 * @brief ��˳���λ��i������Ԫ��
 * @tparam SqList_ElemType ˳���Ԫ��
 * @param i ����λ��i
 * @param e �������Ԫ��
 * @return ����״̬
*/
template <class SqList_ElemType>
Status SqList<SqList_ElemType>::ListInsert(int i, SqList_ElemType e)
{
	if (i < 1 || i > this->length + 1)
		return ERROR;
	if (this->length >= this->listsize) {
		SqList_ElemType* newbase = new SqList_ElemType[this->length + LISTINCREMENT];
		if (!newbase)
			exit(LOVERFLOW);
		memcpy(newbase, this->base, this->length * sizeof(SqList_ElemType));
		delete[] this->base;
		this->base = newbase;
		this->listsize += LISTINCREMENT;
	}
	SqList_ElemType* q = &(this->base[i - 1]);
	for (SqList_ElemType* p = &(this->base[this->length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++this->length;
	return OK;
}


/**
 * @brief ȡ��˳���λ��i��Ԫ��
 * @tparam SqList_ElemType ˳���Ԫ��
 * @param i Ԫ��λ��i
 * @param e ȡ����Ԫ��
 * @return ȡ��״̬
*/
template <class SqList_ElemType>
Status SqList<SqList_ElemType>::GetElem(int i, SqList_ElemType& e)
{
	if (i < 1 || i > this->length)
		return ERROR;
	e = this->base[i - 1];
	return OK;
}

/**
 * @brief ����Ԫ���Ƿ���˳�����
 * @tparam SqList_ElemType ˳���Ԫ��
 * @param e ���ҵ�Ԫ��
 * @return �Ƿ��ڱ���
*/
template <class SqList_ElemType>
bool SqList<SqList_ElemType>::IsInList(const SqList_ElemType& e)
{
	for (int i = 0; i < length; i++) {
		if (base[i] == e)
			return true;
	}
	return false;
}