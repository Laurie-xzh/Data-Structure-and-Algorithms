#include<iostream>
// 大致思路：构造一个循环链表，然后在指定的位置将其删除。
// 指定位置的确定由循环找出
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
		cout << "开始报数！" << endl;
		node* people_to_kill;
		while (people->next != people)                                                   //while的循环条件是用来确定是否只剩下了一个元素 
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
		cout << "最后一个人的编号是" << people->number << endl;
		delete[]people;
	}
};

int main()
{
	int number_of_people = 0;
	int size_of_step = 0;
	
	cout << "请输入玩Josephu游戏的人数" << endl;
	cin >> number_of_people;
	cout << "请输入抽取编号的步长" << endl;
	cin >> size_of_step;
	Josephu test(number_of_people, size_of_step);
	test.set_Josephu_list();
	test.test_Josephu_list();
	return 0;
}