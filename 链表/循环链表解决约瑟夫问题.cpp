#include<iostream>
// ����˼·������һ��ѭ������Ȼ����ָ����λ�ý���ɾ����
// ָ��λ�õ�ȷ����ѭ���ҳ�
using namespace std;

struct node
{
	int number = 0;
	node* next = nullptr;
};
class Josephu
{
private:
	int people_number;
	int step_number;
	node* people;
public:
	Josephu(int people, int step)
	{
		this->people_number = people;
		this->step_number = step;
	}
	void set_Josephu_list()
	{
		people = new node();
		people->number = 1;
		node* temp;
		temp = people;
		for(int i = 1;i<=people_number-1;i++)
		{
			node* create_new = new node();
			create_new->number = i + 1;
			temp->next = create_new;
			temp = temp->next;
		}
		temp->next = people;
	}
	void test_Josephu_list()
	{
		cout << "��ʼ������" << endl;
		node* people_to_kill;
		while (people->next != people)                                                   //while��ѭ������������ȷ���Ƿ�ֻʣ����һ��Ԫ�� 
		{
			for (int i = 1; i < step_number - 1; i++)
			{
				people = people->next;
			}
			people_to_kill = people->next;
			people->next= people_to_kill->next ;
			people_to_kill->next = nullptr;
			people = people->next;
			cout << people_to_kill->number << "->";
			delete[]people_to_kill;
		}
		cout << people->number << endl;
		cout << "���һ���˵ı����" << people->number << endl;
		delete[]people;
	}
};

int main()
{
	int number_of_people = 0;
	int size_of_step = 0;
	
	cout << "��������Josephu��Ϸ������" << endl;
	cin >> number_of_people;
	cout << "�������ȡ��ŵĲ���" << endl;
	cin >> size_of_step;
	Josephu test(number_of_people, size_of_step);
	test.set_Josephu_list();
	test.test_Josephu_list();
	return 0;
}