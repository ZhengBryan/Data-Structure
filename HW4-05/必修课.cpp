#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
int n, m;
struct ArcNode {
	int adjvex;				//�û����յ�
	ArcNode* nextarc;		//��̵Ļ�
	//�����б���Ȩ��
};

typedef struct VNode {
	int in_degree = 0;
	int val;				//����ѧʱ
	int max_preval = 0;		//ǰ�������ۼ�����֧
	vector<int> pre;		//ǰ�����(���ܶ����ͬ)
	ArcNode* firstarc = NULL;
}*AdjList;

struct ALGraph {
	AdjList vertices;
	int vexnum, arcnum;
};

void AddArc(ALGraph& graph, int src, int dst)
{
	ArcNode* p = graph.vertices[src].firstarc;
	ArcNode* q = new(nothrow) ArcNode;
	if (!q)
		exit(-1);
	q->adjvex = dst;

	if (p) {
		while (p->nextarc)
			p = p->nextarc;
		p->nextarc = q;
	}
	else
		graph.vertices[src].firstarc = q;

	q->nextarc = NULL;
}

bool TopologicalSort(ALGraph& G)
{
	int cnt = 0;
	while (true) {
		int cur;
		for (cur = 1; cur <= G.vexnum; cur++)
			if (G.vertices[cur].in_degree == 0)
				break;

		if (cur > G.vexnum)
			break;		//û�����Ϊ0�ĵ���

		//cout << "���ڵ�" << cur <<",ǰ���ṩ" <<G.vertices[cur].max_preval << endl;

		cnt++;
		G.vertices[cur].in_degree--;	//��Ϊ-1
		G.vertices[cur].val += G.vertices[cur].max_preval;
		for (ArcNode* p = G.vertices[cur].firstarc; p; p = p->nextarc) {
			G.vertices[p->adjvex].in_degree--;
			//���¶���һ�����Ĺ���ֵ
			if (G.vertices[p->adjvex].max_preval < G.vertices[cur].val) {
				//if (G.vertices[p->adjvex].pre.size() != 0)
				//	cout << p->adjvex << "�����ֵԭ������" << G.vertices[p->adjvex].pre[0] << "�ṩ��" << G.vertices[p->adjvex].max_preval << ", ���ڸ���Ϊ" << cur << "�ṩ��" << G.vertices[cur].val << endl;
				//else
				//	cout << p->adjvex << "��" << cur << "�ṩ�׸����ֵ" << G.vertices[cur].val << endl;
				G.vertices[p->adjvex].pre.clear();
				G.vertices[p->adjvex].pre.push_back(cur);
				G.vertices[p->adjvex].max_preval = G.vertices[cur].val;
			}
			else if (G.vertices[p->adjvex].max_preval == G.vertices[cur].val)
				G.vertices[p->adjvex].pre.push_back(cur);
		}
	}
	if (cnt == G.vexnum)
		return true;
	else
		return false;
}

/**
 * @brief ������ĳ����Ƿ��ǹؼ����
 * @param graph ������ͼ
 * @param cur ��ǰ���ڽ��
 * @param tgt �������Ľڵ�
 * @return �Ƿ���Ӱ����ʱ���Ĺؼ����
*/
bool dfs_relevance(ALGraph graph, int cur, int tgt){
	if (cur == tgt)
		return true;
	//�ɹ��ߵ���һ�Ż������� ��֧·û��tgt
	if (graph.vertices[cur].pre.size() == 0)
		return false;

	//�����������ʱǰ��
	for (int i = 0; i < graph.vertices[cur].pre.size(); i++) {
		//��һ����֧�к�tgt �ͻ�ı���ʱ��
		if (dfs_relevance(graph, graph.vertices[cur].pre[i], tgt) == true)
			return true;
	}
	return false;
}

int main()
{
	ALGraph graph;
	cin >> graph.vexnum;
	//�±��1��ʼ ����һ������superend
	graph.vertices = new(nothrow) VNode[graph.vexnum + 2];

	for (int i = 1; i <= graph.vexnum; i++) {
		int num, pre;
		cin >> graph.vertices[i].val;
		cin >> num;
		for (int j = 0; j < num; j++) {
			cin >> pre;
			graph.vertices[i].in_degree++;
			AddArc(graph, pre, i);
		}
	}

	for (int i = 1; i <= graph.vexnum; i++) {
		//����Ϊ0�ĵ��һ���ߵ�superend
		if (!graph.vertices[i].firstarc) {
			AddArc(graph, i, graph.vexnum + 1);
		}
	}

	TopologicalSort(graph);

	for (int i = 1; i <= graph.vexnum; i++) {
		cout << graph.vertices[i].val << " " << dfs_relevance(graph, graph.vexnum + 1, i) << endl;
	}


	return 0;
}