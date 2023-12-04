#include <iostream>
#include <queue>
using namespace std;

//�����������Ľ��
struct node {
	int value;		//�����ֵ
	int times;		//���ֵĴ���
	node* lchild, * rchild;
};

/**
 * @brief �����½��
 * @param n �½��ָ��	
 * @param value ��ֵ
*/
void CreateNode(node*& n, int value)
{
	n = new(nothrow) node;
	if (!n)
		exit(-1);
	n->value = value;
	n->times = 1;
	n->lchild = n->rchild = NULL;
}

/**
 * @brief �ڶ����������½��
 * @param T ��ǰ�����Ľ��
 * @param value �½�����ֵ
*/
void Insert(node*& T, int value)
{
	//�����
	if (!T)
		CreateNode(T, value);
	else if (T->value == value) {
		T->times++;
	}
	else if (T->value > value) {
		if (T->lchild)
			Insert(T->lchild, value);
		else
			CreateNode(T->lchild, value);
	}
	else {
		if (T->rchild)
			Insert(T->rchild, value);
		else
			CreateNode(T->rchild, value);
	}
}

/**
 * @brief �ڶ������в��ҽ��
 * @param T ��ǰ�����Ľ��
 * @param value ���ҵĽ����ֵ
*/
int Search(node* T, int value)
{
	if (!T)
		return 0;
	else if (T->value == value)
		return T->times;
	else if (T->value > value) 
		Search(T->lchild, value);
	else 
		Search(T->rchild, value);
}

/**
 * @brief ɾ���������еĽ��
 * @param T ��ǰ�����Ľ��
 * @param value ɾ���Ľ��ֵ
 * @return �Ƿ�ɹ�ɾ��
*/
bool Delete(node*& T, int value)
{
	if (!T)
		return false;  //û�и�Ԫ��
	else if (T->value == value) {
		if (T->times != 1)
			T->times--;
		//ֻ�е�������
		else if (!T->rchild) {
			node* q = T;
			T = T->lchild;
			delete q;
		}
		else if (!T->lchild) {
			node* q = T;
			T = T->rchild;
			delete q;
		}
		//������������
		else {
			node* q = T, * s = T->lchild;
			while (s->rchild) {
				q = s;
				s = s->rchild;
			}
			T->value = s->value;
			T->times = s->times;
			//�������һ��ʼ����û�������� ��qû�пճ����Һ�������s������
			//(sԭ������������ıߺ��ӿճ�)
			if (q != T)
				q->rchild = s->lchild;
			else
				q->lchild = s->lchild;
			delete s;
		}
		return true;
	}
	else if (T->value > value)
		return Delete(T->lchild, value);
	else
		return Delete(T->rchild, value);
}

/**
 * @brief ��ѯ�������������Сֵ
 * @param T ��ǰ�����Ľ��
*/
int GetMin(node* T)
{
	if (T->lchild)
		return GetMin(T->lchild);
	else
		return T->value;
}

/**
 * @brief ���������������� ��¼������q��
 * @param T ��ǰ�����Ľ��
 * @param q ���ڼ�¼�Ķ���
*/
void Traverse(node* T, queue<int>& q)
{
	if (!T)
		return;
	Traverse(T->lchild, q);
	q.push(T->value);
	Traverse(T->rchild, q);
}

int main()
{
	int n;
	node* root = NULL;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int opt;
		queue<int> q;
		cin >> opt;
		switch (opt) {
			int x;
			case 1:
				cin >> x;
				Insert(root, x);
				break;
			case 2:
				cin >> x;
				if (!Delete(root, x))
					cout << "None" << endl;
				break;
			case 3:
				cin >> x;
				cout << Search(root, x) << endl;
				break;
			case 4:
				cout << GetMin(root) << endl;
				break;
			case 5:
				cin >> x;
				Traverse(root, q);
				int ans = -1;
				while (!q.empty() && q.front() < x) {
					ans = q.front();
					q.pop();
				}
				if (ans == -1)
					cout << "None" << endl;
				else
					cout << ans << endl;
		}
	}
	return 0;
}