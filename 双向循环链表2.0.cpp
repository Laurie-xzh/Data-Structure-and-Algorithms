/*�����������100��ϡ�����ʽa��b��ͨ�����������ϵ�����Ҷ���ʽa�Ľ���Ϊ3����������ϵ����0��������ϵ��Ϊ0��
����ʽb�Ľ���Ϊ4����������ϵ����0��������ϵ��Ϊ0��a��b�ֱ���ڴ�ͷ�ڵ��˫��ѭ������A��B�С�
��ʵ�ִ������������ʽϵ���ͣ�Ҫ��ʹ���ԭ����A�У����������Ӵ洢�ռ䣩��
�������㷨�ļ��㸴�Ӷȡ�*/

#include<iostream>
#include <cstdlib>
#include <ctime>


using namespace std;


//����ʽ��ָ��һ��Ϊ����������
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
	* @brief       ��ϵ����ָ����ʼ��һ�¡�0���������ı���
	* @param    i��ָ��
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
	* @brief  ����һ��ϡ�����ʽ
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
		//֮���ÿ�ζ�������n��head֮����롣
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


	//ͬ��
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
		//֮���ÿ�ζ�������n��head֮����롣
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
		cout << "��ʼ��ӡ" << endl;
		ploy* p = this->head;
		while (p->next != this->head)
		{
			if (p->coef != 0)
			{
				cout << p->coef << "  " << "*" << "x��" << p->expn << "�η�" << endl;

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
//���Ӷȣ�O��n1+n2��