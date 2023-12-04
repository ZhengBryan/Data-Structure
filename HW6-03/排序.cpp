/**
 * @file    template.cpp
 * @name    p57ģ�����
 * @date    2022-11-22
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
int newarr[100010];
using namespace std;

/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
class Solution {
private:

	/* �鲢���� */
		/**
		 * @brief ��������������кϲ�
		 * @param arr ������е�����
		 * @param l ǰһ�����еĿ�ʼ
		 * @param m �����еķָ��±�
		 * @param r ��һ�����еĽ���
		*/
	void Merge(vector<int>& arr, int l, int m, int r)
	{
		int i = l, j = m + 1, k;
		//�˴�k��ʼֵ��l����1
		for (k = l; i <= m && j <= r; k++) {
			//�ڴ˴�ȡ��
			if (arr[i] <= arr[j])
				newarr[k] = arr[i++];
			else
				newarr[k] = arr[j++];
		}

		while (i <= m)
			newarr[k++] = arr[i++];

		while (j <= r)
			newarr[k++] = arr[j++];

		for (int i = l; i <= r; i++)
			arr[i] = newarr[i];
	}

	/**
	 * @brief �鲢����
	 * @param arr ���������
	 * @param l ��ʱ���������е�������±�
	 * @param r ��ʱ���������е����Ҳ��±�
	*/
	void MergeSort(vector<int>& arr, int l, int r)
	{
		if (l == r)
			return;
		else {
			int m = (l + r) / 2;
			MergeSort(arr, l, m);
			//ע��˴��� m+1
			MergeSort(arr, m + 1, r);
			Merge(arr, l, m, r);
		}
	}

	/* �������� */

	/**
	 * @brief ����ȡ�з�������
	 * @param L �����vector
	 * @param low ��ǰ�����������ʼ�±�
	 * @param high ��ǰ��������н����±�
	*/
	void findpivotkey(vector<int>& L, int low, int high)
	{
		int min, max, mid = (low + high) / 2;
		if (L[low] < L[high]) {
			min = low;
			max = high;
		}
		else {
			min = high;
			max = low;
		}

		if (L[mid] < L[min])
			min = mid;

		if (L[mid] > L[max])
			max = mid;

		mid = low + high + mid - min - max;
		swap(L[low], L[mid]);
		return;
	}

	/**
	 * @brief ���������򣩽�����ǰ�󰴴�С�ָ�
	 * @param L �����vector
	 * @param low ��ǰ�����������ʼ�±�
	 * @param high ��ǰ��������н����±�
	 * @return ������±�
	*/
	int Partition(vector<int>& L, int low, int high)
	{
		findpivotkey(L, low, high);
		int pivotkey = L[low];
		while (low < high) {
			while (low < high && L[high] > pivotkey)
				high--;
			swap(L[low], L[high]);
			while (low < high && L[low] <= pivotkey)
				low++;
			swap(L[high], L[low]);
		}

		return low;
	}

	/**
	 * @brief ��������
	 * @param L �����vector
	 * @param low ��ǰ�����������ʼ�±�
	 * @param high ��ǰ��������н����±�
	*/
	void Qsort(vector<int>& L, int low, int high)
	{
		if (low < high) {
			int mid = Partition(L, low, high);
			Qsort(L, low, mid - 1);
			Qsort(L, mid + 1, high);
		}
		return;
	}

	void QuickSort(vector<int>& L)
	{
		Qsort(L, 0, L.size() - 1);
		return;
	}



	/* �鲢���� */
	/**
	 * @brief ��������������кϲ�
	 * @param arr ������е�����
	 * @param l ǰһ�����еĿ�ʼ
	 * @param m �����еķָ��±�
	 * @param r ��һ�����еĽ���
	*/
	void Merge(vector<int>& arr, int l, int m, int r)
	{
		int i = l, j = m + 1, k;
		//�˴�k��ʼֵ��l����1
		for (k = l; i <= m && j <= r; k++) {
			//�ڴ˴�ȡ��
			if (arr[i] <= arr[j])
				newarr[k] = arr[i++];
			else
				newarr[k] = arr[j++];
		}

		while (i <= m)
			newarr[k++] = arr[i++];

		while (j <= r)
			newarr[k++] = arr[j++];

		for (int i = l; i <= r; i++)
			arr[i] = newarr[i];
	}

	/**
	 * @brief �鲢����
	 * @param arr ���������
	 * @param l ��ʱ���������е�������±�
	 * @param r ��ʱ���������е����Ҳ��±�
	*/
	void MergeSort(vector<int>& arr, int l, int r)
	{
		if (l == r)
			return;
		else {
			int m = (l + r) / 2;
			MergeSort(arr, l, m);
			//ע��˴��� m+1
			MergeSort(arr, m + 1, r);
			Merge(arr, l, m, r);
		}
	}

	/* �������� */

	/**
	 * @brief ����ȡ�з�������
	 * @param L �����vector
	 * @param low ��ǰ�����������ʼ�±�
	 * @param high ��ǰ��������н����±�
	*/
	void findpivotkey(vector<int>& L, int low, int high)
	{
		int min, max, mid = (low + high) / 2;
		if (L[low] < L[high]) {
			min = low;
			max = high;
		}
		else {
			min = high;
			max = low;
		}

		if (L[mid] < L[min])
			min = mid;

		if (L[mid] > L[max])
			max = mid;

		mid = low + high + mid - min - max;
		swap(L[low], L[mid]);
		return;
	}

	/**
	 * @brief ���������򣩽�����ǰ�󰴴�С�ָ�
	 * @param L �����vector
	 * @param low ��ǰ�����������ʼ�±�
	 * @param high ��ǰ��������н����±�
	 * @return ������±�
	*/
	int Partition(vector<int>& L, int low, int high)
	{
		findpivotkey(L, low, high);
		int pivotkey = L[low];
		while (low < high) {
			while (low < high && L[high] > pivotkey)
				high--;
			swap(L[low], L[high]);
			while (low < high && L[low] <= pivotkey)
				low++;
			swap(L[high], L[low]);
		}

		return low;
	}

	/**
	 * @brief ��������
	 * @param L �����vector
	 * @param low ��ǰ�����������ʼ�±�
	 * @param high ��ǰ��������н����±�
	*/
	void Qsort(vector<int>& L, int low, int high)
	{
		if (low < high) {
			int mid = Partition(L, low, high);
			Qsort(L, low, mid - 1);
			Qsort(L, mid + 1, high);
		}
		return;
	}

	void QuickSort(vector<int>& L)
	{
		Qsort(L, 0, L.size() - 1);
		return;
	}
	/**
	 * @brief ����s��m�Ķ�ʹ������ѵ�����
	 * @param H ��
	 * @param s ��ʼ�±�
	 * @param m ��ֹ�±�
	*/
	void HeapAdjust(vector<int>& H, int s, int m)
	{
		int record = H[s];
		for (int j = 2 * s; j <= m; j *= 2) {
			//�ж���/�� ����?
			if (j < m && H[j] < H[j + 1])
				j++;
			if (record >= H[j])
				break;
			H[s] = H[j];
			s = j;
		}
		H[s] = record;
	}

	/**
	 * @brief ������
	 * @param H �������������
	*/
	void HeapSort(vector<int>& H)
	{
		int Hlength = H.size();
		//����һλ
		H.push_back(0);
		for (int i = Hlength; i > 0; i--)
			H[i] = H[i - 1];

		for (int i = Hlength / 2; i > 0; i--)
			HeapAdjust(H, i, H.size());

		for (int i = Hlength; i > 1; --i) {
			swap(H[1], H[i]);
			HeapAdjust(H, 1, i - 1);
		}

		for (int i = 0; i < Hlength; i++)
			H[i] = H[i + 1];
		H.pop_back();
		//ɾ��һλ
	}

	/**
	 * @brief ϣ�������ĳһ��
	 * @param nums ���������
	 * @param dk ����
	*/
	void ShellInsert(vector<int>& nums, int dk)
	{
		int rec, j;
		for (int i = dk; i < nums.size(); i++) {
			if (nums[i] < nums[i - dk]) {
				rec = nums[i];
				for (j = i - dk; j >= 0 && rec < nums[j]; j -= dk)
					nums[j + dk] = nums[j];
				nums[j + dk] = rec;
			}
		}
	}

	/**
	 * @brief ϣ������
	 * @param nums ���������
	*/
	void ShellSort(vector<int>& nums)
	{
		for (int i = nums.size(); i >= 1; i /= 2)
			ShellInsert(nums, i);
	}

public:
	std::vector<int> mySort(std::vector<int>& nums)
	{
		// ������д��Ĵ���
		ShellSort(nums);
		return nums;
	}
};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/

int main()
{
	int n;
	std::cin >> n;
	//������������������
	std::vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		std::cin >> nums[i];
	}
	Solution s;
	std::vector<int> after_sort(s.mySort(nums));
	std::cout << after_sort[0];
	for (int i = 1; i < n; i++) {
		std::cout << ' ' << after_sort[i];
	}
	std::cout << std::endl;
	return 0;
}
