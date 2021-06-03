#include<iostream>
#define MAXSIZE 100
using namespace std;
//�涨1Ϊtrue , 0Ϊfalse
typedef struct
{
	double* top;
	double* base;
	int stacksize;
}Sqstack;

void Init(Sqstack& s)
{
	s.base = new double[MAXSIZE];
	if (!s.base)
	{
		cout << "ERROR" << endl;
	}
	s.top = s.base;
	s.stacksize = MAXSIZE;
	cout << "��ʼ���ɹ�" << endl;
}

void Push(Sqstack& s,double new_element)
{
	if ((s.top - s.base) == MAXSIZE)
	{
		cout << "ջ����-_-"<<endl;
		 
	}
	*s.top = new_element;
	s.top = s.top + 1;
	cout << "ѹջ�ɹ�" << endl;
	
}
void Pop(Sqstack& s)
{
	if (s.base == s.top)
	{
		cout << "�Ѿ�����" << endl;
		 
	}
	--s.top;
	 
}
double Get_topElement(Sqstack s)
{
	if (s.base != s.top)
	{
		return *(s.top - 1);
	}
}

int main()
{
	double arr[5] = { 1.1,2.2,3.3,4.4,5.5 };
	Sqstack s;
	Init(s);
	Push(s, arr[0]);
	Push(s, arr[1]);
	Push(s, arr[2]);
	Push(s, arr[3]);
	Push(s, arr[4]);
	cout << Get_topElement(s) << endl;
	Pop(s);
	cout << Get_topElement(s) << endl;
	Pop(s);
	cout << Get_topElement(s) << endl;
	Pop(s);
	cout << Get_topElement(s) << endl;
	Pop(s);
	cout << Get_topElement(s) << endl;
	return 0;
}	

