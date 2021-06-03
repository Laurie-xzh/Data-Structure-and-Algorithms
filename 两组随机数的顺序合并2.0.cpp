/*
目标:   把两组随机数合并成一组顺序数,输入数组长度时可以防止负数与小数以及其它字符
作者：61520711徐子航
日期：2021.3.9
版本：2.0
*/


#include<iostream>
#include <cstdlib>
#include <ctime>
#include<string>
#include<ctype.h>
#include <stdlib.h>

#include <sstream>
using namespace std;


//这里用了全局变量，因为不同的函数都要调用
double* nums1;
double* nums2;
double* num;
/**
*@brief      设置两个数组的长度
*
* @param N1   第一次输入，要进行有效性判断
* @param N2   第二次输入，要进行有效性判断
*@param   n1  第一个数组的长度        这里使用引用，从而可以对外传参
* @param  n2  第二个数组的长度        这里使用引用，从而可以对外传参
* @return  void
*/
//复杂度为O(n)
void init_length(string & N1, string & N2,double&n1,double &n2)
{
	/*do
	{
		cout << "设置第一组数的长度" << endl;
		cin >> n1;
		cout << "设置第二组数的长度" << endl;
		cin >> n2;
		cout << "长度为非负！！！" << endl;
	} while (n1 < 0 || n2 < 0 || (int)n1 != n1 || (int)n2 != n2);*/
	int judge_N1 = -1;
	int judge_N2 = -1;
	while (judge_N1 != 0 || judge_N2 != 0)
	{
		cout << "设置第一组数的长度" << endl;
		cin >> N1;
		cout << "设置第二组数的长度" << endl;
		cin >> N2;
		cout << "长度为非负！！！" << endl;

		for (int i = 0; i <= N1.length() - 1; i = i + 1)
		{
			if (isdigit(N1[i]) == 0)
			{
				judge_N1 = -1;
				break;
			}
			else
			{
				judge_N1 = 0;
			}
		}
		for (int i = 0; i <= N2.length() - 1; i = i + 1)
		{
			if (isdigit(N2[i]) == 0)
			{
				judge_N2 = -1;
				break;
			}
			else
			{
				judge_N2 = 0;
			}
		}
		if (judge_N1 == -1)
		{
			cout << "第一个输入有问题，是个非负整数！！！"<<endl;
			cout << "-_-" << endl;
			cout << endl;
		}
		if (judge_N2 == -1)
		{
			cout << "第二个输入有问题，是个非负整数！！！ " << endl;
			cout << "-_-" << endl;
			cout << endl;
		}
		if (judge_N1 == 0 && judge_N2 == 0)
		{
			stringstream ss;
			ss << N1;
			ss >> n1;
			stringstream sss;
			sss << N2;
			sss >> n2;

			break;

			/*
			本来这一段是为了判断数字是否为非负整数，但发现在前面输小数与负数都因为“.”与“-”不是数字而挡在了上面的判断里，
			下面的部分没啥用，就注释掉了。
			那么问题来了，如果以后有场景要求输入小数与负数（负数还好，判断第一个为“-”就好，但小数还有待解决），该怎么办呢
			有待进一步优化
			以及中文输入会崩溃，这个问题没解决
			*/

			/*if (n1 >= 0  &&  n2 >= 0 && (int)n1 == n1 && (int)n2 == n2)
			{
				break;
			}
			else
			{
				cout << "长度得是一个非负整数！！！"   <<endl;
				cout << "-_-" << endl;
			}*/

		}
	}

}


/**
*@brief      把数组打出来
*
*@param   double* arr  是要打印的数组
* @param  n 数组的长度，用来对数组进行遍历
* @return  void
*/
void print(double* arr, double n)
{
	for (int i = 0; i <= n - 1; i = i + 1)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

/**
*@brief      用随机数初始化nums1和nums2,并且打印
*
*@param    n1  nums1的长度
* @param   n2  nums2的长度
* @return   void
*/

//复杂度为O(n)
void init_nums(double n1, double n2)
{
	
	nums1 = new double[n1];
	nums2 = new double[n2];
	//第一组数开始初始化
	for (int i = 0; i <= n1 - 1; i = i + 1)
	{
		//nums1[i] = rand() % 100;
		// (unsigned int)((rand() << 16) + rand()) % (size * 10)
		nums1[i] = (unsigned int)((rand() << 16) + rand()) % (100 * 10);     //赋上随机数
	}
	//第二组数开始初始化
	for (int j = 0; j <= n2 - 1; j = j + 1)
	{
		//nums2[j] = rand() % 100;
		nums2[j] = (unsigned int)((rand() << 16) + rand()) % (100 * 10);
	}


	cout << "第一组数随机赋值" << endl;
	print(nums1, n1);
	cout << endl;

	cout << "第二组数随机赋值" << endl;
	print(nums2, n2);
	cout << endl;
}


/**
*@brief         对数组进行排序
*
*@param      double* arr  要排序的数组
* @param     left  左界/（左哨兵，帮助排序）
* @param     right  右界/(右哨兵，帮助排序)
* @return     void
*/
//复杂度为nlgn
void quicksort(double* arr, int left, int right)
{

	int i, j, t;
	double temp;
	if (left > right)
	{
		return;
	}
	temp = arr[left];
	i = left;
	j = right;
	while (i != j)
	{
		while (arr[j] >= temp && i < j)
		{
			j--;
		}
		while (arr[i] <= temp && i < j)
		{
			i++;
		}
		if (i < j)
		{
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}
	arr[left] = arr[i];
	arr[i] = temp;

	quicksort(arr, left, i - 1);
	quicksort(arr, i + 1, right);
}

/**
*@brief         对nums1和nums2两个数组进行合并
*
*@param      double* nums1  要排序的第一组数
* @param     double* nums2  要排序的第二组数
* @param     n1  第一组数的长度
* @param     n2  第二组数的长度
* @return     void
*/
//复杂度为O(n1+n2)=O(n)
void merge(double* nums1, double* nums2, double n1, double n2)
{
	num = new double[n1 + n2];
	int x = 0;
	int y = 0;
	int n = 0;
	while (x < n1 && y < n2)
	{
		if (nums1[x] <= nums2[y])
		{
			num[n] = nums1[x];
			x++;
			n++;
		}
		else
		{
			num[n] = nums2[y];
			y++;
			n++;
		}
	}
	while (x < n1)
	{
		num[n] = nums1[x];
		x++;
		n++;
	}
	while (y < n2)
	{
		num[n] = nums2[y];
		y++;
		n++;
	}
	/*for (int i = 0; i <= n1+n2 - 1; i = i + 1)
	{
		cout << num[i] << " ";
	}*/
	cout << "合并后的效果" << endl;
	print(num, n1 + n2);
	cout << endl;
}

/**
*@brief     释放内存
*
* @return  void
*/
void release()
{
	if (nums1)
	{
		delete[]nums1;
	}
	if (nums2)
	{
		delete[]nums2;
	}
	if (num)
	{
		delete[]num;
	}
}

int main()
{
	string N1 = " ";
	string N2 = " ";


	double n1 = 0;
	double n2 = 0;
	init_length(N1, N2,n1,n2);
	init_nums(n1, n2);
	quicksort(nums1, 0, n1 - 1);
	quicksort(nums2, 0, n2 - 1);

	cout << "第一组数排序后的样子" << endl;
	print(nums1, n1);
	cout << endl;

	cout << "第二组数排序后的样子" << endl;
	print(nums2, n2);
	cout << endl;

	merge(nums1, nums2, n1, n2);
	release();
	return 0;
	//取所有复杂度得最大值，应为nlgn
}
