#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// �����
struct edge
{
    int u, v;  // �ߵ������˵���
    float cost;  // �ߵ�Ȩֵ
    edge(int x, int y, float c) : u(x), v(y), cost(c) {}
};

// �ߵıȽϺ���
bool cmp(edge a, edge b)
{
    return a.cost < b.cost;
}

// ����x���ڼ��ϵĸ����
int findFather(vector<int> father, int x)
{
    int a = x;
    while (x != father[x])
    {
        x = father[x];
    }

    // ����father����
    int z;
    while (a != father[a])
    {
        z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

// Kruskal�㷨������ͼ����С������
void Kruskal(int n, int m, vector<edge>& E, vector<edge>& res, float& totalCost)
{
    // n:�������
    // m:�ߵĸ���
    // E:�ߵĺϼ�
    vector<int> father(n);
    int faU, faV;
    for (int i = 0; i < n; ++i)
    {
        father[i] = i;
    }
    sort(E.begin(), E.end(), cmp);
    for (int i = 0; i < m; ++i)
    {
        faU = findFather(father, E[i].u);
        faV = findFather(father, E[i].v);
        if (faU != faV)
        {
            res.push_back(E[i]);
            father[faU] = faV;
            totalCost += E[i].cost;
        }
    }
}

int main()
{
    vector<edge> E = { edge(0, 7, 0.16),
                      edge(2, 3, 0.17),
                      edge(1, 7, 0.19),
                      edge(0, 2, 0.26),
                      edge(5, 7, 0.28),
                      edge(1, 3, 0.29),
                      edge(1, 5, 0.32),
                      edge(2, 7, 0.34),
                      edge(4, 5, 0.35),
                      edge(1, 2, 0.36),
                      edge(4, 7, 0.37),
                      edge(0, 4, 0.38),
                      edge(6, 2, 0.40),
                      edge(3, 6, 0.52),
                      edge(6, 0, 0.58),
                      edge(6, 4, 0.93) };
    random_shuffle(E.begin(), E.end());
    cout << "Original Undirected Graphs: " << endl;
    for (size_t i = 0; i < E.size(); ++i)
    {
        cout << "edge: " << E[i].u << " " << E[i].v << " " << E[i].cost << endl;
    }
    cout << "----------------" << endl;
    int n = 8;
    int m = 16;
    vector<edge> res;
    float totalCost = 0;
    Kruskal(n, m, E, res, totalCost);
    cout << "Minimum Spanning Trees: " << endl;
    for (size_t i = 0; i < res.size(); ++i)
    {
        cout << "edge: " << res[i].u << " " << res[i].v << " " << res[i].cost << endl;
    }
    cout << endl;
    cout << "num of edge: " << res.size() << endl;
    cout << "total cost: " << totalCost << endl;

    return 0;
}
