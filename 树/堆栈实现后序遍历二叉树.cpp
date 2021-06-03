#include<iostream>
#include<stack>
//这里没有新定义stack类，而是用了已经给的stack类,而把标记放在了函数里
 
using namespace std;

typedef struct BiTNode
{
	int data;
	BiTNode()
	{}
	 BiTNode* lchild, * rchild;
	BiTNode(int x)
	{
		data = x;
		lchild = NULL;
		rchild = NULL;
	}
}  *BiTree;

 

BiTree createTree(int *arr,int& index,int &size)
{
	BiTNode* p = NULL;
	  
	//size = sizeof(arr) / sizeof(arr[0]);
	// size = 19;
	if (index< size && arr[index]!='#')
	{
		p = new BiTNode(arr[index]);
		p->lchild = createTree(arr, ++index, size );
		p->rchild = createTree(arr, ++index, size );
	}
	return p;
}

void PastOrderTraverse(BiTree root)
{
	BiTree current = root;
	BiTree last = NULL;
	stack<BiTree> s;

	while (current || !s.empty())
	{
		while (current)
		{
			s.push(current);
			current = current->lchild;
		}
		current = s.top();
		if(current->rchild && last != current->rchild)
		{
			current = current->rchild;
		}
		else if (!current->rchild || last == current->rchild)
		{
			cout << current->data <<"->";
			last = current;
			s.pop();
			current = NULL;//这里设为NULL，在进入新一轮while后，可以直接从top元素开始
		}
	}
	cout << "over" << endl;
}

int main()
{
	int arr[] = { 9, 3, 5, 10, '#', '#', 6, 15, '#', '#', 7,'#', '#', '#', 8, 3, '#', '#', 9 };
	int i = 0;
	int size = sizeof(arr) / sizeof(arr[0]);
	BiTNode *x = createTree(arr, i, size);
	PastOrderTraverse(x);
	return 0;

}