#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <stack>
#include "./Trie.h"
using namespace std;

/* void usage(const char* const procname, const int args_num)
 * @brief ��ӡ������ʾ��Ϣ
 * @param procname ��ִ���ļ�����
 * @param args_num ��������
*/
void usage(const char* const procname, const int args_num)
{
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;

	cout << endl;
	cout << "Usage: " << procname << " { --count filename1 (filename2) }" << endl;
	cout << setw(wkey) << ' ' << "{ --top10 filename1 (filename2) }" << endl;
	cout << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ��������(��ѡһ)" << endl;
	cout << setw(wopt) << ' ' << "--count : ͳ�ƴ�Ƶ [�����ļ�] [����ļ�(δָ����Ϊ��Ļ)]" << endl;
	cout << setw(wopt) << ' ' << "--top10 : �������Ƶ����ߵ�ǰtop_num���� [�����ļ�] [����ļ�(δָ����Ϊ��Ļ)]" << endl;
	cout << endl;
}

int main(int argc, char** argv)
{
	Trie trie;
	ofstream outfile;
	if ((argc == 3 || argc == 4) && (strcmp(argv[1], "--count") == 0 || strcmp(argv[1], "--top10") == 0)) {
		if (strcmp(argv[1], "--count") == 0){
			if (!trie.ReadFromFile(argv[2]))
				return -1;
			switch (argc) {
				case 3:
					trie.Traverse(cout);
					break;
				case 4:
					outfile.open(argv[3], ios::out);
					if (!outfile.is_open()) {
						cout << "�ļ�[" << argv[3] << "]�޷�д��!" << endl;
						return -1;
					}
					trie.Traverse(outfile);
					cout << "ͳ����Ϣ�ѳɹ�д���ļ�[" << argv[3] << "]��" << endl;
					outfile.close();
					break;
			}
		}
		else if (strcmp(argv[1], "--top10") == 0) {
			if (!trie.ReadFromFile(argv[2]))
				return -1;
			switch (argc) {
				case 3:
					trie.PrintTop(cout);
					break;
				case 4:
					outfile.open(argv[3], ios::out);
					if (!outfile.is_open()) {
						cout << "�ļ�[" << argv[3] << "]�޷�д��!" << endl;
						return -1;
					}
					trie.PrintTop(outfile);
					cout << "ͳ����Ϣ�ѳɹ�д���ļ�[" << argv[3] << "]��" << endl;
					outfile.close();
					break;
			}
		}
	}
	else
		usage(argv[0], argc);

	return 0;
}