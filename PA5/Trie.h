#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

/* Trie�Ľ�� */
struct node{
	//�Ե�ǰ�ڵ�Ϊ�����ĵ��ʳ��ִ���
	int times; 
	//���ʵ���һ���ַ� ��ǰ�����ӽ��
	node* nextNode[26];
public:
	//�����µ��ֵ������
	node();
};

/* ά����ǰtop_numƵ������Ԫ�� */
struct info {
	//�ַ�������
	string str;
	//���ִ���
	int times;
};

/* Trie���� */
class Trie {
private:
	//�ֵ����ĸ��ڵ�
	node* root;
	//����ļ�����
	string file_content;
	//ͳ��ǰn�Ĵ�Ƶ��Ŀǰtop_num��
	const unsigned int top_num = 10;
	//���ǰtop_num��Ƶ�Ĵ�
	vector<info> top_frequency;
	//�ݹ��ͷ����нڵ�
	void Delete_dfs(node* cur);
	//�ݹ�����ֵ���������е��ʼ�Ƶ��
	void Traverse_dfs(node* cur, queue<char> q, ostream& out);
	//ά��ǰtop_num������
	void MaintainTop(string str, int times);
public:
	//������ֵ���
	Trie();
	//�����ֵ���
	~Trie();
	//���ļ����뵥�ʹ����ֵ���
	bool ReadFromFile(const char* filename);
	//���ֵ��������µ���
	int InsertWord(node* cur, string word);
	//�����ֵ���������е��ʼ�Ƶ��
	void Traverse(ostream& out);
	//��ӡǰtop_num������Ƶ�ε��ַ�
	void PrintTop(ostream& out);
};