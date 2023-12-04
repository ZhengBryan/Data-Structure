#include <iostream>
#include <cstring>
using namespace std;
#define STACK_INIT_SIZE 1000
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
	if (base)
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

void Operate(SqStack& Value, SqStack& Operator)
{
	SElemType v1, v2, o;
	Operator.Pop(o);
	switch (o) {
		case '!':
			Value.Pop(v1);
			v1 = 'F' + 'V' - v1;
			Value.Push(v1);
			break;
		case '&':
			Value.Pop(v1);
			Value.Pop(v2);
			v1 = (v1 == 'V' && v2 == 'V') ? 'V' : 'F';
			Value.Push(v1);
			break;
		case '|':
			Value.Pop(v1);
			Value.Pop(v2);
			v1 = (v1 == 'V' || v2 == 'V') ? 'V' : 'F';
			Value.Push(v1);
			break;
	}
}

int main()
{
	SqStack Value, Operator;

	SElemType ch, get;
	int times = 0;
	while((ch = getchar()) != EOF) {
		if (ch == '\n') {
			cout << "Expression " << ++times << ": ";
			//���ջ�����������
			while (!Operator.StackEmpty())
				Operate(Value, Operator);

			SElemType Answer;
			Value.Top(Answer);
			cout << Answer << endl;
			Value.ClearStack();
		}

		if (ch == 'F' || ch == 'V')
			Value.Push(ch);
		else {
			switch (ch) {
				case '(':
					Operator.Push(ch);
					break;
				case ')':
					while (!Operator.StackEmpty() && (Operator.Top(get), get != '('))
					{
						Operate(Value, Operator);
					}
					Operator.Pop(get); //ȥ��������
					break;
				case '!':
					Operator.Push(ch);
					break;
				case '&':
					while (!Operator.StackEmpty() && (Operator.Top(get), get == '!'))
					{
						Operate(Value, Operator);
					}
					Operator.Push(ch);
					break;
				case '|':
					while (!Operator.StackEmpty() && ((Operator.Top(get), get == '!') || get == '&'))
					{
						Operate(Value, Operator);
					}
					Operator.Push(ch);
					break;
			}
		}
	}

	return 0;
}