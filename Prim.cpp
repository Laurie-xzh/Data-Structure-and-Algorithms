
#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;

/*节点类*/
class Node
{
public:
    Node(char identifier = 0);

    char m_identifier;       //顶点编号
    bool m_isVisited;        //顶点访问标志位：true表示已经被访问
};
Node::Node(char identifier)
{
    m_identifier = identifier;
    m_isVisited = false;
}


/*边类，用于辅助实现生成最小生成树*/
class Edge
{
public:
    Edge(int NodeIndexA = 0, int NodeIndexB = 0, int WeightValue = 0);

    int m_NodeIndexA, m_NodeIndexB;    //边的两端点（索引），这里以无向图为例
    int m_weightValue;                 //边的权值
    bool m_selected;                   //选择标志位，true表示已被选择
};
Edge::Edge(int NodeIndexA, int NodeIndexB, int WeightValue)
{
    m_NodeIndexA = NodeIndexA;
    m_NodeIndexB = NodeIndexB;
    m_weightValue = WeightValue;
    m_selected = false;      //初始时未被选择
}

/*图类*/
class Graph
{
public:
    Graph(int capacity);
    ~Graph();

    int getGraphSize();            //获取当前图的大小
    void resetNode();              //重置所有顶点的访问标志位为false，未访问
    bool addNode(Node* pNode);     //添加新顶点
    bool addEdgeForUndirectedGraph(int row, int col, int val = 1); //添加边以构造无向图，val表示权值，默认权值1
    bool addEdgeForDirectedGraph(int row, int col, int val = 1);   //添加边以构造有向图，val表示权值，默认权值1
    void printMatrix();   //打印邻接矩阵

    void depthFirstTraverse(int nodeIndex);   //深度优先遍历，指定第一个点
    void widthFirstTraverse(int nodeIndex);   //广度优先遍历，指定第一个点

    void MSTPrim(int nodeIndex);        //Prim算法求最小生成树，指定第一个点
    void MSTKruskal();

private:
    bool getValueOfEdge(int row, int col, int& val);  //获取边权值
    void widthFirstTraverseImplement(vector<int> preVec);  //利用vector实现广度优先遍历

    int getMinEdge(vector<Edge> edgeVec);  //Prim算法辅助函数，用于在边集中选择权值最小的边

    int m_iCapacity;     //图容量，即申请的数组空间最多可容纳的顶点个数
    int m_iNodeCount;    //图的现有顶点个数
    Node* m_pNodeArray;  //存放顶点的数组
    int* m_pMatrix;      //为了方便，用一维数组存放邻接矩阵

    Edge* m_pEgde;       //边指针，存储最小生成树的边
};
Graph::Graph(int capacity)
{
    m_iCapacity = capacity;
    m_iNodeCount = 0;

    m_pNodeArray = new Node[m_iCapacity];
    m_pMatrix = new int[m_iCapacity * m_iCapacity];

    for (int i = 0; i < m_iCapacity * m_iCapacity; i++)  //初始化邻接矩阵
    {
        m_pMatrix[i] = 0;
    }

    m_pEgde = new Edge[m_iCapacity - 1];    //最小生成树节点和边数量关系
}
Graph::~Graph()
{
    delete[]m_pNodeArray;
    delete[]m_pMatrix;
    delete[]m_pEgde;
}
int Graph::getGraphSize()
{
    return m_iNodeCount;
}
void Graph::resetNode()
{
    for (int i = 0; i < m_iNodeCount; i++)
    {
        m_pNodeArray[i].m_isVisited = false;
    }
}
bool Graph::addNode(Node* pNode)
{
    if (pNode == NULL)
        return false;
    m_pNodeArray[m_iNodeCount].m_identifier = pNode->m_identifier;
    m_iNodeCount++;
    return true;
}
bool Graph::addEdgeForUndirectedGraph(int row, int col, int val)
{
    if (row < 0 || row >= m_iCapacity)
        return false;
    if (col < 0 || col >= m_iCapacity)
        return false;
    m_pMatrix[row * m_iCapacity + col] = val;
    m_pMatrix[col * m_iCapacity + row] = val;
    return true;
}
bool Graph::addEdgeForDirectedGraph(int row, int col, int val)
{
    if (row < 0 || row >= m_iCapacity)
        return false;
    if (col < 0 || col >= m_iCapacity)
        return false;
    m_pMatrix[row * m_iCapacity + col] = val;
    return true;
}
void Graph::printMatrix()
{
    for (int i = 0; i < m_iCapacity; i++)
    {
        for (int k = 0; k < m_iCapacity; k++)
            cout << m_pMatrix[i * m_iCapacity + k] << " ";
        cout << endl;
    }
}
void Graph::depthFirstTraverse(int nodeIndex)
{
    int value = 0;

    //访问第一个顶点
    cout << m_pNodeArray[nodeIndex].m_identifier << " ";
    m_pNodeArray[nodeIndex].m_isVisited = true;

    //访问其他顶点
    for (int i = 0; i < m_iCapacity; i++)
    {
        getValueOfEdge(nodeIndex, i, value);
        if (value != 0)   //当前顶点与指定顶点连通
        {
            if (m_pNodeArray[i].m_isVisited == true)  //当前顶点已被访问
                continue;
            else           //当前顶点没有被访问，则递归
            {
                depthFirstTraverse(i);
            }
        }
        else       //没有与指定顶点连通
        {
            continue;
        }
    }
}
void Graph::widthFirstTraverse(int nodeIndex)
{
    //访问第一个顶点
    cout << m_pNodeArray[nodeIndex].m_identifier << " ";
    m_pNodeArray[nodeIndex].m_isVisited = true;

    vector<int> curVec;
    curVec.push_back(nodeIndex);      //将第一个顶点存入一个数组
    widthFirstTraverseImplement(curVec);
}
void Graph::widthFirstTraverseImplement(vector<int> preVec)
{
    int value = 0;
    vector<int> curVec;    //定义数组保存当前层的顶点
    for (int j = 0; j < (int)preVec.size(); j++)  //依次访问传入数组中的每个顶点
    {
        for (int i = 0; i < m_iCapacity; i++)  //传入的数组中的顶点是否与其他顶点连接
        {
            getValueOfEdge(preVec[j], i, value);
            if (value != 0)   //连通
            {
                if (m_pNodeArray[i].m_isVisited == true)  //已经被访问
                {
                    continue;
                }
                else   //没有被访问则访问
                {
                    cout << m_pNodeArray[i].m_identifier << " ";
                    m_pNodeArray[i].m_isVisited = true;

                    //保存当前点到数组
                    curVec.push_back(i);
                }
            }
        }
    }

    if (curVec.size() == 0)   //本层次无被访问的点，则终止
    {
        return;
    }
    else
    {
        widthFirstTraverseImplement(curVec);
    }
}
bool Graph::getValueOfEdge(int row, int col, int& val)
{
    if (row < 0 || row >= m_iCapacity)
        return false;
    if (col < 0 || col >= m_iCapacity)
        return false;
    val = m_pMatrix[row * m_iCapacity + col];
    return true;
}
void Graph::MSTPrim(int nodeIndex)
{
    int value = 0;          //存储当前边的权值
    int edgeCount = 0;      //已选出的边数量，用以判断算法终结
    vector<int> nodeVec;    //存储点（索引）集的数组
    vector<Edge> edgeVec;   //存储边的数组

    cout << m_pNodeArray[nodeIndex].m_identifier << endl;

    nodeVec.push_back(nodeIndex);
    m_pNodeArray[nodeIndex].m_isVisited = true;

    while (edgeCount < m_iCapacity - 1)
    {
        int temp = nodeVec.back();           //将当前顶点索引复制给temp
        for (int i = 0; i < m_iCapacity; i++)  //循环判断每一个顶点与当前顶点连接情况
        {
            getValueOfEdge(temp, i, value);
            if (value != 0)  //连通
            {
                if (m_pNodeArray[i].m_isVisited == true) //已经被访问
                    continue;
                else //未被访问,则将边放入被选边集合
                {
                    Edge edge(temp, i, value);
                    edgeVec.push_back(edge);
                }
            }
        }
        /*选择最小边*/
        int edgeIndex = getMinEdge(edgeVec);
        if (edgeIndex == -1)
        {
            cout << "获取最小边失败，请重置后再试！" << endl;
            break;
        }

        edgeVec[edgeIndex].m_selected = true;   //设置选择标志位为true，已被选择

        cout << edgeVec[edgeIndex].m_NodeIndexA << "---" << edgeVec[edgeIndex].m_NodeIndexB << " ";
        cout << edgeVec[edgeIndex].m_weightValue << endl;

        m_pEgde[edgeCount] = edgeVec[edgeIndex];
        edgeCount++;

        /*寻找当前选择的最小边相连的下一个顶点*/
        int nextNodeIndex = edgeVec[edgeIndex].m_NodeIndexB;
        nodeVec.push_back(nextNodeIndex);
        m_pNodeArray[nextNodeIndex].m_isVisited = true;

        cout << m_pNodeArray[nextNodeIndex].m_identifier << endl;
    }
    cout << "最小生成树计算完毕，如上所示！" << endl;
}
void Graph::MSTKruskal()
{

}
int Graph::getMinEdge(vector<Edge> edgeVec)
{
    int minWeight = 0;   //用于辅助选择最小权值边
    int edgeIndex = 0;   //用于存储最小边索引
    int i = 0;

    /*找出第一条未被选择的边*/
    for (; i < (int)edgeVec.size(); i++)
    {
        if (edgeVec[i].m_selected == false)  //当前边未被选择
        {
            minWeight = edgeVec[i].m_weightValue;
            edgeIndex = i;
            break;
        }
    }

    if (minWeight == 0)   //边集所有边被访问
    {
        return -1;
    }

    for (; i < (int)edgeVec.size(); i++)
    {
        if (edgeVec[i].m_selected == true)
            continue;
        else
        {
            if (minWeight > edgeVec[i].m_weightValue)
            {
                minWeight = edgeVec[i].m_weightValue;
                edgeIndex = i;
            }
        }
    }

    return edgeIndex;
}

int main()
{
    Graph* pGraph = new Graph(6);

    cout << "初始化顶点中……" << endl;
    Node* pNodeA = new Node('A');
    Node* pNodeB = new Node('B');
    Node* pNodeC = new Node('C');
    Node* pNodeD = new Node('D');
    Node* pNodeE = new Node('E');
    Node* pNodeF = new Node('F');

    cout << "添加顶点至图中……" << endl;
    pGraph->addNode(pNodeA);
    pGraph->addNode(pNodeB);
    pGraph->addNode(pNodeC);
    pGraph->addNode(pNodeD);
    pGraph->addNode(pNodeE);
    pGraph->addNode(pNodeF);

    pGraph->addEdgeForUndirectedGraph(0, 1, 6);
    pGraph->addEdgeForUndirectedGraph(0, 4, 5);
    pGraph->addEdgeForUndirectedGraph(0, 5, 1);
    pGraph->addEdgeForUndirectedGraph(1, 5, 2);
    pGraph->addEdgeForUndirectedGraph(1, 2, 3);
    pGraph->addEdgeForUndirectedGraph(2, 5, 8);
    pGraph->addEdgeForUndirectedGraph(2, 3, 7);
    pGraph->addEdgeForUndirectedGraph(3, 5, 4);
    pGraph->addEdgeForUndirectedGraph(3, 4, 2);
    pGraph->addEdgeForUndirectedGraph(4, 5, 9);


    cout << "邻接矩阵如下:" << endl;
    pGraph->printMatrix();
    cout << endl << endl;

    cout << "深度优先遍历：" << endl;
    pGraph->depthFirstTraverse(0);
    cout << endl << endl;

    pGraph->resetNode();

    cout << "广度优先遍历：" << endl;
    pGraph->widthFirstTraverse(0);
    cout << endl << endl;

    pGraph->resetNode();

    cout << "最小生成树为：" << endl;
    pGraph->MSTPrim(0);
    cout << endl;

    system("pause");
}
