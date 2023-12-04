#include <iostream>
#include <cstring>
using namespace std;

typedef int Status;
#define QOVERFLOW -2
#define ERROR -1
#define OK	0

//�洢Ԫ�ص�����
typedef struct{
	int x;
	int y;
}QElemtype;

//�����һ���ڵ�
typedef struct QNode{
	QElemtype data;
	QNode* next;
}QNode, * QueuePtr;

class LinkQueue {
private:
	QueuePtr front;
	QueuePtr rear;
public:
	LinkQueue();					//����һ���ն���
	~LinkQueue();					//���ٶ���Q
	Status EnQueue(QElemtype e);	//�ڶ�β����Ԫ��e
	Status DeQueue(QElemtype& e);	//�������׵�Ԫ��(���ǿ�)
	Status GetHead(QElemtype& e);	//ȡ���׵�Ԫ�أ���������
	bool QueueEmpty();				//�ж϶����Ƿ�Ϊ��
};

LinkQueue::LinkQueue()
{
	front = rear = new(nothrow) QNode;
	if (!front)
		exit(QOVERFLOW);
	front->next = NULL;
}

LinkQueue::~LinkQueue()
{
	while (front) {
		rear = front->next;
		delete front;
		front = rear;
	}
}

Status LinkQueue::EnQueue(QElemtype e)
{
	QueuePtr p = new(nothrow) QNode;
	if (!p)
		exit(QOVERFLOW);
	p->data = e;
	p->next = NULL;
	rear->next = p;
	rear = p;
	return OK;
}

Status LinkQueue::DeQueue(QElemtype& e)
{
	if (front == rear)
		return ERROR;
	QueuePtr p = front->next;
	e = p->data;
	front->next = p->next;
	if (rear == p)
		rear = front;
	delete p;
	return OK;
}

Status LinkQueue::GetHead(QElemtype& e)
{
	if (front == rear)
		return ERROR;
	QueuePtr p = front->next;
	e = p->data;
	return OK;
}

bool LinkQueue::QueueEmpty()
{
	return rear == front;
}

void bfs(int n, int m, bool map[1010][1010], bool vis[1010][1010], int x, int y)
{
	LinkQueue Queue;
	QElemtype pst = { x, y }, curpst;
	Queue.EnQueue(pst);
	vis[x][y] = true;
	const int dx[] = { 0, 0, -1, 1 };
	const int dy[] = { -1, 1, 0, 0 };
	while (!Queue.QueueEmpty()) {
		int newx, newy;
		Queue.DeQueue(curpst);
		for (int i = 0; i < 4; i++) {
			newx = curpst.x + dx[i];
			newy = curpst.y + dy[i];
			if (!map[newx][newy] || vis[newx][newy] || newx < 0 || newx >= n || newy < 0 || newy >= m)
				continue;
			pst = { newx, newy };
			vis[newx][newy] = true;
			Queue.EnQueue(pst);
		}
	}
}

bool map[1010][1010];
bool vis[1010][1010];
int main()
{
	memset(vis, 0, sizeof(vis));
	int n, m, count = 0;

	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> map[i][j];

	for (int i = 1; i < n - 1; i++)
		for (int j = 1; j < m - 1; j++) {
			if (map[i][j] && !vis[i][j]) {
				count++;
				bfs(n, m, map, vis, i, j);
			}
		}

	cout << count << endl;

	return 0;
}