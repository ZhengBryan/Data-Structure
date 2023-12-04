#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;
#define SOVERFLOW -2
#define ERROR -1
#define OK	0

typedef char SElemType; 
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

SqStack::SqStack()
{
	base = new(nothrow) SElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
}

SqStack::~SqStack()
{
	if(base)
		delete base;
	stacksize = 0;
}

Status SqStack::ClearStack()
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

Status SqStack::Top(SElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(top - 1);
	return OK;
}

Status SqStack::Pop(SElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(--top);
	return OK;
}

Status SqStack::Push(SElemType e)
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

bool SqStack::StackEmpty()
{
	return base == top;
}

/* ��Ԫ�ص��±� */
int GetIndex(char* given, int len, char ch)
{
	for (int i = 0; i < len; i++) {
		if (ch == given[i])
			return i;
	}
	return -1;
}

void solve(char* given, int len)
{
	SqStack stack;
	int index = 0, index2;
	bool yes = true;
	for (int i = 0; i < len; i++) {
		char ch = getchar();
		if (ch == EOF)
			exit(0);
		SElemType e;
		if (!stack.StackEmpty() && (stack.Top(e), e == ch))
			stack.Pop(e);
		else if ((index2 = GetIndex(given, len, ch)) >= index) {
			while (index <= index2) {
				stack.Push(given[index]);
				index++;
			}
			if (!stack.StackEmpty() && (stack.Top(e), e == ch)) {
				stack.Pop(e);
			}
		}
		else
			yes = false;
	}
	cout << (yes ? "yes" : "no") << endl;
}

int main()
{
	char given[1010];
	int len;
	scanf("%s\n", given);
	len = strlen(given);

	while (true) {
		solve(given, len);
		if (getchar() != '\n')
			break;
	}
	return 0;
}