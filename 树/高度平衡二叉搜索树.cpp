#include <iostream>
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
struct AVLTreeNode {
	int val;				//�ڵ�ֵ
	int bf;				//�ڵ��ƽ������ֵ
	struct AVLTreeNode* left;
	struct AVLTreeNode* right;
	AVLTreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
};
void PrintAVLTree(AVLTreeNode*& root) {
	if (root == nullptr)
		return;
	cout << root->val << " ";
	PrintAVLTree(root->left);
	PrintAVLTree(root->right);
}
//����ת
void Right_Rotation(AVLTreeNode*& root) {
	AVLTreeNode* Left = root->left;
	root->left = Left->right;
	Left->right = root;
	root = Left;
}
//����ת
void Left_Rotation(AVLTreeNode*& root) {
	AVLTreeNode* Right = root->right;
	root->right = Right->left;
	Right->left = root;
	root = Right;
}
//��ƽ��
void LeftBalance(AVLTreeNode*& root) {
	AVLTreeNode* L = root->left;
	switch (L->bf) {
	case LH:
		root->bf = L->bf = EH;
		Right_Rotation(root);
		break;
	case RH:
		AVLTreeNode* Lr = L->right;
		switch (Lr->bf)
		{
		case LH:
			root->bf = RH;
			L->bf = EH;
			break;
		case EH:
			L->bf = root->bf = EH;
			break;
		case RH:
			L->bf = LH;
			root->bf = EH;
			break;
		}
		Lr->bf = EH;
		Left_Rotation(L);
		root->left = L;
		Right_Rotation(root);
		break;
	}
}
//��ƽ��
void RightBalance(AVLTreeNode*& root) {
	AVLTreeNode* R = root->right;
	switch (R->bf) {
	case RH:
		root->bf = R->bf = EH;
		Left_Rotation(root);
		break;
	case LH:
		AVLTreeNode* Rl = R->left;
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
		root->right = R;
		Left_Rotation(root);
	}
}
//��������
bool InsertAVL(AVLTreeNode*& root, int e, bool& taller) {
	if (!root)
	{	 //���ڵ�Ϊ�ջ����Ѿ��ݹ鵽Ҷ�ڵ���ӽڵ�
		root = new AVLTreeNode(e);
		root->bf = EH;
		taller = true;
	}
	else {
		if (e == root->val) {
			taller = false;
			return false;
		}
		else if (e > root->val) {
			if (!InsertAVL(root->right, e, taller))
				return false;
			if (taller) {
				switch (root->bf) {
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
			if (!InsertAVL(root->left, e, taller))
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
//taller ���ڼ�¼�����½ڵ���Ƿ�ʹ��Ӧ�������߶����ӣ��Ӷ�����ƽ�������ж��Ƿ���Ҫ��������ƽ��
//ɾ���ڵ�
bool DeleteAVLNode(AVLTreeNode*& root, int key, bool& shorter) {
	if (root == nullptr)
		return false;
	else if (key == root->val) {
		AVLTreeNode* tmp = nullptr;
		if (!root->left) {
			tmp = root;
			root = root->right;
			shorter = true;
			delete tmp;
		}
		else if (!root->right) {
			tmp = root;
			root = root->left;
			shorter = true;
			delete tmp;
		}
		else {
			tmp = root->left;
			while (tmp->right)
				tmp = tmp->right;
			root->val = tmp->val;
			DeleteAVLNode(root->left, root->val, shorter);
		}
	}
	else if (key < root->val) {
		if (!DeleteAVLNode(root->left, key, shorter))
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
				if (root->right->bf == EH) {
					shorter = false;
				}
				else   shorter = true;
				RightBalance(root);
				break;
			}
		}


	}
	else {
		if (!DeleteAVLNode(root->right, key, shorter))
			return false;
		if (shorter) {
			switch (root->bf)
			{
			case LH:
				if (root->left->bf == EH) {
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
//����߶�
int CalculateHeight(AVLTreeNode* root) {
	if (!root)
		return 0;
	int LeftHeight = CalculateHeight(root->left);
	int RightHeight = CalculateHeight(root->right);
	return LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;
}
