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
	* @brief 在最后加一个结点，入队
	* @param data 要插入的数
	*/
	void Add(const double& data)
	{
		Node* n = new Node(data);
		if (head == nullptr)
		{
			head = tail = n;

		}
		else
		{
			tail->next = n;
			tail = n;
		}
		cout << data << "  入队成功" << endl;
	}
	/**
	* @brief 获得链表长度
	* @param
	* @return 返回长度

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
	* @brief  获得结点的指针
	* @param i 下标
	*
	* return 下标对应的结点指针

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
	* @brief 运算符重载，可以用[]来找结点，就像数组一样
	* @param i 下标
	*
	* return 下标对应的结点内容

	*/
	double& operator[](int i)
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
		* @brief 运算符重载，可以用[]来找结点，就像数组一样，这个是只读版
		* @param i 下标
		*
		* return 下标对应的结点内容

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
	* @brief 找到数值为data的结点
	* @param data 要找的数值
	*
	* @return 返回指针就好
	*
	*/
	Node* find(const double& data)
	{
		for (Node* p = head; p; p = p->next)
		{
			if (p->data == data)
			{
				cout << "yep" << endl;
				return p;
			}
		}
		cout << "找不到" << endl;
		return nullptr;
	}

	/**
	* @brief 移除下标为i的结点
	* @param  i 下标

	*/
	bool Remove()//i是第i个
	{		 
		//Node* l = GetNode(i - 1);
		//Node* p = l ? l->next : GetNode(i);
		Node* p = head;
		Node* r = p ? p->next : GetNode(2);

		/*if (!p)
		{
			return false;
		}
		if (l && r)
		{
			l->next = r;
		}*/
		if (p && r)
		{
			head = r;
		}
	/*	if (l && !r)
		{
			tail = l;
			l->next = nullptr;
		}*/
		if ( p&& !r)
		{
			head = tail = nullptr;
		}

		delete p;

		return true;

	}

	/**
	*@brief  在下标为i的结点之后插入数值为data的结点
	* @param data  要插入的数据
	* @param i        下标

	*/
	//void insert(double& data, int& i)
	//{
	//	if (i >= GetCount() || head == nullptr)
	//	{
	//		Add(data);
	//		return;
	//	}
	//	Node* p = new Node(data);

	//	//在头部插入
	//	if (i <= 0)
	//	{
	//		p->next = head;
	//		head = p;
	//	}
	//	else
	//	{
	//		Node* l = GetNode(i);
	//		Node* r = GetNode(i + 1);
	//		l->next = p;
	//		p->next = r;
	//	}



	//}
	//打印
	void print()
	{
		Node* p = head;
		for (p;;)
		{
			if (p)
			{
				cout << p->data << "->";
				p = p->next;
			}
			else
			{
				break;
			}

		}
		cout << endl;
		return;
	}

};


 
int main()
{
	double x1 = 1.5;
	double x2 = 2.0;
	double x3 = 4.9;

	List myList;
	myList.Add(x1);
	myList.Add(x2);
	myList.Add(x3);
	cout << myList.GetCount() << endl;
	myList.print();
	cout << endl;
	
	myList.Remove();
	cout << myList.GetCount() << endl;
	myList.print();
	myList.Remove();
	cout << myList.GetCount() << endl;
	myList.print();
	myList.Remove();
	cout << myList.GetCount() << endl;
	myList.print();
	

 
}

