#include "./long_long_int.h"

/**
 * @brief ���������޲ι��죨��0��
*/
LONG_LONG_INT::LONG_LONG_INT()
{
	memset(this->number, 0, sizeof(this->number));
	length = 1;
}

/**
 * @brief ͨ��long long���������
 * @param n ��������ֵn
*/
LONG_LONG_INT::LONG_LONG_INT(long long n)
{
	memset(this->number, 0, sizeof(this->number));
	for (int i = 0; ; i++) {
		this->number[i] = n % 10;
		n /= 10;
		if (!n) {
			length = i + 1;
			return;
		}
	}
}

/**
 * @brief ���������* �������˷�
 * @param that ����˷�����һ��������
 * @return �˻�
*/
const LONG_LONG_INT LONG_LONG_INT:: operator*(const LONG_LONG_INT& that) const
{
	LONG_LONG_INT answer;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < that.length; j++) {
			int newn = answer.number[i + j] + this->number[i] * that.number[j];
			answer.number[i + j] = newn % 10;
			answer.number[i + j + 1] += newn / 10;
		}
	}

	//����0
	if ((length == 1 && !number[0]) || (that.length == 1 && !that.number[0])) {
		answer.length = 1;
		return answer;
	}

	answer.length = answer.number[length + that.length - 1] ? length + that.length : length + that.length - 1;
	return answer;
}

/**
 * @brief ���������+ �������ӷ�
 * @param that ����ӷ�����һ��������
 * @return ����ĺ�
*/
const LONG_LONG_INT LONG_LONG_INT:: operator+(const LONG_LONG_INT& that) const
{
	LONG_LONG_INT answer;
	for (int i = 0; i < max(that.length, length); i++) {
		answer.number[i] += number[i] + that.number[i];
		answer.number[i + 1] += answer.number[i] / 10;
		answer.number[i] %= 10;
	}

	answer.length = answer.number[max(that.length, length)] ? max(that.length, length) + 1 : max(that.length, length);
	return answer;
}

/**
 * @brief ����>> �����������
 * @param in ������
 * @param that ����Ĵ���������
*/
istream& operator >> (istream& in, LONG_LONG_INT& that)
{
	char input[2048];
	in >> input;

	that.length = strlen(input);

	for (int i = that.length - 1; i >= 0; i--)
		that.number[that.length - 1 - i] = input[i] - '0';

	return in;
}

/**
 * @brief ����<< �����������
 * @param in �����
 * @param that ����Ĵ���������
*/
ostream& operator << (ostream& out, const LONG_LONG_INT& that)
{
	for (int i = that.length - 1; i >= 0; i--)
		out << that.number[i] + 0;		//��������, int���

	return out;
}
