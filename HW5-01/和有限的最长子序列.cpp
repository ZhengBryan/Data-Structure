#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

/**
 * @brief ��ǰ׺������
 * @param n ����Ԫ�ظ���
 * @param nums ԭ����
 * @param presum ǰ׺������
*/
void getPrefixSum(int n, int* nums, int* presum)
{
	memset(presum, 0, n * sizeof(int));
	for (int i = 0; i < n; i++) {
		if (i == 0)
			presum[i] = nums[i];
		else
			presum[i] = presum[i - 1] + nums[i];
	}
}

/**
 * @brief ���ֲ�����С����
 * @param n ����Ԫ�ظ���
 * @param nums ǰ׺������
 * @param tgt ��������к�
 * @return 
*/
int searchBin(int n, int* nums, int tgt)
{
	int l = 0, r = n;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (nums[mid] <= tgt)
			l = mid;
		else
			r = mid;
	}

	//���⴦�� ����������Ԫ�ض�С��queries[i]�����
	if (nums[l] > tgt)
		return l - 1;

	return l;
}

int main()
{
	int n, m;
	//nums���ڴ洢��������飬����������
	//preSum���ڴ洢������ǰ׺��
	int nums[1000], preSum[1000];
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		cin >> nums[i];

	//������
	sort(nums, nums + n);

	getPrefixSum(n, nums, preSum);

	
	for (int i = 0; i < m; i++) {
		int query;
		cin >> query;
		cout << searchBin(n, preSum, query) + 1 << " ";
	}

	return 0;
}