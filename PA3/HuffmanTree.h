#pragma once
#include "./queue.hpp"

#define CHAR_NUM_TOT 256	

/* ���������Ľ�� */
typedef struct HTNode {
	unsigned int weight;	//����Ȩ��
	unsigned char value;	//�����ַ�ֵ
	unsigned int parent, lchild, rchild;	//����˫�ס����ӡ��Һ���
}*HTPointer;

/* �ַ�-����Ƶ�� */
struct CharWithNode {
	unsigned char ch;		//�ַ�
	unsigned int weight;	//Ȩ��-���ֵĴ���
};

/* ����������� */
typedef char** HuffmanCode;

/* ���������Ľṹ�� */
class HuffmanTree {
private:
	HTPointer tree;					//������������
	CharWithNode* char_list;		//�ַ�����Ƶ�ʵ��б�
	HuffmanCode code_list;			//������������б�
	unsigned int n;					//�ַ�������
	//ͳ���ַ�����Ƶ��
	void CalCharFreq(const char* filename, const char* filename1, bool output = true);
	void CalCharFreq(const char* str);
	//�����ַ�����Ƶ��
	void ReadCharFreq(const char* filename);
	//ѡ����ڵ���Ȩֵ��С��
	void Select(int max, int& s1, int& s2);
	//������������ �������Ӧÿ���ַ���01��
	void HuffmanCoding();
	//��ȡĳ�ַ���list���±�
	int GetIndex(unsigned char ch);
	//���빦��
	void Inner_Encode(const char* infilename, const char* outfilename);
	//���빦��
	void Inner_Decode(const char* infilename, const char* outfilename);
	//ѹ������
	void Inner_Compress(const char* infilename, const char* outfilename);
	//��ѹ����
	void Inner_Decompress(const char* infilename, const char* outfilename);
	//��ӡ��������
	void PrintTree();
public:
	//���������Ĺ���
	HuffmanTree();
	//��������������
	~HuffmanTree();
	//��ʾģʽ
	void Display(const char* str);
	//����ģʽ
	void Encode(const char* infilename, const char* outfilelist, const char* outfilename);
	//����ģʽ
	void Decode(const char* infilename, const char* infilelist, const char* outfilename);
	//ѹ��ģʽ
	void Compress(const char* infilename, const char* outfilename);
	//��ѹģʽ
	void Decompress(const char* infilename, const char* outfilename);
};
