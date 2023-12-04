#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "./queue.hpp"
using namespace std;
const char* CommodityNameList[] = { "���ݽṹ��C���԰棩\t", "��ɢ��ѧѧϰָ����ϰ�����", "�����߼������ԭ��ʵ���̳�", "������������ͳ��\t", "������������ͳ��ͬ��ϰ���", "���Ļ����񽻼�\t", "�������ѧ����\t" };
struct Data {
	char CommodityName[128];	//��Ʒ����
	float Price;				//��Ʒ�۸�
	int RequestTime;			//�����ʱ��
	friend ostream& operator<<(ostream& out, const Data& that);
};

ostream& operator<<(ostream& out, const Data& that)
{
	cout << "��Ʒ����:" << that.CommodityName << "\t\t\t��Ʒ�۸�:" << that.Price << "\t\t����ʱ��:��" << that.RequestTime << "��" << endl;
	return out;
}

void wait_for_enter()
{
	cout << endl << "�밴�س�������";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

int Menu()
{
	system("mode con: cols=83 lines=30");
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\t PA2*-���е�Ӧ��" << endl;
	
	cout << endl << endl;
	cout << "\t\t\t\t    �˵�ѡ��" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|\t1\t|\t2\t|\t3\t|\t0\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|   ���Զ���\t|   ����Ϣ����\t|   ����Ϣ����\t|      �˳�\t|" << endl;
	cout << "\t|   ��������\t|    ����ģ��\t|    ����ģ��\t|      QUIT\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl << endl << endl;
	cout << "\t\t\t     [�밴��Ӧ����ѡ����]" << endl;
	cout << "\t\t\t\t\t";
	while (char ch = _getch()) 
		if (ch >= '0' && ch <= '3')
			return ch - '0';
	return 0;
}

void TestBasicFunction()
{
	system("cls");
	int e;
	cout << "���濪ʼ����SqQueue�ĸ�������" << endl;
	cout << "-----------------------------" << endl;

	cout << endl << "<���Թ��캯��>" << endl;
	cout << "��������е���󳤶�:";
	int maxsize;
	cin >> maxsize;
	while (!cin.good()) {
		cout << "��������, ����������:";
		cin.clear();
		cin.ignore(65536, '\n');
		cin >> maxsize;
	}
	getchar();
	{
		SqQueue<int> queue(maxsize);
		cout << "��󳤶�Ϊ" << maxsize << "�Ŀն��н����ɹ�" << endl;
		wait_for_enter();


#if 1
		cout << endl << "<����Enqueue����>" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.EnQueue(i * 2 + 1) == OK)
				cout << "Ԫ��(" << i * 2 + 1 << ")�������" << endl;
			else
				cout << "Ԫ��(" << i * 2 + 1 << ")����ʧ��" << endl;
		}
		wait_for_enter();
#endif


#if 1
		cout << endl << "<����Dequeue����>" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.DeQueue(e) == OK)
				cout << "Ԫ��(" << e << ")�ѳɹ�����" << endl;
			else
				cout << "�����ѿ�, ����ʧ��!" << endl;
		}
		wait_for_enter();
#endif


#if 1
		cout << endl << "<����GetHead����>" << endl;
		cout << "�Ƚ������������" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.EnQueue(i * 2 + 1) == OK)
				cout << "Ԫ��(" << i * 2 + 1 << ")�������" << endl;
			else
				cout << "Ԫ��(" << i * 2 + 1 << ")����ʧ��" << endl;
		}

		cout << endl << "������, ���濪ʼ����" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.GetHead(e) == OK)
				cout << "Ԫ��(" << e << ")��ǰ�ڶ���" << endl;
			else
				cout << "�����ѿ�, ���׻�ȡʧ��!" << endl;
			if (queue.DeQueue(e) == OK)
				cout << "Ԫ��(" << e << ")�ѳɹ�����" << endl;
			else
				cout << "�����ѿ�, ����ʧ��!" << endl;
		}
		wait_for_enter();
#endif


#if 1
		cout << endl << "<����PrintQueue����>" << endl;
		cout << "�Ƚ������������" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.EnQueue(i * 2 + 1) == OK)
				cout << "Ԫ��(" << i * 2 + 1 << ")�������" << endl;
			else
				cout << "Ԫ��(" << i * 2 + 1 << ")����ʧ��" << endl;
		}
		cout << "������Ԫ��cout��ӡ����:" << endl;
		queue.PrintQueue(cout);
		cout << "�������������ļ�,";
		ofstream out;
		out.open("test.txt", ios::out);
		out << "������Ԫ������ļ���ӡ����:" << endl;
		queue.PrintQueue(out);
		cout << "��򿪿�ִ���ļ�����Ŀ¼���test.txt�ļ������" << endl;
		out.close();
		wait_for_enter();
#endif


#if 1
		cout << endl << "<����ClearQueue����>" << endl;
		cout << "���濪ʼ��ն���" << endl;
		queue.ClearQueue();
		cout << "����������, ������Ԫ�ش�ӡ����:" << endl;
		queue.PrintQueue(cout);
		wait_for_enter();
#endif


#if 1
		cout << endl << "<����QueueEmpty����>" << endl;
		cout << "��ǰ����״̬��:" << (queue.QueueEmpty() ? "��" : "�ǿ�") << endl;
		cout << "�������������" << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.EnQueue(i * 2 + 1) == OK)
				cout << "Ԫ��(" << i * 2 + 1 << ")�������" << endl;
			else
				cout << "Ԫ��(" << i * 2 + 1 << ")����ʧ��" << endl;
		}
		cout << "��ǰ����״̬��:" << (queue.QueueEmpty() ? "��" : "�ǿ�") << endl;
		wait_for_enter();
#endif


#if 1
		cout << endl << "<����QueueLength����>" << endl;
		cout << "��ǰ���г�����:" << queue.QueueLength() << endl;
		for (int i = 0; i <= maxsize + 2; i++) {
			if (queue.DeQueue(e) == OK)
				cout << "Ԫ��(" << e << ")�ѳɹ�����" << endl;
			else
				cout << "�����ѿ�, ����ʧ��!" << endl;
			cout << "��ǰ���г�����:" << queue.QueueLength() << endl;
		}
		wait_for_enter();
#endif


		cout << endl << "<������������>" << endl;
	}
	cout << "Queue�����Ѿ������ٳɹ�" << endl;
	wait_for_enter();

	cout << "���й��ܲ������, ��������������˵�";
	getchar();
}

void Simulation1()
{
	system("cls");
	int TotalMiss = 0;
	cout << "������ʼģ��100���ڵ�����" << endl;
	wait_for_enter();
	for (int i = 1; i <= 100; i++) {
		int request = rand() % 3000 + 500;
		cout << endl << "��" << i << "���ڲ�����" << request << "������" << endl;
		if (request >= 1000) {
			request -= 1000;
			cout << "Bϵͳ����1000������" << endl;
			if (request >= 1000) {
				request -= 1000;
				cout << "Cϵͳ����1000������" << endl;
			}
			else {
				cout << "Cϵͳ����" << request << "������" << endl;
				request = 0;
			}
		}
		else {
			cout << "Bϵͳ����" << request << "������" << endl;
			request = 0;
		}
		if(request)
			cout << "������" << request << "����������" << endl;
		TotalMiss += request;
		Sleep(100);
	}
	cout << endl << endl << "�ܹ���" << TotalMiss << "����������" << endl;
	wait_for_enter();
}

void Simulation2()
{
	system("cls");
	SqQueue<Data> MessageQueue(10000);
	int RequestTot = 0, WaitSum = 0;
	cout << "������ʼģ��100���ڵ�����" << endl;
	wait_for_enter();
	for (int i = 1; i <= 100; i++) {
		int request = rand() % 3000 + 500;
		cout << endl << "��" << i << "���ڲ�����" << request << "������" << endl;
		Data e;
		for (int j = 0; j < request; j++) {
			strcpy(e.CommodityName, CommodityNameList[rand() % 7]);		//���ģ����Ʒ����
			e.Price = (rand() % 200 + 100) / 10.0f;						//���ģ�ⶩ���۸�
			e.RequestTime = i;		//�����ʱ���
			MessageQueue.EnQueue(e);
		}

		//ϵͳ��ʼ��������
		int j;
		for (j = 1; j <= 1000; j++) {
			if (MessageQueue.DeQueue(e) != OK) 
				break;
				//�����Ѿ�Ϊ��
			RequestTot++;
			WaitSum += i - e.RequestTime;	//�ȴ�ʱ��
		}
		cout << "ϵͳB������" << j - 1 << "������" << endl;

		for (j = 1; j <= 1000; j++) {
			if (MessageQueue.DeQueue(e) != OK) 
				break;
				//�����Ѿ�Ϊ��
			RequestTot++;
			WaitSum += i - e.RequestTime;	//�ȴ�ʱ��
		}
		cout << "ϵͳC������" << j - 1 << "������" << endl;
		cout << "��Ϣ��������" << MessageQueue.QueueLength() << "������" << endl;
		Sleep(100);
	}

	cout << endl << endl<< "�ܹ��ɹ���������" << RequestTot << "��" << endl;
	cout<< "ƽ��ÿλ�û��ȴ����󱻴�����" << WaitSum * 1.0f / RequestTot << "��" << endl;
	wait_for_enter();

	system("mode con: cols=150 lines=50");
	cout << "��ֹ����100��, ����" << MessageQueue.QueueLength() << "������δ��������������:" << endl;
	wait_for_enter();
	MessageQueue.PrintQueue(cout);

	cout << "�����ѽ���, �����������˵�" << endl;
	wait_for_enter();
}

int main()
{
	int ret;
	srand((unsigned)time(NULL));
	while (ret = Menu()) {
		switch (ret){
			case 1:
				TestBasicFunction();
				break;
			case 2:
				Simulation1();
				break;
			case 3:
				Simulation2();
				break;
		}
	}
	
	return 0;
}