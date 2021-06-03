
#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;

/*�ڵ���*/
class Node
{
public:
    Node(char identifier = 0);

    char m_identifier;       //������
    bool m_isVisited;        //������ʱ�־λ��true��ʾ�Ѿ�������
};
Node::Node(char identifier)
{
    m_identifier = identifier;
    m_isVisited = false;
}


/*���࣬���ڸ���ʵ��������С������*/
class Edge
{
public:
    Edge(int NodeIndexA = 0, int NodeIndexB = 0, int WeightValue = 0);

    int m_NodeIndexA, m_NodeIndexB;    //�ߵ����˵㣨������������������ͼΪ��
    int m_weightValue;                 //�ߵ�Ȩֵ
    bool m_selected;                   //ѡ���־λ��true��ʾ�ѱ�ѡ��
};
Edge::Edge(int NodeIndexA, int NodeIndexB, int WeightValue)
{
    m_NodeIndexA = NodeIndexA;
    m_NodeIndexB = NodeIndexB;
    m_weightValue = WeightValue;
    m_selected = false;      //��ʼʱδ��ѡ��
}

/*ͼ��*/
class Graph
{
public:
    Graph(int capacity);
    ~Graph();

    int getGraphSize();            //��ȡ��ǰͼ�Ĵ�С
    void resetNode();              //�������ж���ķ��ʱ�־λΪfalse��δ����
    bool addNode(Node* pNode);     //����¶���
    bool addEdgeForUndirectedGraph(int row, int col, int val = 1); //��ӱ��Թ�������ͼ��val��ʾȨֵ��Ĭ��Ȩֵ1
    bool addEdgeForDirectedGraph(int row, int col, int val = 1);   //��ӱ��Թ�������ͼ��val��ʾȨֵ��Ĭ��Ȩֵ1
    void printMatrix();   //��ӡ�ڽӾ���

    void depthFirstTraverse(int nodeIndex);   //������ȱ�����ָ����һ����
    void widthFirstTraverse(int nodeIndex);   //������ȱ�����ָ����һ����

    void MSTPrim(int nodeIndex);        //Prim�㷨����С��������ָ����һ����
    void MSTKruskal();

private:
    bool getValueOfEdge(int row, int col, int& val);  //��ȡ��Ȩֵ
    void widthFirstTraverseImplement(vector<int> preVec);  //����vectorʵ�ֹ�����ȱ���

    int getMinEdge(vector<Edge> edgeVec);  //Prim�㷨���������������ڱ߼���ѡ��Ȩֵ��С�ı�

    int m_iCapacity;     //ͼ�����������������ռ��������ɵĶ������
    int m_iNodeCount;    //ͼ�����ж������
    Node* m_pNodeArray;  //��Ŷ��������
    int* m_pMatrix;      //Ϊ�˷��㣬��һά�������ڽӾ���

    Edge* m_pEgde;       //��ָ�룬�洢��С�������ı�
};
Graph::Graph(int capacity)
{
    m_iCapacity = capacity;
    m_iNodeCount = 0;

    m_pNodeArray = new Node[m_iCapacity];
    m_pMatrix = new int[m_iCapacity * m_iCapacity];

    for (int i = 0; i < m_iCapacity * m_iCapacity; i++)  //��ʼ���ڽӾ���
    {
        m_pMatrix[i] = 0;
    }

    m_pEgde = new Edge[m_iCapacity - 1];    //��С�������ڵ�ͱ�������ϵ
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

    //���ʵ�һ������
    cout << m_pNodeArray[nodeIndex].m_identifier << " ";
    m_pNodeArray[nodeIndex].m_isVisited = true;

    //������������
    for (int i = 0; i < m_iCapacity; i++)
    {
        getValueOfEdge(nodeIndex, i, value);
        if (value != 0)   //��ǰ������ָ��������ͨ
        {
            if (m_pNodeArray[i].m_isVisited == true)  //��ǰ�����ѱ�����
                continue;
            else           //��ǰ����û�б����ʣ���ݹ�
            {
                depthFirstTraverse(i);
            }
        }
        else       //û����ָ��������ͨ
        {
            continue;
        }
    }
}
void Graph::widthFirstTraverse(int nodeIndex)
{
    //���ʵ�һ������
    cout << m_pNodeArray[nodeIndex].m_identifier << " ";
    m_pNodeArray[nodeIndex].m_isVisited = true;

    vector<int> curVec;
    curVec.push_back(nodeIndex);      //����һ���������һ������
    widthFirstTraverseImplement(curVec);
}
void Graph::widthFirstTraverseImplement(vector<int> preVec)
{
    int value = 0;
    vector<int> curVec;    //�������鱣�浱ǰ��Ķ���
    for (int j = 0; j < (int)preVec.size(); j++)  //���η��ʴ��������е�ÿ������
    {
        for (int i = 0; i < m_iCapacity; i++)  //����������еĶ����Ƿ���������������
        {
            getValueOfEdge(preVec[j], i, value);
            if (value != 0)   //��ͨ
            {
                if (m_pNodeArray[i].m_isVisited == true)  //�Ѿ�������
                {
                    continue;
                }
                else   //û�б����������
                {
                    cout << m_pNodeArray[i].m_identifier << " ";
                    m_pNodeArray[i].m_isVisited = true;

                    //���浱ǰ�㵽����
                    curVec.push_back(i);
                }
            }
        }
    }

    if (curVec.size() == 0)   //������ޱ����ʵĵ㣬����ֹ
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
    int value = 0;          //�洢��ǰ�ߵ�Ȩֵ
    int edgeCount = 0;      //��ѡ���ı������������ж��㷨�ս�
    vector<int> nodeVec;    //�洢�㣨��������������
    vector<Edge> edgeVec;   //�洢�ߵ�����

    cout << m_pNodeArray[nodeIndex].m_identifier << endl;

    nodeVec.push_back(nodeIndex);
    m_pNodeArray[nodeIndex].m_isVisited = true;

    while (edgeCount < m_iCapacity - 1)
    {
        int temp = nodeVec.back();           //����ǰ�����������Ƹ�temp
        for (int i = 0; i < m_iCapacity; i++)  //ѭ���ж�ÿһ�������뵱ǰ�����������
        {
            getValueOfEdge(temp, i, value);
            if (value != 0)  //��ͨ
            {
                if (m_pNodeArray[i].m_isVisited == true) //�Ѿ�������
                    continue;
                else //δ������,�򽫱߷��뱻ѡ�߼���
                {
                    Edge edge(temp, i, value);
                    edgeVec.push_back(edge);
                }
            }
        }
        /*ѡ����С��*/
        int edgeIndex = getMinEdge(edgeVec);
        if (edgeIndex == -1)
        {
            cout << "��ȡ��С��ʧ�ܣ������ú����ԣ�" << endl;
            break;
        }

        edgeVec[edgeIndex].m_selected = true;   //����ѡ���־λΪtrue���ѱ�ѡ��

        cout << edgeVec[edgeIndex].m_NodeIndexA << "---" << edgeVec[edgeIndex].m_NodeIndexB << " ";
        cout << edgeVec[edgeIndex].m_weightValue << endl;

        m_pEgde[edgeCount] = edgeVec[edgeIndex];
        edgeCount++;

        /*Ѱ�ҵ�ǰѡ�����С����������һ������*/
        int nextNodeIndex = edgeVec[edgeIndex].m_NodeIndexB;
        nodeVec.push_back(nextNodeIndex);
        m_pNodeArray[nextNodeIndex].m_isVisited = true;

        cout << m_pNodeArray[nextNodeIndex].m_identifier << endl;
    }
    cout << "��С������������ϣ�������ʾ��" << endl;
}
void Graph::MSTKruskal()
{

}
int Graph::getMinEdge(vector<Edge> edgeVec)
{
    int minWeight = 0;   //���ڸ���ѡ����СȨֵ��
    int edgeIndex = 0;   //���ڴ洢��С������
    int i = 0;

    /*�ҳ���һ��δ��ѡ��ı�*/
    for (; i < (int)edgeVec.size(); i++)
    {
        if (edgeVec[i].m_selected == false)  //��ǰ��δ��ѡ��
        {
            minWeight = edgeVec[i].m_weightValue;
            edgeIndex = i;
            break;
        }
    }

    if (minWeight == 0)   //�߼����б߱�����
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

    cout << "��ʼ�������С���" << endl;
    Node* pNodeA = new Node('A');
    Node* pNodeB = new Node('B');
    Node* pNodeC = new Node('C');
    Node* pNodeD = new Node('D');
    Node* pNodeE = new Node('E');
    Node* pNodeF = new Node('F');

    cout << "��Ӷ�����ͼ�С���" << endl;
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


    cout << "�ڽӾ�������:" << endl;
    pGraph->printMatrix();
    cout << endl << endl;

    cout << "������ȱ�����" << endl;
    pGraph->depthFirstTraverse(0);
    cout << endl << endl;

    pGraph->resetNode();

    cout << "������ȱ�����" << endl;
    pGraph->widthFirstTraverse(0);
    cout << endl << endl;

    pGraph->resetNode();

    cout << "��С������Ϊ��" << endl;
    pGraph->MSTPrim(0);
    cout << endl;

    system("pause");
}
