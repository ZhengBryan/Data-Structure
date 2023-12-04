#include <iostream>
#include <cstring>
#include <cmath>
#define ERROR -1
using namespace std;

/**
 * @brief �ж��Ƿ�������
 * @param n �жϵ���
*/
bool isPrime(int n)
{
	if (n == 1)
		return false;
	for (int i = 2; i <= sqrt(n); i++)
		if (n % i == 0)
			return false;
	return true;
}

/**
 * @brief ��ȡ�ַ���keyֵ
 * @param str �ַ���
 * @param mod ģ��
*/
int getKey(char* str, int mod)
{
	const int weight = 37;
	int key = 0;
	for (int i = 0; str[i]; i++) {
		key *= weight;
		key += str[i];
		key %= mod;
	}
	return key;
}

/**
 * @brief ����̽����ɢ��
 * @param hash ��¼�Ƿ��Ѿ�ռ�õ�����
 * @param key ԭ�ȵ�key
 * @param mod ģ��
 * @return �����ͻ���key
*/
int avoidConflict(bool* hash, int key, int mod)
{
	if (!hash[key]) {
		hash[key] = true;
		return key;
	}
	int newkey;
	bool breakout = false;
	for (int i = 1; i <= mod/2; i++) {
		for (int j = 1; j >= -1; j -= 2) {
			newkey = (((key + j * i * i) % mod) + mod) % mod;
			if (!hash[newkey]) {
				breakout = true;
				break;
			}
		}
		if (breakout)
			break;
	}
	if (!hash[newkey]) {
		hash[newkey] = true;
		return newkey;
	}
	else
		return ERROR;
}

int main()
{
	int n, mod;
	//�洢��keyֵ�Ƿ�ռ��
	bool hash[10010];
	memset(hash, 0, sizeof(bool) * 10010);
	cin >> n >> mod;

	//ģ��ת��
	while (!isPrime(mod))
		mod++;

	for (int i = 0; i < n; i++) {
		char str[105];
		cin >> str;
		int key = getKey(str, mod);
		int ret = avoidConflict(hash, key, mod);
		if (ret == ERROR)
			cout << "- ";
		else
			cout << ret << " ";
	}

	return 0;
}