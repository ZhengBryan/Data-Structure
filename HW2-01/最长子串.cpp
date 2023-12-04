#include <iostream>
#include <cstring>
using namespace std;
char input[100010];
bool valid[100010];

#define STACK_INIT_SIZE 100000
#define STACKINCREMENT 10

typedef int Status;
#define SOVERFLOW -2
#define ERROR -1
#define OK	0

typedef int SElemType;  //��¼�����ŵ��±�
struct SqStack{
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


int main()
{
	SqStack stack;
	int len;
	for (int i = 0; i < 100010; i++) {
		input[i] = getchar();
		if (input[i] == '\r' || input[i] == '\n') {
			len = i;
			break;
		}
		if (input[i] == '(') {
			stack.Push(i);
		}
		else if (input[i] == ')') {
			if (stack.StackEmpty())
				continue;
			else {
				SElemType get;
				stack.Pop(get);
				valid[i] = true;
				valid[get] = true;
			}
		}
	}
	
	int MaxIndex = 0, MaxLen = 0, CurIndex = 0, CurLen = 0;
	for (int i = 0; i < len + 1; i++) {
		if (CurLen == 0 && valid[i]) {
			CurIndex = i;
			CurLen++;
		}
		else if (valid[i])
			CurLen++;
		else if (CurLen && !valid[i]) {
			MaxIndex = CurLen > MaxLen ? CurIndex : MaxIndex;
			MaxLen = CurLen > MaxLen ? CurLen : MaxLen;
			CurLen = 0;
		}
	}

	cout << MaxLen << " " << MaxIndex << endl;

	return 0;
}