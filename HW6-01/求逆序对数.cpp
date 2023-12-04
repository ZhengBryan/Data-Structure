#include <iostream>
#include <cstring>
#define MAXN 20005
using namespace std;
int cnt = 0;
//int����������������� ����������
//newarr�����ݴ�merge���������
int arr[MAXN], newarr[MAXN];

/**
 * @brief ��������������кϲ�
 * @param arr ������е�����
 * @param l ǰһ�����еĿ�ʼ
 * @param m �����еķָ��±�
 * @param r ��һ�����еĽ���
*/
void Merge(int arr[], int l, int m, int r)
{
	int i = l, j = m + 1, k;
	//�˴�k��ʼֵ��l����1
	for (k = l; i <= m && j <= r; k++) {
		//�ڴ˴�ȡ��
		if (arr[i] <= arr[j])
			newarr[k] = arr[i++];
		else {
			cnt += m - i + 1;
			newarr[k] = arr[j++];
		}
	}

	while (i <= m)
		newarr[k++] = arr[i++];

	while (j <= r)
		newarr[k++] = arr[j++];

	memcpy(arr + l, newarr + l, (r - l + 1) * sizeof(int));
}

/**
 * @brief �鲢����
 * @param arr ���������
 * @param l ��ʱ���������е�������±�
 * @param r ��ʱ���������е����Ҳ��±�
*/
void MergeSort(int arr[], int l, int r)
{
	if (l == r)
		return;
	else {
		int m = (l + r) / 2;
		MergeSort(arr, l, m);
		//ע��˴��� m+1
		MergeSort(arr, m + 1, r);
		Merge(arr, l, m, r);
		//printf("��ʱlΪ%d, rΪ%d, ����Ϊ", l, r);
		//for (int i = l; i <= r; i++)
		//	cout << arr[i] << " ";
		//cout << endl;
	}
}

int main()
{
	int n;

	while (true) {
		cin >> n;
		if (!n)
			break;
		cnt = 0;
		for (int i = 1; i <= n; i++)
			cin >> arr[i];
		MergeSort(arr, 1, n);
		cout << cnt << endl;
	}
	return 0;
}