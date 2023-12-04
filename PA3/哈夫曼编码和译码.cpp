#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <iomanip>
#include "./HuffmanTree.h"

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
	cout << "Usage: " << procname << " { --display }" << endl;
	cout << setw(wkey) << ' ' << "{ --encode filename1 filename2 filename3 }" << endl;
	cout << setw(wkey) << ' ' << "{ --decode filename1 filename2 filename3 }" << endl;
	cout << setw(wkey) << ' ' << "{ --compress filename1 filename2 }" << endl;
	cout << setw(wkey) << ' ' << "{ --decompress filename1 filename2 }" << endl;
	cout << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ��������(��ѡһ)" << endl;
	cout << setw(wopt) << ' ' << "--display : չʾ���������ͽṹ" << endl;
	cout << setw(wopt) << ' ' << "--encode : (��ʾ��)���ļ����й��������� [�������ļ�] [������ַ�Ƶ���ļ�] [������ļ�]" << endl;
	cout << setw(wopt) << ' ' << "--decode : (��ʾ��)�������������ļ����� [�������ļ�] [������ַ�Ƶ���ļ�] [������ļ�]" << endl;
	cout << setw(wopt) << ' ' << "--compress : ���ļ��ù���������ѹ�� [��ѹ���ļ�] [ѹ�����ļ�]" << endl;
	cout << setw(wopt) << ' ' << "--decompress : �������������ļ���ѹ [����ѹ�ļ�] [��ѹ���ļ�]" << endl;
	cout << endl;
}


int main(int argc, char** argv)
{
	HuffmanTree tree;

	if (argc == 1)
		usage(argv[0], argc);

	/* displayģʽ */
	else if (strcmp(argv[1], "--display") == 0 && argc == 2) {
		char input[128];
		cout << "\n��������ʾ���ַ��� : ";
		cin >> input;
		tree.Display(input);
	}

	/* encodeģʽ */
	else if (strcmp(argv[1], "--encode") == 0 && argc == 5)
		tree.Encode(argv[2], argv[3], argv[4]);

	/* decodeģʽ */
	else if (strcmp(argv[1], "--decode") == 0 && argc == 5)
		tree.Decode(argv[2], argv[3], argv[4]);

	/* compressģʽ */
	else if (strcmp(argv[1], "--compress") == 0 && argc == 4)
		tree.Compress(argv[2], argv[3]);

	/* decompressģʽ */
	else if (strcmp(argv[1], "--decompress") == 0 && argc == 4)
		tree.Decompress(argv[2], argv[3]);

	else 
		usage(argv[0], argc);

	return 0;
}