#include <iostream>
#include <string.h>
using namespace std;

#define STACK_INIT_SIZE 100000
#define STACKINCREMENT 10

typedef int Status;
#define SOVERFLOW -2
#define OK 1
#define ERROR 0
#define TOVERFLOW -1

template <class SElemType>
struct SqStack {
private:
	SElemType* base;
	SElemType* top;
	int stacksize;
public:
	SqStack();					//�����ջ
	~SqStack();					//�������е�ջ
	Status ClearStack();		//������ջ�ÿ�ջ
	Status Top(SElemType& e);	//ȡջ��Ԫ��
	Status Pop(SElemType& e);	//����ջ��Ԫ��
	Status Push(SElemType e);	//��Ԫ����ջ
	bool StackEmpty();			//�Ƿ�Ϊ��ջ
};

template <class SElemType>
SqStack<SElemType>::SqStack()
{
	base = new(nothrow) SElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
}

template <class SElemType>
SqStack<SElemType>::~SqStack()
{
	if (base)
		delete base;
	stacksize = 0;
}

template <class SElemType>
Status SqStack<SElemType>::ClearStack()
{
	//������ԭ�пռ�
	if (base)
		delete base;
	//��������
	base = new(nothrow) SElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
	return OK;
}

template <class SElemType>
Status SqStack<SElemType>::Top(SElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(top - 1);
	return OK;
}

template <class SElemType>
Status SqStack<SElemType>::Pop(SElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(--top);
	return OK;
}

template <class SElemType>
Status SqStack<SElemType>::Push(SElemType e)
{
	if (top - base >= stacksize) {
		SElemType* newbase = new(nothrow) SElemType[stacksize + STACKINCREMENT];
		if (!newbase)
			exit(SOVERFLOW);
		memcpy(newbase, base, sizeof(SElemType) * stacksize);
		delete base;
		base = newbase;
		top = base + stacksize;
		stacksize += STACKINCREMENT;
	}
	*top = e;
	top++;
	return OK;
}

template <class SElemType>
bool SqStack<SElemType> ::StackEmpty()
{
	return base == top;
}

typedef char TElemType;

typedef struct BiTNode {
	TElemType data;
	BiTNode* lchild, * rchild;
}*BiTree;

Status CreateBiTree(BiTree& T, const int n)
{
	struct Node {
		BiTree bitree;
		int state;
		Node(BiTree b = NULL, int s = 0)
		{
			bitree = b;
			state = s;
		}
	}p;
	SqStack<Node> stack;
	int i = 0, j = 0;
	do {
		string instr;
		char name;
		cin >> instr;
		if (instr == "push") {
			i++;
			cin >> name;
			BiTree newnode = new(nothrow) BiTNode;
			if (!newnode)
				exit(TOVERFLOW);
			newnode->data = name;
			newnode->lchild = newnode->rchild = NULL;
			
			//�Ƿ��Ǹ��ڵ�
			if (i == 1) {
				T = newnode;
				stack.Push(Node(newnode, 0));
			}
			else {
				stack.Pop(p);
				if (p.state == 0) {			//���ҽڵ㶼��û�б����ù�
					p.state++;
					stack.Push(p);
					p.bitree->lchild = newnode;
					//cout << p.bitree->data << "�����ӽڵ���" << newnode->data << endl;
				}
				else if (p.state == 1) {	//��ڵ����ù�
					//�ҽڵ����ú� ��ǰ�ڵ㲻��Ҫ�ٱ�������
					p.bitree->rchild = newnode;
					//cout << p.bitree->data << "�����ӽڵ���" << newnode->data << endl;
				}
				stack.Push(Node(newnode, 0));
			}
		}
		else if (instr == "pop") {
			j++;
			stack.Pop(p);
			p.state++;
			stack.Push(p);
			if (p.state >= 2)
				stack.Pop(p);
		}
		stack.Top(p);


	} while (i < n || j < n);
	
	return OK;
}

//�ݹ鷽��-�������
Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T) {
		if (PostOrderTraverse(T->lchild, visit) == OK)
			if (PostOrderTraverse(T->rchild, visit) == OK)
				if ((*visit)(T->data) == OK)
					return OK;
		return ERROR;
	}
	else   //��������OK
		return OK;
}

Status VisitPrintNormal(TElemType e)
{
	cout << e;
	return OK;
}

int main()
{
	BiTree tree;

	int n;
	cin >> n;
	CreateBiTree(tree, n);

	PostOrderTraverse(tree, VisitPrintNormal);

	return 0;
}
