#include <iostream>
#include <conio.h>
#include <string>
#include <cstring>
using namespace std;
#define MAX_VEX_NUM 20

struct Graph {
	//��¼��㡢����
	int vex_num = 5;
	int arc_num = 8;	
	//�ڽӾ���
	int map[MAX_VEX_NUM + 1][MAX_VEX_NUM + 1] =
	{
		//�±��1��ʼ �±�0��¼�õ����ӵı���
		{},				
		{3, 0, 1, 1, 0, 1},
		{3, 1, 0, 1, 0, 1},
		{4, 1, 1, 0, 1, 1},
		{2, 0, 0, 1, 0, 1},
		{4, 1, 1, 1, 1, 0}
	};
};

/**
 * @brief ���������������ͼ�������ж�ͼ�Ƿ���ͨ��
 * @param graph �жϵ�ͼ
 * @param cur ��ǰ�Ľ��
 * @param vis �洢����Ƿ񱻷��ʹ�
*/
void dfsGraph(const Graph& graph, int cur, bool* vis)
{
	vis[cur] = true;
	for (int i = 1; i <= graph.vex_num; i++)
		if (graph.map[cur][i] && !vis[i])
			dfsGraph(graph, i, vis);
}

/**
 * @brief �жϵ�ǰͼ�Ƿ���ڿ��е�ŷ��·��
 * @param graph �жϵ�ͼ
*/
bool isEulerPathExist(const Graph& graph)
{
	//���ж�ͼ�Ƿ���ͨ
	bool vis[MAX_VEX_NUM] = {0};
	dfsGraph(graph, 1, vis);
	for (int i = 1; i <= graph.vex_num; i++)
		if (!vis[i])
			return false;

	//���жϱ���Ϊ�����ĵ����
	int odd_num = 0;
	for (int i = 1; i <= graph.vex_num; i++) {
		if (graph.map[i][0] % 2 == 1)
			odd_num++;
	}

	if (odd_num == 0 || odd_num == 2)
		return true;
	else
		return false;
}

/**
 * @brief ���� "���� ���� �߾�����Ϣ" �ķ�ʽ����ͼ
 * @param graph �����ͼ
*/
void inputGraph(Graph& graph)
{
	while (true) {
		cout << "�����붥���� : ";
		cin >> graph.vex_num;
		if (cin.good() && graph.vex_num <= MAX_VEX_NUM)
			break;
		else if (cin.good())
			cout << "�������Ӧ�ò�����" << MAX_VEX_NUM << "!" << endl;
		else
			cout << "�����ʽ�Ƿ���" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	while (true) {
		cout << "��������� : ";
		cin >> graph.arc_num;
		if (cin.good())
			break;
		else
			cout << "�����ʽ�Ƿ���" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	cout << "������" << graph.arc_num << "���Ա����ӵĶ������ :" << endl;
	memset(graph.map, 0, sizeof(graph.map));
	for (int i = 0; i < graph.arc_num; i++) {
		int src, dst;
		while (true) {
			cin >> src >> dst;
			if (cin.good())
				break;
			else
				cout << "�����ʽ�Ƿ�, ���ٴ�����ñߵ�������!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		//0��ʾ����֮���ޱ�, 1��ʾ�б�
		graph.map[src][dst] = 1;
		graph.map[dst][src] = 1;
		//�±�0����¼ÿ��������ӵı���
		graph.map[src][0]++;
		graph.map[dst][0]++;
	}
}

/**
 * @brief ���Ѵ�ӡŷ��·�� 
 * @param graph ������ͼ 
 * @param pst ��ǰ���ڶ˵�
 * @param dep ��չ�����
 * @param s	  ���������
*/
void printEulerPath(Graph& graph, int pst, int dep, string s)
{
	static int count = 0;
	if (dep >= graph.arc_num) {
		cout << "path" << ++count << " : " << s << endl;
		return;
	}
	else {
		for (int i = 1; i <= graph.vex_num; i++) {
			if (graph.map[pst][i]) {
				//ɾ���߹��ı�
				graph.map[pst][i] = 0;
				graph.map[i][pst] = 0;

				printEulerPath(graph, i, dep + 1, s + to_string(i) + ' ');

				graph.map[pst][i] = 1;
				graph.map[i][pst] = 1;
			}
		}
	}
}

int main(){
	Graph graph;

	cout << "�Ƿ��ӡ��Ŀ����? [��Ŀ����(Y/y) : ����ָ��(N/n)]" << endl;
	bool input;
	while (true) {
		char ch = _getche();
		if (ch == 'Y' || ch == 'y') {
			input = false;
			break;
		}
		else if (ch == 'N' || ch == 'n') {
			input = true;
			break;
		}
		cout << endl << "������Y(y) �� N(n) ����ѡ��!" << endl;
	}
	cout << endl;

	if (input)
		inputGraph(graph);

	if (isEulerPathExist(graph)) {
		cout << endl << "���е�һ�ʻ�·������ : " << endl;
		for (int i = 1; i <= graph.arc_num; i++)
			printEulerPath(graph, i, 0, to_string(i) + ' ');
	}
	else
		cout << "��ǰ��ͼ�����ڿ��е�һ�ʻ�·��!" << endl;

	return 0;
}