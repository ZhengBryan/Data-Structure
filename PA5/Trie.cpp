#include "./Trie.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

/**
 * @brief �����µ��ֵ������
*/
node::node()
{
	times = 0;
	memset(nextNode, 0, sizeof(nextNode));
}

/**
 * @brief �����յ��ֵ���
*/
Trie::Trie()
{
	root = new(nothrow) node;
	if (!root)
		exit(-1);
}

/**
 * @brief �ݹ�ɾ�����н��(������������ )
 * @param cur ��ǰ�����Ľ��
*/
void Trie::Delete_dfs(node* cur)
{
	for (int i = 0; i < 26; i++)
		if (cur->nextNode[i])
			Delete_dfs(cur->nextNode[i]);
	delete cur;
}

/**
 * @brief �����ֵ���(����Delete_dfs)
*/
Trie::~Trie()
{
	Delete_dfs(root);
}

/**
 * @brief ���ֵ����в����µ���
 * @param cur ��ǰ�Ľ��λ��
 * @param word �²���ĵ���
 * @return �õ���Ŀǰ�ĳ���Ƶ��
*/
int Trie::InsertWord(node* cur, string word)
{
	int index = word[0] - 'a';
	// ���û�иýڵ���½�
	if (cur->nextNode[index] == NULL) {
		cur->nextNode[index] = new(nothrow) node;
		if (!cur->nextNode[index])
			exit(-1);
	}
	//���ʽ�����
	if (word.size() == 1)
		return (++cur->nextNode[index]->times);
	else {
		word.replace(0, 1, "");
		return InsertWord(cur->nextNode[index], word);
	}
}

/**
 * @brief ������������ݹ����
 * @param cur ��ǰ�����Ľ��
 * @param q �洢�ַ����Ķ���
 * @param out �����
*/
void Trie::Traverse_dfs(node* cur, queue <char> q, ostream& out)
{
	queue<char> q1(q), q2;

	if (cur->times > 0) {
		out << "<";
		while (!q1.empty()) {
			out << q1.front();
			q1.pop();
		}
		out << ", " << cur->times << ">" << endl;
	}

	for (int i = 0; i < 26; i++) {
		if (!cur->nextNode[i])
			continue;
		q2 = q;
		q2.push(i + 'a');
		Traverse_dfs(cur->nextNode[i], q2, out);
	}
}

/**
 * @brief �����ֵ���������е��ʼ�Ƶ��
*/
void Trie::Traverse(ostream& out)
{
	queue<char> q;
	Traverse_dfs(root, q, out);
}

/**
 * @brief ά��ǰtop_num������Ƶ�������ַ���
 * @param str ��ǰ���ַ���
 * @param times ���ַ�������Ƶ��
*/
void Trie::MaintainTop(string str, int times)
{
	unsigned int i = top_frequency.size();
	while (i > 0 && times >= top_frequency[i - 1].times){
		if (top_frequency[i - 1].str == str) {
			top_frequency.erase(top_frequency.begin() + i - 1);
		}
		i--;
	}
	top_frequency.insert(top_frequency.begin() + i, info{str, times});
	if (top_frequency.size() > top_num)
		top_frequency.pop_back();
}

/**
 * @brief ��ӡ����Ƶ��Ϊǰtop_num�ĵ���
 * @param out �����
*/
void Trie::PrintTop(ostream& out)
{
	for (unsigned int i = 0; i < top_frequency.size(); i++) {
		out << top_frequency[i].str << "\t" << top_frequency[i].times << endl;
	}
}

/**
 * @brief ���ļ����뵥�ʹ����ֵ���
 * @param filename ������ļ���
*/
bool Trie::ReadFromFile(const char* filename)
{
	ifstream infile(filename, ios::in);
	stringstream filestream;
	if (!infile.is_open()) {
		cout << "�ļ�[" << filename << "]������!" << endl;
		return false;
	}

	filestream << infile.rdbuf();
	infile.close();
	file_content = filestream.str();
	
	//���������ַ�
	while (file_content.find("-\n") != string::npos) {
		file_content.replace(file_content.find("-\n"), strlen("-\n"), "");
	}

	//��ʣ�����ַ�ת�ո�
	while (file_content.find("-") != string::npos) {
		file_content.replace(file_content.find("-"), strlen("-"), " ");
	}

	bool invalid = false;
	//��дתСд
	for (unsigned int i = 0; i < file_content.size(); i++) {
		if (file_content[i] >= 'a' && file_content[i] <= 'z')
			continue;
		else if (file_content[i] >= 'A' && file_content[i] <= 'Z')
			file_content[i] += ('a' - 'A');
		else {
			if (file_content[i] < 0)
				invalid = true;
			file_content[i] = ' ';
		}
	}

	if(invalid)
		clog << "�ļ��д��ڷ�ASCII�ַ�������������" << endl;
	
	/* �ļ����벿�ֽ��� ���¿�ʼ���� */

	filestream.clear();
	filestream.str("");
	filestream << file_content;
	while (filestream.good()) {
		string newword;
		filestream >> newword;
		if (newword == "")
			break;
		MaintainTop(newword, InsertWord(root, newword));
	}
	
	return true;
}