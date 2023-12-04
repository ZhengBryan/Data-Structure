#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <iomanip>
#include "./system.h"
using namespace std;

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
 * @brief ��ʼ��ϵͳ
 * @param tj ͬ�ô�ѧѡ��ϵͳ
*/
void InitSystem(EduSystem& tj)
{
	char FileDir[128];
	system("mode con: cols=83 lines=30");
	ifstream File;
	cout << endl << endl << endl << endl;
	cout << "\t\t\t��ӭ��¼ͬ�ô�ѧѧ����Ϣ����ϵͳ!" << endl;
	cout << endl << endl << endl << endl << endl << endl;

	while (true) {
		cout << "\t\t[������ѧ������·������ѧ������]" << endl;
		cout << "\t\t���ڴ˴�����:";
		cin >> FileDir;
		File.open(FileDir, ios::in);
		if (File.is_open())
			break;
		else
			cout << "\t\t�ļ���ʧ��, ������!" << endl;
	}
	tj.InitStudentList(File);
	cout << "\t\t���ɹ�����ѧ��" << tj.GetStudentNum() << "��!" << endl << endl;
	File.close();

	while (true) {
		cout << "\t\t[������γ�����·������γ�����]" << endl;
		cout << "\t\t���ڴ˴�����:";
		cin >> FileDir;
		File.open(FileDir, ios::in);
		if (File.is_open())
			break;
		else
			cout << "\t\t�ļ���ʧ��, ������!" << endl;
	}
	tj.InitCourseList(File);
	cout << "\t\t���ɹ�����γ�" << tj.GetCourseNum() << "��!" << endl;

	getchar();
	wait_for_enter("\t\t��ʼ���������");
}

/**
 * @brief ���ӻ��˵�����
 * @return ѡ��Ĳ˵���
*/
int Menu()
{
	system("mode con: cols=83 lines=30");
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\tͬ�ô�ѧѡ��ϵͳ" << endl;

	cout << endl << endl;
	cout << "\t\t\t\t    �˵�ѡ��" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t1\t|\t2\t|\t3\t|\t4\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|   ����ѧ��\t|    �����γ�\t|    ɾ��ѧ��\t|    ɾ���γ�\t|" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t5\t|\t6\t|\t7\t|\t0\t|" << endl;
	cout << '\t' << setw(65) << setfill('-') << "" << endl;
	cout << "\t|\t\t|\t\t|\t\t|\t\t|" << endl;
	cout << "\t|   ��ѯѧ��\t|    ��ѯ�γ�\t|    �γ�ע��\t|    �˳�ϵͳ\t|" << endl;
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
	EduSystem TongjiEdu;
	InitSystem(TongjiEdu);
	int ret;
	while (ret = Menu())
	{
		StudentInfo tmps;
		CourseInfo tmpc;
		ostringstream out;
		switch (ret) {
			case 1:
				system("cls");
				char tmpt[20];
				cout << "\n\t\t\t\t[����ѧ����Ϣ]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t������ѧ��ѧ��:";
					cin >> tmps.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				cout << "\n\t\t������ѧ������:";
				cin >> tmps.name;
				while (true) {
					cout << "\n\t\t������ѧ���Ա�:";
					cin >> tmpt;
					if (strcmp(tmpt, "��") == 0) {
						tmps.gender = 'M';
						break;
					}
					else if (strcmp(tmpt, "Ů") == 0) {
						tmps.gender = 'F';
						break;
					}
					cout << "\t\t�Ա����Ϊ �� / Ů!" << endl;
				}
				cout << "\n\t\t������ѧ��רҵ:";
				cin >> tmps.major;
				if (TongjiEdu.InsertStudent(tmps) == ERROR) {
					getchar();
					wait_for_enter("\n\n\t\t��ѧ���Ѿ���ѧ��");
				}
				else {
					getchar();
					wait_for_enter("\n\n\t\tѧ����Ϣ¼�����");
				}
				break;
			case 2:
				system("cls");
				cout << "\n\t\t\t\t[�����γ���Ϣ]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t������γ̿κ�:";
					cin >> tmpc.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				cout << "\n\t\t������γ̿���:";
				cin >> tmpc.name;
				cout << "\n\t\t������γ�ѧ��:";
				cin >> tmpc.credit;
				cout << "\n\t\t�������Ͽεص�:";
				cin >> tmpc.venue;
				if (TongjiEdu.InsertCourse(tmpc) == ERROR) {
					getchar();
					wait_for_enter("\n\n\t\t�ÿκ��Ѿ��пγ�");
				}
				else {
					getchar();
					wait_for_enter("\n\n\t\t�γ���Ϣ¼�����");
				}
				break;
			case 3:
				system("cls");
				cout << "\n\t\t\t\t[ɾ��ѧ����Ϣ]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t������ѧ��ѧ��:";
					cin >> tmps.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				if (TongjiEdu.DeleteStudent(tmps) == ERROR)
					cout << "\t\t�����ڸ�ѧ��!!!" << endl;
				else
					cout << "\t\t\n\t\t[ѧ��]" << tmps.ID << "\n\t\t[����]" << tmps.name << "\n\t\t[�Ա�]" << (tmps.gender == 'M' ? "��" : "Ů") << "\n\t\t[רҵ]" << tmps.major << "\n\t\t�ѳɹ�ɾ��" << endl;
				getchar();
				wait_for_enter("\n\n\t\t����ִ�н���");
				break;
			case 4:
				system("cls");
				cout << "\n\t\t\t\t[ɾ���γ���Ϣ]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t������γ̿κ�:";
					cin >> tmpc.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				if (TongjiEdu.DeleteCourse(tmpc) == ERROR)
					cout << "\t\t�����ڸÿγ�!!!" << endl;
				else
					cout << "\t\t\n\t\t[�κ�]" << tmpc.ID << "\n\t\t[����]" << tmpc.name << "\n\t\t[ѧ��]" << tmpc.credit << "\n\t\t[�ص�]" << tmpc.venue << "\n\t\t�ѳɹ�ɾ��" << endl;
				getchar();
				wait_for_enter("\n\n\t\t����ִ�н���");
				break;
			case 5:
				system("cls");
				cout << "\n\t\t\t\t[��ѯѧ����Ϣ]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t������ѧ��ѧ��:";
					cin >> tmps.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				if (TongjiEdu.SearchStudent(tmps, out) == ERROR)
					cout << "\t\t�����ڸ�ѧ��!!!" << endl;
				else
					cout << "\t\t��ѧ������Ϣ��:\n\t\t[ѧ��]" << tmps.ID << "\n\t\t[����]" << tmps.name << "\n\t\t[�Ա�]" << (tmps.gender == 'M' ? "��" : "Ů") << "\n\t\t[רҵ]" << tmps.major << endl;
				cout << "\n\t\tע��Ŀγ�����:\n" << out.str();
				getchar();
				wait_for_enter("\n\n\t\t����ִ�н���");
				break;
			case 6:
				system("cls");
				cout << "\n\t\t\t\t[��ѯ�γ���Ϣ]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t������γ̿κ�:";
					cin >> tmpc.ID;
					cout << tmpc.ID << endl;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				if (TongjiEdu.SearchCourse(tmpc, out) == ERROR)
					cout << "\t\t�����ڸÿγ�!!!" << endl;
				else
					cout << "\t\t�ÿγ̵���Ϣ��:\n\t\t[�κ�]" << tmpc.ID << "\n\t\t[����]" << tmpc.name << "\n\t\t[ѧ��]" << tmpc.credit << "\n\t\t[�ص�]" << tmpc.venue << endl;
				cout << "\n\t\tע���ѧ������:\n" << out.str();
				getchar();
				wait_for_enter("\n\n\t\t����ִ�н���");
				break;
			case 7:
				system("cls");
				cout << "\n\t\t\t\t[ѧ��ע��γ�]" << endl;
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t������ѧ��ѧ��:";
					cin >> tmps.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				cout << endl << endl << endl << endl;
				while (true) {
					cout << "\t\t������γ̿κ�:";
					cin >> tmpc.ID;
					if (cin.good())
						break;
					cin.clear();
					cin.ignore(65536, '\n');
				}
				int ret = TongjiEdu.Register(tmpc, tmps);
				if (ret == NO_STUDENT)
					cout << "\n\n\t\tѧ��������!" << endl;
				else if (ret == NO_COURSE)
					cout << "\n\n\t\t�γ̲�����!" << endl;
				else if (ret == ALREADY_REGISTER)
					cout << "\n\n\t\t��ѧ����ע����ÿγ�" << endl;
				else
					cout << "\n\n\t\t�γ�ע��ɹ�" << endl;
				getchar();
				wait_for_enter("\n\n\t\t����ִ�н���");
				break;
		}
	}

	return 0;
}