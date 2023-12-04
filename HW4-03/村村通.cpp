#define INT_MAX 2147483647
#include <iostream>
#include <cstring>
using namespace std;
int graph[100][100];
int n;
int tot_cost;

struct{
	int adjvex;	  //����ǰ�����̵�V-U�еĽ��
	int lowcost;  //���ӱߵ�Ȩ
}closedge[100];


int minimum()
{
	int min = 0;
	int minv = INT_MAX;
	for(int i = 0; i < n; i++)
		if (closedge[i].lowcost != -1 && closedge[i].lowcost < minv) {
			min = i;
			minv = closedge[i].lowcost;
		}
	return min;
}

void MiniSpanTree_PRIM()
{
	//��0�Ŵ�ׯ��ʼ������
	closedge[0].lowcost = -1;	//�ϳ����
	for (int j = 1; j < n; j++)
		closedge[j] = { 0, graph[0][j] };

	for (int i = 1; i < n; i++) {
		int k = minimum();
		tot_cost += closedge[k].lowcost;
		closedge[k].lowcost = -1;

		//�����µ�closedge
		for (int j = 0; j < n; j++) {
			if (graph[k][j] < closedge[j].lowcost)
				closedge[j] = { k, graph[k][j] };
		}
	}
}

int main() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
			//�Ѿ��ϲ��ı��
			if (i == j)
				graph[i][j] = -1;
		}
	}

	int m;
	cin >> m;
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a - 1][b - 1] = 0;  //��·����Ϊ0 �㷨����ѡ���Ҳ��ƶ�������
		graph[b - 1][a - 1] = 0;
	}


	MiniSpanTree_PRIM();

	cout << tot_cost << endl;

	return 0;
}