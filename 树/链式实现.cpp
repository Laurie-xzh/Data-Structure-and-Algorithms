#include<iostream>
#include<stack>

#define  TElemType int
#define Status int
using namespace std;
//
//typedef struct BiTNode
//{
//	TElemType data;
//	struct BiTNode* lchild, * rchild;
//}BiTNode,*BiTree;
//
//struct stkNode
//{
//	BiTNode* ptr;
//	enum tag {L,R};
//	stkNode(BiTNode* N = NULL) :
//		ptr(N), tag(L) {}
//};


typedef struct Node
{
	int _data;
	Node* _right;
	Node* _left;
	Node()
	{}
	Node(int x)
	{
		_data = x;
		_left = NULL;
		_right = NULL;
	}
}*pNode;


pNode createTree(const int* arr, size_t& index, const size_t size, int invalid)
{ 
	Node* root = NULL; 
	if (index < size && arr[index] != invalid) 
	{ 
		root = new Node(arr[index]);
		root->_left = createTree (arr, ++index, size, invalid); 
		root->_right = createTree (arr, ++index, size, invalid); 
	}
	return root;
}
 void pastOrder_NR(pNode root)
{
	if (NULL == root)
		cout << "empty" << endl;

	pNode cur = root;
	pNode last = NULL;
	stack<pNode> s;

	while (cur || !s.empty())
	{
		while (cur)//ѹ�����������
		{
			s.push(cur);
			cur = cur->_left;
		}

		cur = s.top();

		if (cur->_right && last != cur->_right)//����ջ��������������㡣������û�����ʹ��������������ѹ��ջ��
		{
			cur = cur->_right;
		}
		else if ((NULL == cur->_right) || (last == cur->_right))
			//���������Ϊ�ջ����Ѿ������ʹ��������ջ����㲢����
		{
			cout << cur->_data << "->";
			last = cur;//����lastֵ
			s.pop();
			//cur�ÿ��������ڵ�ԭջ����㱻���ʲ���������һ��while�ǽ���ǰջ��������������ջ����ǰջ�������������Ѿ�����������		
			//��˻������ѭ�������Խ�cur�ÿգ�ֱ�ӿ��ǵ�ǰջ������������            
			//һ��ĳ�������ջ�����Ȼ�������������������Ȼ���������������
			cur = NULL;
		}
	}cout << "over" << endl;
}

void test()
{
	int arr[] = { 1, 2, 4, 10, '#', '#', 6, 11, '#', '#', 7,'#', '#', '#', 3, 8, '#', '#', 9 };
	size_t index = 0;
	pNode root = createTree (arr, index, sizeof(arr) / sizeof(arr[0]), '#');

	 
	cout << "pastOrder_NR:";
	pastOrder_NR(root);
	 
	cout << endl;
}

//int main()
//{
//	test();
//	return 0;
//}
