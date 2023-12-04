#include <iostream>
#include "./sqlist.hpp"
#include "./linklist.hpp"
#define LOVERFLOW	-1
#define ERROR		-2
#define OK			0
#define HASHTABLE_LEN 19997

using namespace std;

template <class Hash_ElemType>
class Hashtable {
private:
	LinkList<Hash_ElemType>* base;
public:
	//���캯�� ��ϣ��Ľ���
	Hashtable();
	//�������� ��ϣ�������
	~Hashtable();
	//�ڹ�ϣ���в�����Ԫ��
	Status TableInsert(const Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e));
	//�ڹ�ϣ���в�������Ԫ��
	Status TableSearch(Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e));
	//�ڹ�ϣ����ɾ������Ԫ��
	Status TableDelete(Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e));
	//�ڹ�ϣ����ȡԪ�ص�λ��(���޸���������)
	Status LocateElem(const Hash_ElemType& e, Hash_ElemType*& ep, int(*GetIndex)(const Hash_ElemType& e));
	//���ҹ�ϣ�����Ƿ��и�Ԫ��
	bool IsInTable(const Hash_ElemType&e, int(*GetIndex)(const Hash_ElemType& e));
};

/**
 * @brief �չ�ϣ��Ľ���
 * @tparam Hash_ElemType ��ϣ���Ԫ������
 * @param len ��ϣ��ĳ���
*/
template <class Hash_ElemType>
Hashtable<Hash_ElemType>::Hashtable()
{
	base = new(nothrow) LinkList<Hash_ElemType>[HASHTABLE_LEN];
	if (!base)
		exit(LOVERFLOW);
}


/**
 * @brief ��ϣ�������
 * @tparam Hash_ElemType ��ϣ���Ԫ������
*/
template <class Hash_ElemType>
Hashtable<Hash_ElemType>::~Hashtable()
{
	delete[] base;
}


/**
 * @brief �ڹ�ϣ���в�����Ԫ��
 * @tparam Hash_ElemType ��ϣ���Ԫ������
 * @param e ��ǰ�����Ԫ��
 * @param GetIndex ȡ��keyֵ�±�ĺ���
 * @return �Ƿ�ɹ�����
*/
template <class Hash_ElemType>
Status Hashtable<Hash_ElemType>::TableInsert(const Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return ERROR;
	return base[ret].ListInsert(1, e);
}


/**
 * @brief �ڹ�ϣ���в�������Ԫ�أ����ص�ַ���޸�
 * @tparam Hash_ElemType ��ϣ���Ԫ������
 * @param e ��ǰ���ҵ�Ԫ��
 * @param ep �ҵ���Ԫ�ص�ַ
 * @param GetIndex ȡ��keyֵ�±�ĺ���
 * @return �Ƿ�ɹ�����
*/
template <class Hash_ElemType>
Status Hashtable<Hash_ElemType>::LocateElem(const Hash_ElemType& e, Hash_ElemType*& ep, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return ERROR;
	
	return base[ret].LocatePosition(e, ep);
}


/**
 * @brief �ڹ�ϣ���в�������Ԫ��
 * @tparam Hash_ElemType ��ϣ���Ԫ������
 * @param e ��ǰ���ҵ�Ԫ��
 * @param GetIndex ȡ��keyֵ�±�ĺ���
 * @return �Ƿ�ɹ�����
*/
template <class Hash_ElemType>
Status Hashtable<Hash_ElemType>::TableSearch(Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return ERROR;

	return base[ret].SearchElem(e);
}


/**
 * @brief �ڹ�ϣ����ɾ������Ԫ��
 * @tparam Hash_ElemType ��ϣ���Ԫ������
 * @param e ׼��ɾ����Ԫ��
 * @param GetIndex ȡ��keyֵ�±�ĺ���
 * @return Ԫ�ر����Ƿ����
*/
template <class Hash_ElemType>
Status Hashtable<Hash_ElemType>::TableDelete(Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return ERROR;

	int index = base[ret].LocateElem(e);
	//���в����ڸ�Ԫ��
	if (!index)
		return ERROR;

	return base[ret].ListDelete(index, e);
}


/**
 * @brief �ڹ�ϣ���в���Ԫ���Ƿ����
 * @tparam Hash_ElemType ��ϣ���Ԫ������
 * @param e ��ǰ���ҵ�Ԫ��
 * @param GetIndex ȡ��keyֵ�±�ĺ���
 * @return �Ƿ����
*/
template <class Hash_ElemType>
bool Hashtable<Hash_ElemType>::IsInTable(const Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return false;

	int index = base[ret].LocateElem(e);
	return index;		//�Ƿ���ڶ�Ӧ��������
}