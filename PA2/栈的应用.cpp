#include <iostream>
#include <iomanip>
#include <conio.h>
#include "./long_long_int.h"
#include "./sqstack.hpp"
#include "./linkstack.hpp"
using namespace std;

/* ��ջ���ⷽʽģ�⺯����ŵ���Ϣ */
struct Data {
	int n;					//����Ĳ���, ��ʾ��ǰ����n
	int returnAddress;		//�����ķ��ص�ַ �˴�ʵ�����ڱ�ʾ�ú������е���ģ��0/1
	Data(){					//�޲ι��캯��
		n = 1;
		returnAddress = 0;
	};					
	Data(int _n, int _ra)	//˫�ι��캯��
	{
		n = _n;
		returnAddress = _ra;
	}
};

/**
 * @brief �ݹ鷽ʽ��׳�
 * @param n ��n!
 * @return �׳˽��
*/
LONG_LONG_INT Factorial_1(int n)
{
	if (n == 1)
		return 1;
	else
		return LONG_LONG_INT(n) * Factorial_1(n - 1);
}

/**
 * @brief ջ���ⷽʽ��׳�
 * @tparam stack ջ������
 * @param n ��n!
 * @param function ��ź�����Ϣ��ջ
 * @return �׳˽��
*/
template <class stack>
LONG_LONG_INT Factorial_2(int n, stack& function)
{
	LONG_LONG_INT ret;		  //ģ��ͨ���Ĵ������ݵĸ�����������ֵ

	function.Push({ n, 0 });  //ģ���һ��������main����
	while (!function.StackEmpty()) {
		Data now;
		function.Top(now);
		switch (now.returnAddress) {
			//�ݹ���õĲ���
			case 0:
				function.Pop(now);
				if (now.n > 1) {
					function.Push({ now.n, 1 });		//�����ֳ�
					function.Push({ now.n - 1, 0 });	//������һ��
				}
				else {
					ret = 1;		//����
				}
				break;
			//���ݵĲ���
			case 1:
				function.Pop(now);						//�ָ��ֳ�
				ret = ret * LONG_LONG_INT(now.n);		//���㷵��ֵ
				break;
		}
	}
	
	return ret;
}

/**
 * @brief �ȴ��س�����
 * @param prompt ��ʾ��
*/
void wait_for_enter(const char* prompt)
{
	cout << endl << prompt << ",�밴�س�������";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

/**
 * @brief ���ӻ��˵�����
 * @return ѡ��Ĳ˵���
*/
int Menu()
{
	//system("mode con: cols=83 lines=30");
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\t   PA2-ջ��Ӧ��" << endl;

	cout << endl << endl;
	cout << "\t\t\t\t    �˵�ѡ��" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t1\t|\t2\t|\t3\t|\t0\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|   ˳���ջ\t|     ����ջ\t|    ��ͨ�ݹ�\t|    �˳���ʾ\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl << endl << endl;
	cout << "\t\t\t     [�밴��Ӧ����ѡ����]" << endl;
	cout << "\t\t\t\t\t";
	while (char ch = _getch())
		if (ch >= '0' && ch <= '7')
			return ch - '0';
	return 0;
}

int main()
{
	LinkStack<Data> linkstack;
	SqStack<Data> sqstack;
	int ret;
	int n;
	while (ret = Menu()) {
		switch (ret){
			case 1:
				system("cls");
				cout << "------����(˳���)ջ���ⷽʽ����n�Ľ׳�-----" << endl << endl;
				cout << "��������׳˵����ֵ" << endl;
				cin >> n;
				wait_for_enter("��ʾ������ʼ");
				cout << "n\t�׳˽��" << endl;
				cout << "------------------------------------" << endl;
				for (int i = 1; i <= n; i++)
					cout << i << "\t" << Factorial_2(i, sqstack) << endl;
				wait_for_enter("��ʾ���");
				system("cls");
				break;
			case 2:
				system("cls");
				cout << "------����(����)ջ���ⷽʽ����n�Ľ׳�-----" << endl << endl;
				cout << "��������׳˵����ֵ" << endl;
				cin >> n;
				wait_for_enter("��ʾ������ʼ");
				cout << "n\t�׳˽��" << endl;
				cout << "------------------------------------" << endl;
				for (int i = 1; i <= n; i++)
					cout << i << "\t" << Factorial_2(i, linkstack) << endl;
				wait_for_enter("��ʾ���");
				system("cls");
				break;
			case 3:
				system("cls");
				cout << "-----���Եݹ麯����ʽ����n�Ľ׳�-----" << endl << endl;
				cout << "��������׳˵����ֵ" << endl;
				cin >> n;
				wait_for_enter("��ʾ������ʼ");
				cout << "n\t�׳˽��" << endl;
				cout << "-------------------------------------" << endl;
				for (int i = 1; i <= n; i++)
					cout << i << "\t" << Factorial_1(i) << endl;
				system("cls");
				break;
		}
	}

	return 0;
}