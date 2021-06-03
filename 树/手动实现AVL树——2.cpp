
#include<iostream>
#include<cstdlib>
#include<ctime>
 
using namespace std;
typedef struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
}BTNode;

int height(struct Node* N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

BTNode* newNode(int key)
{
    struct Node* node = (BTNode*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

BTNode* ll_rotate(BTNode* y)
{
    BTNode* x = y->left;
    y->left = x->right;
    x->right = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

BTNode* rr_rotate(BTNode* y)
{
    BTNode* x = y->right;
    y->right = x->left;
    x->left = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

int getBalance(BTNode* N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
//���뺯������������һ����
//insert��������Ҫ������balance����ƽ������
BTNode* insert(BTNode* node, int key)
{

    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    
    int balance = getBalance(node);



    if (balance > 1 && key < node->left->key) //LL��
        return ll_rotate(node);


    if (balance < -1 && key > node->right->key)     //RR��
        return rr_rotate(node);


    if (balance > 1 && key > node->left->key)     //LR��
    {
        node->left = rr_rotate(node->left);
        return ll_rotate(node);
    }

    if (balance < -1 && key < node->right->key)     //RL��
    {
        node->right = ll_rotate(node->right);
        return rr_rotate(node);
    }

    return node;
}

//����delete�е�һ����������
BTNode* minValueNode(BTNode* node)
{
    BTNode* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

BTNode* deleteNode(BTNode* root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            BTNode* temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            BTNode* temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }


    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);


    if (balance > 1 && getBalance(root->left) >= 0) //LL��
        return ll_rotate(root);


    if (balance > 1 && getBalance(root->left) < 0) //LR��
    {
        root->left = rr_rotate(root->left);
        return ll_rotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) //RR��
        return rr_rotate(root);

    if (balance < -1 && getBalance(root->right) > 0)  //Rl��
    {
        root->right = ll_rotate(root->right);
        return rr_rotate(root);
    }

    return root;
}

int arr_save[100] = { 0 };
int k = 0;
//������������������arr_save����
void preOrder1(struct Node* root)
{
    if (root != NULL)
    {
        arr_save[k] = root->key;
        cout << root->key;
      //  printf("%d ", root->key);
        cout <<"  (" <<arr_save[k]<<") ";

       
        k = k + 1;
        preOrder1(root->left);
        preOrder1(root->right);
    }
    
}

void preOrder(struct Node* root)
{
    if (root != NULL)
    {
        
        cout << root->key;
 
 
        preOrder(root->left);
        preOrder(root->right);
    }
    
}
int main()
{
    BTNode* root = NULL;
    srand(time(0));
    int arr1[100] = {0};
    for (int i = 0; i <= 99; i++)
    {
        arr1[i] = rand() % 100 + 1;
    }
    for (int i = 0; i <= 99; i++)
    {
        root = insert(root, arr1[i]);
    }
     
    cout<<"ǰ�������"<<endl;
    preOrder1(root);
   
    int arr_target[100] = { 0 };
    for (int m = 0; m <=99; m++)
    {
    	arr_target[m] = arr_save[99 - m];
        //cout << arr_target[m] <<"  ";
    }

    cout << endl;
    preOrder(root);
    cout << endl;
    
    for (int m = 0; m <= 99; m++)
    {
        if (arr_target[m] != 0)
        {
            cout << arr_target[m] << endl;
            root = deleteNode(root, arr_target[m]);
            preOrder(root);
            cout << endl;
        }
        
    }
  
    cout<<endl;
    cout<<"ǰ�����"<<endl;
    preOrder(root);
    return 0;
}