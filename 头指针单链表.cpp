#include<iostream>

using namespace std;
//template<typename T>
class Node
{
	double data;
	Node* next;

public:
	Node(const double& data)
	{
		this->data = data;
		next = nullptr;
	}


	//template<typename TT>
	friend class List;
};

//template<typename T>
class List
{
	Node* head = nullptr;
	Node* tail = nullptr;

public:
	/**
	* @brief ������һ�����
	* @param data Ҫ�������
	*/
	void Add(const double &data)
	{
		Node* n = new Node(data);
		if (head == nullptr)
		{
			head =tail= n;
			 
		}
		else
		{
			tail->next = n;
			tail = n;
		}
		 
	}
	/**
	* @brief ���������
	* @param 
	* @return ���س���
	
	*/
	int GetCount()
	{
		int c = 0;
		for (Node* p = head; p; p = p->next)
		{
			c++;
		}
		return c;
	}
	/**
	* @brief  ��ý���ָ��
	* @param i �±�
	*
	* return �±��Ӧ�Ľ��ָ��

	*/
	Node* GetNode(int i)
	{
		int c = 0;
		for (Node* p = head; p; p = p->next)
		{
			if (i == c)
			{
				return p;
			}
			c++;
			
		}
		return nullptr;
	}
	/**
	* @brief ��������أ�������[]���ҽ�㣬��������һ��
	* @param i �±�
	* 
	* return �±��Ӧ�Ľ������
	
	*/
double & operator[](int i)
	{
		int c = 0;
		for (Node* p = head; p; p = p->next)
		{
			if (i == c)
			{
				return p->data;
			}
			c++;

		}

	}
/**
	* @brief ��������أ�������[]���ҽ�㣬��������һ���������ֻ����
	* @param i �±�
	*
	* return �±��Ӧ�Ľ������

	*/
const double& operator[](int i)const
{
	int c = 0;
	for (Node* p = head; p; p = p->next)
	{
		if (i == c)
		{
			return p->data;
		}
		c++;

	}

}
/**
* @brief �ҵ���ֵΪdata�Ľ��
* @param data Ҫ�ҵ���ֵ
* 
* @return ����ָ��ͺ�
* 
*/
Node* find(const double& data)
{
	for (Node* p = head; p; p = p->next)
	{
		if (p->data == data)
		{
			cout << "yep" << endl;
			return p ;
		}
	}
	cout << "�Ҳ���" << endl;
	return nullptr;
}

/**
* @brief �Ƴ��±�Ϊi�Ľ��
* @param  i �±�

*/
bool Remove(int i)//i�ǵ�i��
{
	//����һ
	/*Node* l = GetNode(i - 1);
	Node* p = GetNode(i);
	Node* r = GetNode(i + 1);*/

	//������
	Node* l = GetNode(i - 1);
	Node* p = l ? l->next : GetNode(i);
	Node* r= p ? p->next : GetNode(i+1);

	if (!p)
	{
		return false;
	}
	if (l && r)
	{
		l->next = r;
	}
	if (!l && r)
	{
		head = r;
	}
	if (l && !r)
	{
		tail = l;
		l->next = nullptr;
	}
	if (!l && !r)
	{
		head = tail = nullptr;
	}

	delete p;

	return true;

}

/**
*@brief  ���±�Ϊi�Ľ��֮�������ֵΪdata�Ľ��
* @param data  Ҫ���������
* @param i        �±�

*/
void insert(double& data, int &i)
{
	if (i >= GetCount() || head == nullptr)
	{
		Add(data);
		return;
	}
	Node* p = new Node(data);

	//��ͷ������
	if (i <= 0)
	{
		p->next = head;
		head = p;
	}
	else
	{
		Node* l = GetNode(i);
		Node* r = GetNode(i + 1);
		l->next = p;
		p->next = r;
	}



}
//��ӡ
void print()
{
	Node* p = head;
	for (p;;)
	{
		if(p)
		{
			cout << p->data << "->";
			p = p->next;
		}
		else
		{
			break;
		}
	
	}
	return;
}

};

 
//ListNode* deleteNode(ListNode* head, int val)
//{
//    ListNode* p = head;
//    int j = 0;
//    while ((p->next) && (j < val - 1))
//    {
//        p = p->next;
//        j = j + 1;
//    }
//    if ((!p->next) || j > val - 1)
//    {
//        return NULL;
//    }
//    ListNode* q = p->next;
//    p->next = q->next;
//    delete q;
//    return head;
//
//}
int main()
{
	double x1 = 1.5;
	double x2 = 2.0;
	double x3 = 4.9;

	List myList;
	myList.Add(x1);
	myList.Add(x2);
	myList.Add(x3);
	cout << myList.GetCount()<< endl;
	cout << myList[2] << endl;
	myList.find(2.0);
	myList.find(3);
	myList.print();
	cout << endl;

	double x4 = 666;
	int i = 1;
	myList.insert(x4, i);
	cout<<myList.GetCount()<<endl;
	myList.print();
	cout << endl;
	myList.Remove(i);
	cout<<myList.GetCount()<<endl;
	myList.print();
}