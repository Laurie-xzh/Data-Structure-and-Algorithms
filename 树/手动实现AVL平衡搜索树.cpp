#include<iostream>
#include<iomanip>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
 #include<vector>
#include<algorithm>
#include<string>
#include<stack>
#include<queue>
#include<algorithm>
#define LH +1
#define EH 0
#define RH -1
using namespace std;

//template<class T>
//class AVLtreeNode
//{
//	T key;
//	int height;
//	AVLtreeNode* leftchild;
//	AVLtreeNode* rightchild;
//
//	AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r) :
//		key(value), height(0), left(l), right(r) {}
//};
//
//template<class T>
//class AVLtree
//{
//private:
//	AVLtreeNode<T>* root;
//
//public:
//	AVLtree();
//	~AVLtree();
//
//	// 获取树的高度
//	int height();
//	// 获取树的高度
//	int max(int a, int b);
//
//
//	// (递归实现)查找"AVL树"中键值为key的节点
//	AVLTreeNode<T>* search(T key);
//
//	//生成一个AVL
//	 // 将结点(key为节点键值)插入到AVL树中
//	void insert(T key);
//
//	// 删除结点(key为节点键值)
//	void remove(T key);
//
//	// 销毁AVL树
//	void destroy();
//
//	// 打印AVL树
//	void print();
//	 
//};
//
//template <class T>
//AVLtree<T>::AVLtree()
//{
//	root = NULL;
//}
//
//template <class T>
//AVLtree<T>::~AVLtree()
//{
//	destroy(root);
//}
//template<class T>
//AVLtreeNode<T>* AVLtree<T>::search(T key)
//{
//	return search(mRoot, key);
//}
struct AVLTreeNode
{
	int val = 25;
	int bf;
	AVLTreeNode* leftchild = nullptr;
	AVLTreeNode* rightchild = nullptr;

	AVLTreeNode(int a):val(a),leftchild(nullptr),rightchild(nullptr){}
 };
int arr_save[50] = { 0 };
int k = 0;
void PrintAVLTree(AVLTreeNode*&root)
{
	
	if (root == NULL)
	{
		return;
	}
	
	cout << "树："<<root->val<<"  ";
	arr_save[k] = root->val;
	cout <<"arr: "<<arr_save[k] << endl;
	k = k + 1;
	PrintAVLTree(root->leftchild);
	PrintAVLTree(root->rightchild);
}
void PrintAVLTree_1(AVLTreeNode*& root)
{

	if (root == NULL)
	{
		return;
	}
	 
	cout << root->val << endl;
	PrintAVLTree_1(root->leftchild);
	PrintAVLTree_1(root->rightchild);
}
//右旋转
void Right_Rotation(AVLTreeNode*& root) 
{
	AVLTreeNode* Left = root->leftchild;
	root->leftchild = Left->rightchild;
	Left->rightchild = root;
	root = Left;
}
//左旋转
void Left_Rotation(AVLTreeNode*& root)
{
	AVLTreeNode* Right = root->rightchild;
	root->rightchild = Right->leftchild;
	Right->leftchild = root;
	root = Right;
}
//左平衡
void LeftBalance(AVLTreeNode*& root)
{
	AVLTreeNode* L=root->leftchild;
	switch (L->bf)
	{
	case LH:
		root->bf = L->bf = EH;
		Right_Rotation(root);
		break;
	case RH:
		AVLTreeNode* Lr = L->rightchild;
		switch (Lr->bf)
		{
		case LH:
			root->bf = RH;
			L->bf     = EH;
			break;
		case EH:
			L->bf = root->bf = EH;
			break;
		case RH:
			L->bf     = LH;
			root->bf = EH;
			break;
		}
		Lr->bf = EH;
		Left_Rotation(L);
		root->leftchild = L;
		Right_Rotation(root);
		break;
	}
}
//右平衡
void RightBalance(AVLTreeNode*& root) {
	AVLTreeNode* R = root->rightchild;
	switch (R->bf) {
	case RH:
		root->bf = R->bf = EH;
		Left_Rotation(root);
		break;
	case LH:
		AVLTreeNode* Rl = R->leftchild;
		switch (Rl->bf) {
		case LH:
			root->bf = EH;
			R->bf = RH;
			break;
		case EH:
			root->bf = R->bf = EH;
			break;
		case RH:
			root->bf = LH;
			R->bf = EH;
			break;
		}
		Rl->bf = EH;
		Right_Rotation(R);
		root->rightchild = R;
		Left_Rotation(root);
	}
}
//插入
//taller:判断插入之后是不是使树的高度增大，从而需要进行平衡
bool InsertAVL(AVLTreeNode*&root, int e, bool & taller)
{
	if (!root)
	{
		root = new AVLTreeNode(e);
		root->bf = EH;
		taller = true;
	}

	else
	{
		if (e == root->val)
		{
			taller = false;
			cout << "已经有啦" << endl;
			return false;
		}
		else if (e > root->bf)
		{
			if (!InsertAVL(root->rightchild, e, taller))
			{
				return false;
			}
			if (taller)
			{
				switch (root->bf)
				{
				case EH:
					root->bf = RH;
					taller = true;
					break;
				case RH:
					RightBalance(root);
					taller = false;
					break;
				case LH:
					root->bf = EH;
					taller = false;
					break;
				}
			}
		}
		else if (e < root->val) {
			if (!InsertAVL(root->leftchild, e, taller))
				return false;
			if (taller) {
				switch (root->bf) {
				case EH:
					root->bf = LH;
					taller = true;
					break;
				case LH:
					LeftBalance(root);
					taller = false;
					break;
				case RH:
					root->bf = EH;
					taller = false;
					break;
				}
			}
		}
	}
	return true;
}

//删除
bool DeleteAVLNode(AVLTreeNode*& root, int key, bool& shorter) {
	if (root == nullptr)
		return false;
	else if (key == root->val) {
		AVLTreeNode* tmp = nullptr;
		if (!root->leftchild) {
			tmp = root;
			root = root->rightchild;
			shorter = true;
			delete tmp;
		}
		else if (!root->rightchild) {
			tmp = root;
			root = root->leftchild;
			shorter = true;
			delete tmp;
		}
		else {
			tmp = root->leftchild;
			while (tmp->rightchild)
				tmp = tmp->rightchild;
			root->val = tmp->val;
			DeleteAVLNode(root->leftchild, root->val, shorter);
		}
	}
	else if (key < root->val) {
		if (!DeleteAVLNode(root->leftchild, key, shorter))
			return false;
		if (shorter) {
			switch (root->bf) {
			case LH:
				root->bf = EH;
				shorter = true;
				break;
			case EH:
				root->bf = RH;
				shorter = false;
				break;
			case RH:
				if (root->rightchild->bf == EH) {
					shorter = false;
				}
				else   shorter = true;
				RightBalance(root);
				break;
			}
		}
	}
	else
	{
		if (!DeleteAVLNode(root->rightchild, key, shorter))
			return false;
		if (shorter) {
			switch (root->bf)
			{
			case LH:
				if (root->leftchild->bf == EH) {
					shorter = false;
				}
				else shorter = true;
				LeftBalance(root);
				break;
			case EH:
				root->bf = LH;
				shorter = false;
				break;
			case RH:
				root->bf = EH;
				shorter = true;
				break;
			}
		}

	}
	return true;
}
void init(AVLTreeNode*& root)
{
	 
	 
	bool judge = true;
	srand(time(0));
	int arr[50] = { 0 };
	int i = 0;
	for (i; i <= 49; i++)
	{
		arr[i] = rand()%100 +rand()%10+1;
		cout << arr[i] << "  ";
		
	}
	for (int j = 0; j <= 49; j++)
	{
		bool x =InsertAVL(root, arr[j], judge);
	}
	cout << endl;
	 
	
}

int main()
{
	bool judge_delete = true;
	bool delete_whether_successful = true;
	AVLTreeNode* root = NULL;
	
	int x = 25;

	init(root);
	cout << "---------下面把树打印出来--------" << endl;
	PrintAVLTree(root);
	delete_whether_successful = DeleteAVLNode(root, x, judge_delete);
 
	cout << "---------下面把树打印出来--------" << endl;
	PrintAVLTree_1(root);


	//cout << "makabakamakabaka" << endl;
	///*for (int i = 0; i <= 49; i++)
	//{
	//	cout << arr_save[i] << endl;
	//}*/
	//cout << endl;
	//int arr_target[50] = { 0 };
	//for (int m = 0; m <= 49; m++)
	//{
	//	arr_target[m] = arr_save[49 - m];
	//}
	///*for (int n = 0; n <= 49; n++)
	//{
	//	cout << arr_target[n] << endl;
	//}*/
	//for (int x = 0; x <= 49; x++)
	//{
	//	if (arr_target[x] != 0)
	//	{
	//		cout << arr_target[x]<<endl;
	//		bool judge =DeleteAVLNode(root, arr_target[x], judge_delete);

	//		PrintAVLTree_1(root);
	//		cout << "-------------------------------------------------" << endl;
	//	}
	//}
	return 0;
}