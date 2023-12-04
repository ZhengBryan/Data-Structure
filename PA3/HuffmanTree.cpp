#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include  "./HuffmanTree.h"
using namespace std;

/**
 * @brief ��ӡһ�������Ŀո�(iomanip)
 * @param n ��ӡ�Ŀո���
*/
static void PrintSpace(int n)
{
	for (int i = 0; i < n; i++)
		cout << " ";
}

/**
 * @brief ��2��n����
 * @param n ���ݵ���n
 * @return 2��n���ݽ��
*/
static int pow2(int n)
{
	int ans = 1;
	for (int i = 0; i < n; i++)
		ans *= 2;
	return ans;
}


/**
 * @brief ������������
*/
HuffmanTree::HuffmanTree()
{
	tree = NULL;
	char_list = NULL;
	code_list = NULL;
}


/**
 * @brief ���ٹ�������
*/
HuffmanTree::~HuffmanTree()
{
	if(char_list)
		delete[] char_list;
	if(code_list)
		delete[] code_list;
	if (tree)
		delete[] tree;
}


/**
 * @brief �����ļ���ÿ���ַ����ֵ�Ƶ��
 * @param filename �����ѹ���ļ�
 * @param filename1 ������ַ�Ƶ���ļ�
 * @param output �Ƿ�Ҫ������ļ�
*/
void HuffmanTree::CalCharFreq(const char* filename, const char* filename1, bool output)
{
	int* templist = new(nothrow) int[CHAR_NUM_TOT];
	int order[CHAR_NUM_TOT];
	for (int i = 0; i < CHAR_NUM_TOT; i++)
		order[i] = i;

	if (!templist)
		exit(OVER_FLOW);
	memset(templist, 0, CHAR_NUM_TOT * sizeof(int));
	ifstream infile;
	ofstream outfile;
	infile.open(filename, ios::in | ios::binary);		//���ļ�
	if (!infile.is_open()) {
		cout << "�ļ�" << filename << "��ʧ��!" << endl;
		exit(0);
	}
	if (output) {
		outfile.open(filename1, ios::out);	//���ļ�
		if (!outfile.is_open()) {
			cout << "�ļ�" << filename1 << "д��ʧ��!" << endl;
			exit(0);
		}
	}

	unsigned char ch;
	while (infile.peek() != EOF) {
		ch = infile.get();
		templist[ch] += 1;
	}

	unsigned int i, j;

	n = 0;
	for (int i = 0; i < CHAR_NUM_TOT; i++)
		if (templist[i])
			++n;

	char_list = new(nothrow) CharWithNode[n];
	if (!char_list)
		exit(OVER_FLOW);
	j = 0;
	for (i = 0; i < n; i++) {
		while (templist[j] == 0)
			j++;
		char_list[i].weight = templist[j];
		char_list[i].ch = (unsigned char)j;
		j++;
	}

	//��ʾʱ���ÿ����Ƶ�����ļ�
	if (output) {
		for (unsigned int i = 0; i < n; i++)
			outfile << char_list[i].ch + 0 << " " << char_list[i].weight + 0 << endl;
	}

	delete[] templist;
	infile.close();
	if (output)
		outfile.close();
}


/**
 * @brief �����ַ�����ÿ���ַ����ֵ�Ƶ��(��������)
 * @param str ������ַ���
 * @param output �Ƿ�Ҫ������ļ�
*/
void HuffmanTree::CalCharFreq(const char* str)
{
	int* templist = new(nothrow) int[CHAR_NUM_TOT];
	int order[CHAR_NUM_TOT];
	for (int i = 0; i < CHAR_NUM_TOT; i++)
		order[i] = i;

	if (!templist)
		exit(OVER_FLOW);
	memset(templist, 0, CHAR_NUM_TOT * sizeof(int));

	for (unsigned int i = 0; i < strlen(str); i++) {
		templist[str[i]] += 1;
	}

	unsigned int i, j;

	n = 0;
	for (int i = 0; i < CHAR_NUM_TOT; i++)
		if (templist[i])
			++n;

	char_list = new(nothrow) CharWithNode[n];
	if (!char_list)
		exit(OVER_FLOW);
	j = 0;
	for (i = 0; i < n; i++) {
		while (templist[j] == 0)
			j++;
		char_list[i].weight = templist[j];
		char_list[i].ch = (unsigned char)j;
		j++;
	}

	for (unsigned int i = 0; i < n; i++)
		cout << char_list[i].ch << "�ĳ���Ƶ��Ϊ : " << char_list[i].weight + 0 << endl;

	delete[] templist;
}


/**
 * @brief �����ַ�Ƶ���ļ���Ϣд��list
 * @param filename ������ַ�Ƶ���ļ�
*/
void HuffmanTree::ReadCharFreq(const char* filename)
{
	int* templist = new(nothrow) int[CHAR_NUM_TOT];
	if (!templist)
		exit(OVER_FLOW);
	memset(templist, 0, sizeof(int) * CHAR_NUM_TOT);

	ifstream infile;
	ofstream outfile;
	infile.open(filename, ios::in);		//���ļ�
	n = 0;	//���㿪ʼ����
	while (infile.good()) {
		int order, num;
		infile >> order >> num;
		if (!infile.good())
			break;
		n++;
		templist[order] = num;
	}

	char_list = new(nothrow) CharWithNode[n];
	if (!char_list)
		exit(OVER_FLOW);
	int j = 0;
	for (unsigned int i = 0; i < n; i++) {
		while (templist[j] == 0)
			j++;
		char_list[i].weight = templist[j];
		char_list[i].ch = (char)j;
		j++;
	}

	infile.close();
}



/**
 * @brief ѡ��������Ȩֵ��С���������
 * @param max ��1-max�ķ�Χ�в���
 * @param s1 Ȩֵ��С�Ľ��
 * @param s2 Ȩֵ��С�Ľ��
*/
void HuffmanTree::Select(int max, int& s1, int& s2)
{
	s1 = -1, s2 = -1;
	for (int i = 1; i <= max; i++) {
		//�Ѿ��и���� ����
		if (tree[i].parent)
			continue;
		if (s1 == -1 || tree[i].weight < tree[s1].weight) {
			s2 = s1;
			s1 = i;
		}
		else if (s2 == -1 || tree[i].weight < tree[s2].weight)
			s2 = i;
	}
}



/**
 * @brief ������������ �������Ӧÿ���ַ���01��
*/
void HuffmanTree::HuffmanCoding()
{
	unsigned int m = 2 * n - 1;
	HTPointer p;
	unsigned int i;
	tree = new(nothrow) HTNode[2 * n];
	if (!tree)
		exit(OVER_FLOW);
	CharWithNode* q = char_list;
	for (p = tree + 1, i = 1; i <= n; ++i, ++p, ++q) {
		p->weight = q->weight;
		p->value = q->ch;
		p->lchild = p->rchild = 0;
		p->parent = 0;
	}
	for (; i <= m; ++i, ++p) {
		p->weight = 0;
		p->value = 0;
		p->lchild = p->rchild = 0;
		p->parent = 0;
	}

	//���濪ʼ����
	for (unsigned int i = n + 1; i <= m; ++i) {
		int s1, s2;
		Select(i - 1, s1, s2);
		tree[s1].parent = i;
		tree[s2].parent = i;
		tree[i].lchild = s1;
		tree[i].rchild = s2;
		tree[i].value = '^';
		tree[i].weight = tree[s1].weight + tree[s2].weight;
	}

	code_list = new(nothrow) char* [n + 1];
	if (!code_list)
		exit(OVER_FLOW);
	char* cd = new(nothrow) char[n];
	if (!cd)
		exit(OVER_FLOW);
	cd[n - 1] = '\0';

	for (unsigned int i = 1; i <= n; ++i) {
		int start = n - 1;
		int f, c;
		for (c = i, f = tree[i].parent; f; c = f, f = tree[f].parent) {
			if (tree[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		code_list[i] = new(nothrow) char[n - start];
		if (!code_list[i])
			exit(OVER_FLOW);
		strcpy(code_list[i], &cd[start]);
	}

	delete[] cd;
}



/**
 * @brief ��ȡĳ�ַ���list���±�
 * @param ch Ҫ���ҵ��ַ�
*/
int HuffmanTree::GetIndex(unsigned char ch)
{
	for (unsigned int i = 1; i <= n; i++)
		if (tree[i].value == ch)
			return i;
	return -1;
}


/**
 * @brief ���빦��
 * @param infilename ��������ļ���
 * @param outfilename �������ļ���
*/
void HuffmanTree::Inner_Encode(const char* infilename, const char* outfilename)
{
	ifstream infile;
	ofstream outfile;
	infile.open(infilename, ios::in);		//���ļ�
	if (!infile.is_open()) {
		cout << "�ļ�" << infilename << "��ʧ��!" << endl;
		exit(0);
	}
	outfile.open(outfilename, ios::out);	//���ļ�
	if (!outfile.is_open()) {
		cout << "�ļ�" << outfilename << "д��ʧ��!" << endl;
		exit(0);
	}

	char ch;
	while (infile.peek() != EOF) {
		ch = infile.get();
		int ret = GetIndex(ch);
		if (ret == -1) {
			cout << "�ļ��ڰ���ASCII�벻��0-127�ڵ��ַ�!" << endl;
			exit(0);
		}
		outfile << code_list[ret];
	}

	cout << "�ļ�" << infilename << "�ѳɹ�����, ���" << outfilename << "�鿴������Ϣ��" << endl;

	infile.close();
	outfile.close();
}


/**
 * @brief ���빦��
 * @param infilename ��������ļ���
 * @param outfilename �������ļ���
*/
void HuffmanTree::Inner_Decode(const char* infilename, const char* outfilename)
{
	ifstream infile;
	ofstream outfile;
	infile.open(infilename, ios::in);		//�������ļ�
	if (!infile.is_open()) {
		cout << "�ļ�" << infilename << "��ʧ��!" << endl;
		exit(0);
	}
	outfile.open(outfilename, ios::out);	//������ļ�
	if (!outfile.is_open()) {
		cout << "�ļ�" << outfilename << "д��ʧ��!" << endl;
		exit(0);
	}

	unsigned char ch;
	HTPointer now = &tree[2 * n - 1];
	while (infile.peek() != EOF) {
		ch = infile.get();
		if (ch == '0' && now->lchild) {
			now = &tree[now->lchild];
		}
		else if (ch == '1' && now->rchild) {
			now = &tree[now->rchild];
		}
		else if (ch != '1' && ch != '0') {
			cout << "�ļ������ʽ����!" << endl;
			exit(0);
		}
		else {
			outfile << now->value;
			now = &tree[2 * n - 1];
			if (ch == '0' && now->lchild) {
				now = &tree[now->lchild];
			}
			else if (ch == '1' && now->rchild) {
				now = &tree[now->rchild];
			}
		}
	}

	/* �������һ���ַ� */
	outfile << now->value;
	cout << "�ļ�" << infilename << "�Ѿ��ɹ�����Ϊ�ļ�" << outfilename << endl;

	infile.close();
	outfile.close();
}



/**
 * @brief ѹ������
 * @param infilename ��ѹ�����ļ���
 * @param outfilename ����ѹ���ļ���
*/
void HuffmanTree::Inner_Compress(const char* infilename, const char* outfilename)
{
	ifstream infile;
	ofstream outfile;

	infile.open(infilename, ios::in | ios::binary);					//�������ļ�
	if (!infile.is_open()) {
		cout << "�ļ�" << infilename << "��ʧ��!" << endl;
		exit(0);
	}

	outfile.open(outfilename, ios::out | ios::binary);	//������ļ�
	if (!outfile.is_open()) {
		cout << "�ļ�" << outfilename << "д��ʧ��!" << endl;
		exit(0);
	}

	outfile << (unsigned char)n;			//���ַ�����д��
	for (unsigned int i = 1; i <= n; i++) {
		outfile << tree[i].value;			//������д��, ��ʡ�ռ�
		for (int j = 0; j < 4; j++) {	//unsigned int��4��д��
			outfile << char(tree[i].weight >> (j * 8));
		}
	}

	//�ȵ�8���ֽ����������һ��
	unsigned char ch, outch = 0;
	int i = 1;
	int org_tot = 0, aft_tot = 0;		//ͳ���ַ�����
	while (infile.peek() != EOF) {
		ch = infile.get();
		org_tot++;
		int ret = GetIndex(ch);
		if (ret == -1) {
			cout << "�ļ��д��ڷ�0-127���ַ�!" << endl;
			exit(0);
		}
		for (unsigned int j = 0; j < strlen(code_list[ret]); j++) {
			if (code_list[ret][j] == '1')
				outch |= (1 << (8 - i));
			i++;
			if (i == 9) {
				aft_tot++;
				outfile << outch;
				outch = 0;
				i = 1;
			}
		}
	}

	if (i != 1) {
		aft_tot++;
		outfile << outch;
	}

	cout << "�ļ�" << infilename << "�Ѿ�ѹ���ɹ�, ѹ����Ϊ" << aft_tot * 100.0 / org_tot << "%" << endl;

	infile.close();
	outfile.close();
}



/**
 * @brief ��ѹ����
 * @param infilename ����ѹ���ļ���
 * @param outfilename ��ѹ����ļ���
*/
void HuffmanTree::Inner_Decompress(const char* infilename, const char* outfilename)
{
	ifstream infile;
	ofstream outfile;
	infile.open(infilename, ios::in | ios::binary);		//�������ļ�
	if (!infile.is_open()) {
		cout << "�ļ�" << infilename << "��ʧ��!" << endl;
		exit(0);
	}
	outfile.open(outfilename, ios::out | ios::binary);	//������ļ�
	if (!outfile.is_open()) {
		cout << "�ļ�" << outfilename << "д��ʧ��!" << endl;
		exit(0);
	}

	unsigned char ch;
	//��ȡn����Ϣ
	ch = infile.get();
	//�������ַ���ռ ������Ϊ0
	n = ch ? ch : 256;
	//���ļ�ͷ��ȡ�ַ�Ƶ����Ϣ
	char_list = new(nothrow) CharWithNode[n];
	if (!char_list)
		exit(OVER_FLOW);

	int tot_ch = 0, cur_ch = 0;			//ͳ���ĵ����ַ�����

	for (unsigned int i = 0; i < n; i++) {
		ch = infile.get();
		char_list[i].ch = ch;
		char_list[i].weight = 0;
		for (int j = 0; j < 4; j++) {
			ch = infile.get();
			char_list[i].weight |= (ch << (j * 8));
		}
		tot_ch += char_list[i].weight;
	}

	HuffmanCoding();

	unsigned char cur;
	HTPointer now = &tree[2 * n - 1];					//���λ���ǹ��������ĸ��ڵ�
	while (infile.peek() != EOF) {
		cur = infile.get();
		//�ڹ����������Ҷ�Ӧ�ı���
		for (int i = 1; i <= 8; i++) {
			char bit = !!(cur & (1 << (8 - i)));
			if (bit == 0 && now->lchild) {
				now = &tree[now->lchild];
			}
			else if (bit == 1 && now->rchild) {
				now = &tree[now->rchild];
			}
			else {
				cur_ch++;				//��¼�ַ���
				if (cur_ch > tot_ch)	//�ļ����ȵ��� ��ֹĩβ0������
					break;
				outfile << now->value;
				now = &tree[2 * n - 1];
				if (bit == 0 && now->lchild) {
					now = &tree[now->lchild];
				}
				else if (bit == 1 && now->rchild) {
					now = &tree[now->rchild];
				}
			}
		}
	}

	//���һ���ֽ����ý��� û���ü����
	if (cur_ch < tot_ch)
		outfile << now->value;

	cout << "�ļ�" << infilename << "�ѽ�ѹ�ɹ�!" << endl;

	infile.close();
	outfile.close();
}



/**
 * @brief ��ӡ��������
*/
void HuffmanTree::PrintTree()
{
	int depth = 0;
	{
		struct NodeWithDepth {
			HTPointer node;
			int depth;
			NodeWithDepth(HTPointer bb = NULL, int dd = 1)
			{
				node = bb;
				depth = dd;
			}
		};
		SqQueue<NodeWithDepth> queue(1000);  //queue����󳤶�

		NodeWithDepth p;
		queue.EnQueue(NodeWithDepth(&tree[2 * n - 1], 1));
		while (!queue.QueueEmpty()) {
			queue.DeQueue(p);
			depth = max(depth, p.depth);
			if (p.node->lchild)
				queue.EnQueue(NodeWithDepth(&tree[p.node->lchild], p.depth + 1));
			if (p.node->rchild)
				queue.EnQueue(NodeWithDepth(&tree[p.node->rchild], p.depth + 1));
		}
	}
	/* �������������� */

	/* ���¿�ʼ����� */
	{
		struct NodeWithNo {
			HTPointer node;
			int depth;
			int no;
			NodeWithNo(HTPointer bb = NULL, int dd = 1, int nn = 1)
			{
				node = bb;
				depth = dd;
				no = nn;
			}
		};
		SqQueue<NodeWithNo> queue(1000), queue2(1000);  //queue����󳤶�

		queue.ClearQueue();
		queue.EnQueue(NodeWithNo(&tree[2 * n - 1], 1, 1));
		NodeWithNo p, q, r, s;
		//����һ�е�ǰ�ÿո�
		PrintSpace(pow2(depth - 1) - 1);
		while (!queue.QueueEmpty()) {
			queue.DeQueue(p);
			if (p.node->lchild)
				queue.EnQueue(NodeWithNo(&tree[p.node->lchild], p.depth + 1, 2 * p.no));
			if (p.node->rchild)
				queue.EnQueue(NodeWithNo(&tree[p.node->rchild], p.depth + 1, 2 * p.no + 1));
			//�����ǰ�ڵ�
			cout << p.node->value;
			queue2.EnQueue(p);		  //������һ������ ��Ϊ����һ����� / \ 
			if (queue.QueueEmpty())   //���һ���ڵ���������� ����
				cout << endl;
			else {
				queue.GetHead(q);
				if (q.depth == p.depth) {   //����ͬ���
					PrintSpace((q.no - p.no) * pow2((depth - p.depth) + 1) - 1);
				}
				else {					    //�ڲ�ͬ���
					cout << endl;
					//�ȴ������׿ո�
					queue2.GetHead(r);
					PrintSpace(pow2(depth - p.depth) - 2 + (r.no - pow2(p.depth - 1)) * pow2((depth - p.depth) + 1));
					while (!queue2.QueueEmpty()) {
						queue2.DeQueue(r);
						cout << (r.node->lchild ? '/' : ' ') << ' ' << (r.node->rchild ? '\\' : ' ');
						if (!queue2.QueueEmpty()) {  //������ĩ
							queue2.GetHead(s);
							PrintSpace((s.no - r.no) * pow2((depth - s.depth) + 1) - 3);
						}
					}
					cout << endl;
					PrintSpace(pow2(depth - q.depth) - 1 + (q.no - pow2(p.depth)) * pow2((depth - q.depth) + 1));
				}
			}
		}
	}
}


/**
 * @brief չʾģʽ
 * @param str ������ַ���
*/
void HuffmanTree::Display(const char* str)
{
	CalCharFreq(str);
	HuffmanCoding();
	PrintTree();
}


/**
 * @brief ����ģʽ
 * @param infilename �������ļ�
 * @param outfilelist �ַ�Ƶ���ļ�
 * @param outfilename ������ļ�
*/
void HuffmanTree::Encode(const char* infilename, const char* outfilelist, const char* outfilename)
{
	CalCharFreq(infilename, outfilelist);
	HuffmanCoding();
	Inner_Encode(infilename, outfilename);
}


/**
 * @brief ����ģʽ
 * @param infilename �������ļ�
 * @param infilelist �ַ�Ƶ���ļ�
 * @param outfilename ������ļ�
*/
void HuffmanTree::Decode(const char* infilename, const char* infilelist, const char* outfilename)
{
	ReadCharFreq(infilelist);
	HuffmanCoding();
	Inner_Decode(infilename, outfilename);
}


/**
 * @brief ѹ��ģʽ
 * @param infilename ��ѹ���ļ�
 * @param outfilename ѹ�����ļ�
*/
void HuffmanTree::Compress(const char* infilename, const char* outfilename)
{
	CalCharFreq(infilename, NULL, false);	//��ģʽ������д���ļ���
	HuffmanCoding();
	Inner_Compress(infilename, outfilename);
}


/**
 * @brief ��ѹģʽ
 * @param infilename ����ѹ�ļ�
 * @param outfilename ��ѹ���ļ�
*/
void HuffmanTree::Decompress(const char* infilename, const char* outfilename)
{
	Inner_Decompress(infilename, outfilename);
	//�ȴ��ļ��ж��� ����ں����ڵ���HuffmanCoding
}