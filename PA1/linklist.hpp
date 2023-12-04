#pragma once
typedef int Status;
#define LOVERFLOW	-1
#define ERROR		-2
#define OK			0
using namespace std;

/* ����ڵ� */
template <class LinkList_ElemType>
class LNode {
public:
	LinkList_ElemType data;		//��ŵ�����
	LNode* next;				//ֱ�Ӻ�̵�ָ��
};

/* ���� */
template <class LinkList_ElemType>
class LinkList {
	LNode <LinkList_ElemType>* base;
	typedef LNode<LinkList_ElemType> LNode_;
	typedef LNode<LinkList_ElemType>* LNodep;
public:
	//������ͷ�ڵ�Ŀ�����
	LinkList();
	//�������
	~LinkList();
	//����Ԫ��
	Status ListInsert(int i, const LinkList_ElemType& e);
	//ɾ��Ԫ��
	Status ListDelete(int i, LinkList_ElemType& e);
	//ȡԪ��
	Status GetElem(int i, LinkList_ElemType& e);
	//ȡԪ�ص�ַ
	Status LocatePosition(const LinkList_ElemType& e, LinkList_ElemType*& ep);
	//���ص�һ�������и�Ԫ�ص�index �������ڷ���NULL
	int LocateElem(const LinkList_ElemType& e);
	//�ҵ���һ�������еĸ�Ԫ�أ����滻(����Ԫ��=��������ڲ�����ϸ��Ϣ)
	Status SearchElem(LinkList_ElemType& e);
};

/**
 * @brief ������ͷ�ڵ�Ŀ�����
 * @tparam LinkList_ElemType ����Ԫ��
*/
template <class LinkList_ElemType>
LinkList<LinkList_ElemType>::LinkList()
{
	this->base = new(nothrow) LNode_;
	if (!base)
		exit(LOVERFLOW);
	base->next = NULL;   //��ͷ�ڵ�Ŀ�����
}

/**
 * @brief ���������
 * @tparam LinkList_ElemType ����Ԫ��
*/
template <class LinkList_ElemType>
LinkList<LinkList_ElemType>::~LinkList()
{
	LNodep p = base, q;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}

}

/**
 * @brief ��������λ��i������Ԫ��
 * @tparam LinkList_ElemType ����Ԫ��
 * @param i λ��i
 * @param e �����Ԫ��
 * @return ����״̬
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::ListInsert(int i, const LinkList_ElemType& e)
{
	LNodep p = base;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
		return ERROR;
	LNodep s = new(nothrow)LNode_;
	if (!s)
		return LOVERFLOW;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}


/**
 * @brief ��������λ��i��ɾ��Ԫ��
 * @tparam LinkList_ElemType ����Ԫ��
 * @param i ɾ��λ��i
 * @param e ȡ��ɾ����Ԫ��
 * @return ɾ��״̬
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::ListDelete(int i, LinkList_ElemType& e)
{
	LNodep p = base, q;
	int j = 0;
	while (p->next && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	delete q;
	return OK;
}


/**
 * @brief ȡ��������λ��i����Ԫ��
 * @tparam LinkList_ElemType ����Ԫ�� 
 * @param i Ԫ�ص�λ��i
 * @param e ȡ����Ԫ��
 * @return ȡ��״̬
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::GetElem(int i, LinkList_ElemType& e)
{
	LNodep p = base->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;
	e = p->data;
	return OK;
}


/**
 * @brief ȡ����������ӦԪ�صĵ�ַ
 * @tparam LinkList_ElemType ����Ԫ��
 * @param e ��ȡ����ַ��Ԫ��
 * @param ep ȡ����Ԫ�ص�ַ
 * @return ȡ��״̬
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::LocatePosition(const LinkList_ElemType& e, LinkList_ElemType*& ep)
{
	LNodep p = base->next;
	while (p) {
		if (p->data == e) {
			ep = &p->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR;  //û�и�Ԫ��
}


/**
 * @brief ���ص�һ�������и�Ԫ�ص�index �������ڷ���NULL
 * @tparam LinkList_ElemType ����Ԫ��
 * @param e ���ҵ�Ԫ��
 * @return ����״̬
*/
template <class LinkList_ElemType>
int LinkList<LinkList_ElemType>::LocateElem(const LinkList_ElemType& e)
{
	LNodep p = base;
	int j = 0;
	while (p->next) {
		p = p->next;
		++j;
		if (p->data == e) {
			return j;
		}
	}
	return NULL;
}

/**
 * @brief ��Ԫ�ص���ϸ��Ϣ(ͨ������=ͨ��ĳ���ṹ���Ա�����ҵ���ӦԪ�� ֱ��ȡ��������Ϣ)
 * @tparam LinkList_ElemType ����Ԫ��
 * @param e ���ҵ�Ԫ��
 * @return ����״̬
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::SearchElem(LinkList_ElemType& e)
{
	LNodep p = base->next;
	while (p) {
		if (p->data == e) {
			e = p->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR;  //û�и�Ԫ��
}