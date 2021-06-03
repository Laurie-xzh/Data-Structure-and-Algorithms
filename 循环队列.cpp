//ѭ������
#include<iostream>
#define MAXQSIZE 100
using namespace std;

typedef struct
{
	double* base;
	int head;
	int tail;
}Queue;

void init(Queue& s)
{
	s.base = new double[MAXQSIZE];
	if (!s.base)
	{
		exit;
	}
	s.head = s.tail=0;
	cout << "��ʼ���ɹ�" << endl;
}

int Length_Queue(Queue& s)
{
	return (s.tail - s.head + MAXQSIZE) % MAXQSIZE;
}

void put_in(Queue& s, double new_element)
{
	if (((s.tail + 1) % MAXQSIZE) == s.head)
	{
		cout << "�����Ѿ�����" << endl;
		exit;
	}
	s.base[s.tail] = new_element;
	s.tail = (s.tail + 1) % MAXQSIZE;
	cout <<new_element<< "��ӳɹ�" << endl;
}

void go_out(Queue& s,double &element_out)
{
	if (s.head == s.tail)
	{
		cout << "�Ѿ�����" << endl;
		exit;
	}
	element_out = s.base[s.head];
	s.head = (s.head + 1) % MAXQSIZE;
	cout << element_out << "   ��ȥ��" << endl;
}

double get_head(Queue& s)
{
	if (s.head != s.tail)
	{
		return s.base[s.head];
	}
}

int main()
{
	double arr[5] = { 1,2,3,4,5 };
	double e = 0;
	Queue s;
	init(s);
	put_in(s, arr[0]);
	Length_Queue(s);
	put_in(s, arr[1]);
	Length_Queue(s);
	put_in(s, arr[2]);
	Length_Queue(s);
	put_in(s, arr[3]);
	Length_Queue(s);
	put_in(s, arr[4]);
	Length_Queue(s);

	go_out(s, e);
	Length_Queue(s);
	go_out(s, e);
	Length_Queue(s);
	go_out(s, e);
	Length_Queue(s);
	go_out(s, e);
	Length_Queue(s);
	go_out(s, e);
	Length_Queue(s);
	return 0;


}


