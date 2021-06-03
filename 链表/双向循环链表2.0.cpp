/*随机生成两个100阶稀疏多项式a和b，通过随机数生成系数，且多项式a的阶数为3的整数倍项系数非0，其它项系数为0，
多项式b的阶数为4的整数倍项系数非0，其它项系数为0，a、b分别存于带头节点的双向循环链表A、B中。
现实现代码计算两多项式系数和，要求和存于原链表A中（不额外增加存储空间）。
评估该算法的计算复杂度。*/

#include<iostream>
#include <cstdlib>
#include <ctime>


using namespace std;


//多项式的指数一定为非零整数！
class ploy
{
public:
	double coef;
	int  expn;
	ploy* next;
	ploy* prior;



	ploy()
	{

		this->next = nullptr;
		this->prior = nullptr;
	}
	/**
	* @brief       把系数和指数初始化一下。0是所有数的倍数
	* @param    i是指数
	*
	* @return
	*/
	void init_CoefandExpn(int& i)
	{

		if (i == 1)
		{
			this->coef = 0;
			this->expn = i;
		}
		else
		{
			this->coef = rand() % 100;
			this->expn = i;
		}


	}


};



class List
{
private:
	ploy* head = new ploy;
	int length = 0;


public:


	void print_list()
	{

		ploy* x = this->head;
		while (x->next != head)
		{
			cout << x->coef << endl;
			x = x->next;
		}
	}

	/**
	* @brief  创造一个稀疏多项式
	*/
	void init_a()
	{
		int i = 0;
		head->init_CoefandExpn(i);


		ploy* n = new ploy;

		n->prior = head;
		head->next = n;
		n->next = head;
		head->prior = n;
		i = i + 1;
		n->init_CoefandExpn(i);
		ploy* tail = n;
		//之后就每次都可以在n和head之间插入。
		while(i<=100)
		{
			i = i + 1;
			
		
			if ((i % 3) == 0)
			{
				ploy* p = new ploy;
				p->init_CoefandExpn(i);

				cout << p->coef << "   " << i << endl;
				p->prior = tail;

				p->next = head;
				tail->next = p;
				head->prior = p;

				tail = p;
			}
			 

			



		}
		cout << "finished" << endl;
	}


	//同上
	void init_b()
	{
		int i = 0;
		head->init_CoefandExpn(i);


		ploy* n = new ploy;

		n->prior = head;
		head->next = n;
		n->next = head;
		head->prior = n;
		i = i + 1;
		n->init_CoefandExpn(i);
		ploy* tail = n;
		//之后就每次都可以在n和head之间插入。
		while (i <= 100)
		{
			i = i + 1;


			if ((i % 4) == 0)
			{
				ploy* p = new ploy;
				p->init_CoefandExpn(i);

				cout << p->coef << "   " << i << endl;
				p->prior = tail;

				p->next = head;
				tail->next = p;
				head->prior = p;

				tail = p;
			}






		}
		cout << "finished" << endl;
	}


	List plus(List& B)
	{

		cout << "begin" << endl;


		ploy* p = this->head;
		ploy* q = B.head;
		while (p->next != this->head && q->next != B.head)
		{
			//cout << p->coef << "+" << q->coef << endl;
			
			while (p->expn < q->expn)
			 {
				p = p->next;
			 }
			while (p->expn > q->expn)
			{
				q = q->next;
			}
			while (p->expn<q->expn && (p->next->expn)>q->expn)
			{
				q->next = p->next;
				q->prior = p;
				
			}
			if (p->expn == q->expn)
			{
				p->coef = p->coef + q->coef;
				p = p->next;
				q = q->next;
			}
			if (p->next == head)
			{

			}

		}
		return *this;
	}

	void print()
	{
		cout << "开始打印" << endl;
		ploy* p = this->head;
		while (p->next != this->head)
		{
			if (p->coef != 0)
			{
				cout << p->coef << "  " << "*" << "x的" << p->expn << "次方" << endl;

			}
			p = p->next;
		}
	}


};

void Add(List& A, List& B)
{
	List* p1 = &A;
	List* p2 = &B;
	List* p3 = &A;

 

}
int main()
{
	srand(time(0));
	List a;

	List b;
	a.init_a();
	a.print();

	b.init_b();
	b.print();

	a.plus(b);
	a.print();
	return 0;
}
//复杂度：O（n1+n2）