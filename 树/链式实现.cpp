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
		while (cur)//压入左子树结点
		{
			s.push(cur);
			cur = cur->_left;
		}

		cur = s.top();

		if (cur->_right && last != cur->_right)//考虑栈顶结点的右子树结点。存在且没被访问过，将右子树结点压入栈中
		{
			cur = cur->_right;
		}
		else if ((NULL == cur->_right) || (last == cur->_right))
			//右子树结点为空或者已经被访问过，则访问栈顶结点并弹出
		{
			cout << cur->_data << "->";
			last = cur;//更新last值
			s.pop();
			//cur置空作用在于当原栈顶结点被访问并弹出后，下一层while是将当前栈顶结点的左子树入栈，当前栈顶结点的左子树已经被遍历过，		
			//因此会造成死循环，所以将cur置空，直接考虑当前栈顶结点的右子树            
			//一旦某个结点入栈，首先会遍历这个结点的左子树，然后考虑右子树的情况
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
