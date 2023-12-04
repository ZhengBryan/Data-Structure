#include <iostream>
#include <string>
#include <string.h>
using namespace std;

#define STACK_INIT_SIZE 100000
#define STACKINCREMENT 10

typedef int Status;

#define OK 1
#define ERROR -1
#define SOVERFLOW -2
#define TOVERFLOW -2
#define QOVERFLOW -2

struct set {
	char letter;
	int value;
};

template <class QElemType>
class SqQueue {
private:
	QElemType* base;
	int MAXQSIZE;
	int front;
	int rear;
public:
	SqQueue(int maxqsize);		//�����ն��У����캯����
	~SqQueue();					//���ٶ��У�����������
	int QueueLength();		//��ȡ���г���
	Status EnQueue(QElemType e);		//��Ԫ�����
	Status DeQueue(QElemType& e);		//����Ԫ�س���
	Status GetHead(QElemType& e);		//��ȡ����Ԫ��
	Status ClearQueue();	//��ն���
	bool QueueEmpty();		//�ж϶����Ƿ�Ϊ��
	Status PrintQueue(ostream& out);	//�Ӷ�����һ���Ԫ��
};

template <class QElemType>
SqQueue <QElemType>::SqQueue(int maxqsize)
{
	MAXQSIZE = maxqsize + 1;  //��һ��λ�����������Ϳ�
	base = new(nothrow) QElemType[MAXQSIZE];
	if (!base)
		exit(QOVERFLOW);
	front = rear = 0;
}

template <class QElemType>
SqQueue <QElemType>::~SqQueue()
{
	if (base)
		delete base;
	front = rear = 0;
}

template <class QElemType>
Status SqQueue <QElemType>::ClearQueue()
{
	front = rear = 0;
	return OK;
}

template <class QElemType>
int SqQueue <QElemType> ::QueueLength()
{
	return (rear - front + MAXQSIZE) % MAXQSIZE;
}

template <class QElemType>
Status SqQueue <QElemType> ::EnQueue(QElemType e)
{
	if ((rear + 1) % MAXQSIZE == front)
		return ERROR;
	base[rear] = e;
	rear = (rear + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::DeQueue(QElemType& e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	front = (front + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::GetHead(QElemType& e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	return OK;
}

template <class QElemType>
bool SqQueue <QElemType>::QueueEmpty()
{
	return front == rear;
}

template <class QElemType>
Status SqQueue<QElemType>::PrintQueue(ostream& out)
{
	if (front == rear) {
		out << "Queue is Empty." << endl;
		return ERROR;
	}

	for (int i = front; i != rear; i = (i + 1) % MAXQSIZE)
		out << base[i] << " ";
	out << endl;
	return OK;
}


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


void MakeExpressionTree(SqStack<BiTree>& Value, SqStack<BiTree>& Operator)
{
	BiTree opr, a, b;
	Operator.Pop(opr);
	Value.Pop(a);
	Value.Pop(b);
	opr->lchild = b;
	opr->rchild = a;
	Value.Push(opr);
}

Status CreateBiTree(BiTree& T)
{
	string input;
	cin >> input;

	SqStack<BiTree> Operator, Value;
	for (unsigned int i = 0; i < input.size(); i++) {
		BiTree q, p = new(nothrow) BiTNode;
		if (!p)
			exit(TOVERFLOW);
		p->data = input[i];
		p->lchild = p->rchild = NULL;
		if (input[i] == '(' || input[i] == ')' || input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
			switch (input[i]) {
				case '(':
					Operator.Push(p);
					break;
				case ')':
					while (!Operator.StackEmpty() && (Operator.Top(q), q->data != '('))
					{
						MakeExpressionTree(Value, Operator);
					}
					Operator.Pop(q); //ȥ��������
					break;
				case '*':
				case '/':
					while (!Operator.StackEmpty() && (Operator.Top(q), q->data == '*' || q->data == '/'))
					{
						MakeExpressionTree(Value, Operator);
					}
					Operator.Push(p);
					break;
				case '+':
				case '-':
					while (!Operator.StackEmpty() && (Operator.Top(q), q->data != '('))
					{
						MakeExpressionTree(Value, Operator);
					}
					Operator.Push(p);
					break;
			}
		}
		else {
			Value.Push(p);
		}
	}
	
	//���ջ�����������
	while (!Operator.StackEmpty())
		MakeExpressionTree(Value, Operator);
	
	return Value.Top(T);
}

//�ݹ鷽��-�������
Status PostOrderTraverse(BiTree T, SqStack<int>& stack, Status(*visit)(SqStack<int>& stack, TElemType e, set* list, int n), set* list, int n)
{
	if (T) {
		if (PostOrderTraverse(T->lchild, stack, visit, list, n) == OK)
			if (PostOrderTraverse(T->rchild, stack, visit, list, n) == OK)
				if ((*visit)(stack, T->data, list, n) == OK)
					return OK;
		return ERROR;
	}
	else   //��������OK
		return OK;
}

//ȡ����ֵ
int GetValue(set* list, int n, char e)
{
	for (int i = 0; i < n; i++) {
		if (list[i].letter == e)
			return list[i].value;
	}
	return ERROR;
}

//visit���� �������+���ʽ��ֵ
Status Print(SqStack<int>& stack, TElemType e, set* list, int n)
{
	cout << e;
	if (e == '*' || e == '/' || e == '+' || e == '-') {
		int a, b;
		stack.Pop(b);
		stack.Pop(a);
		switch (e) {
			case '*':
				stack.Push(a * b);
				break;
			case '/':
				stack.Push(a / b);
				break;
			case '+':
				stack.Push(a + b);
				break;
			case '-':
				stack.Push(a - b);
				break;
		}
	}
	else  //��������ջ
		stack.Push(GetValue(list, n, e));
	return OK;
}

void PrintSpace(int n)
{
	for (int i = 0; i < n; i++)
		cout << " ";
}

int pow2(int n)
{
	int ans = 1;
	for (int i = 0; i < n; i++)
		ans *= 2;
	return ans;
}

Status PrintTree(BiTree T)
{
	int depth = 0;
	{
		struct NodeWithDepth {
			BiTree node;
			int depth;
			NodeWithDepth(BiTree bb = NULL, int dd = 1)
			{
				node = bb;
				depth = dd;
			}
		};
		SqQueue<NodeWithDepth> queue(1000);  //queue����󳤶�

		NodeWithDepth p;
		queue.EnQueue(NodeWithDepth(T, 1));
		while (!queue.QueueEmpty()) {
			if (queue.DeQueue(p) != OK)
				return ERROR;
			depth = max(depth, p.depth);
			if (p.node->lchild)
				queue.EnQueue(NodeWithDepth(p.node->lchild, p.depth + 1));
			if (p.node->rchild)
				queue.EnQueue(NodeWithDepth(p.node->rchild, p.depth + 1));
		}
	}
	/* �������������� */

	/* ���¿�ʼ����� */
	{
		struct NodeWithNo {
			BiTree node;
			int depth;
			int no;
			NodeWithNo(BiTree bb = NULL, int dd = 1, int nn = 1)
			{
				node = bb;
				depth = dd;
				no = nn;
			}
		};
		SqQueue<NodeWithNo> queue(1000), queue2(1000);  //queue����󳤶�

		queue.ClearQueue();
		queue.EnQueue(NodeWithNo(T, 1, 1));
		NodeWithNo p, q, r, s;
		//����һ�е�ǰ�ÿո�
		PrintSpace(pow2(depth - 1) - 1);
		while (!queue.QueueEmpty()) {
			if (queue.DeQueue(p) != OK)
				return ERROR;
			if (p.node->lchild)
				queue.EnQueue(NodeWithNo(p.node->lchild, p.depth + 1, 2 * p.no));
			if (p.node->rchild)
				queue.EnQueue(NodeWithNo(p.node->rchild, p.depth + 1,2 * p.no + 1));
			//�����ǰ�ڵ�
			cout << p.node->data;
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
							PrintSpace((s.no - r.no)* pow2((depth - s.depth) + 1) - 3);
						}
					}
					cout << endl;
					PrintSpace( pow2(depth - q.depth) - 1 + (q.no - pow2(p.depth))* pow2((depth - q.depth) + 1));
				}
			}
		}
	}
	return OK;
}


int main()
{
	BiTree tree;
	SqStack<int> answer;	//��ű��ʽ��

	CreateBiTree(tree);

	//�������ʼ������������ֵ
	int n;
	cin >> n;
	set* list = new(nothrow) set[n];
	if (!list)
		return TOVERFLOW;
	for (int i = 0; i < n; i++)
		cin >> list[i].letter >> list[i].value;
	

	//�������(˳�㽫���ʽѹջ)
	PostOrderTraverse(tree, answer, Print, list, n);
	cout << endl;

	PrintTree(tree);

	//������ʽ��ֵ
	int ans;
	answer.Top(ans);
	cout << ans;

	return 0;
}
