#pragma once
#include <iostream>
#include <cstring>
using namespace std;
#define MAXN 1024	//���ŵĴ�����λ��(ʮ����)

//��ʾ����������
class LONG_LONG_INT {
private:
	//��Ŵ�����������
	char number[MAXN];
	//����������
	int length;

public:
	//�޲ι��������(0)
	LONG_LONG_INT();
	//��long long���������
	LONG_LONG_INT(long long n);
	//���ش������ӷ�
	const LONG_LONG_INT operator+ (const LONG_LONG_INT& that) const;
	//���ش������˷�
	const LONG_LONG_INT operator* (const LONG_LONG_INT& that) const;
	//����>> ���������
	friend istream& operator >> (istream& in, LONG_LONG_INT& that);
	//����<< ���������
	friend ostream& operator << (ostream& out, const LONG_LONG_INT& that);
};