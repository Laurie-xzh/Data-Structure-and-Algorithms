#include<iostream>
#include<string>
#include<stack>

using namespace std;

template<class T>
class Stack : public stack<T>
{

public:
	T pop()
	{
		T tmp = this->top();
		stack<T>::pop();
		return tmp;
	}
};

class cell
{
private:
	int x, y;
public:
	cell(int i = 0, int j = 0)
	{
		 x = i;
		 y = j;
	}
	bool operator==(const cell& c)const
	{
		return x == c.x && y == c.y;
	}
	friend class maze;
};

class maze
{
public:
	maze();
	void exit_maze();
private:
	cell current_cell, exit_cell, begin_cell;
	const char exit, entry, visited, passable, wall;
	Stack<cell> mazeStack;
	char** store;
	void pushUnvisited(int, int);
	friend ostream& operator<<(ostream&, const maze&);
	int rows, cols;
};
maze::maze() :exit('e'), entry('m'), visited('.'), passable('0'), wall('1')
{
	Stack<char*>mazerows;
	char str[50];
	char* s;
	int col, row = 0;
	cout << "根据下面的提示输入一个迷宫\n"
		<< "m----起点\ne----出口\n.----看过的点\n0----可通过的点\n1----墙\n"
		<< "一次输一行；  所有的行数输完后以Ctrl-z结尾退出 \n";
	while (cin >> str)
	{
		row++;
		cols = strlen(str);
		s = new char[cols + 3];

		//mazerows.push(s);

		//strcpy_s(s + 1, cols,str);
		for (int i = 1; i <= cols ; i++)
		{
			s[i] = str[i - 1];
		}
	
		s[0] = s[cols + 1] = wall;
		s[cols + 2] = '\0';
		mazerows.push(s);
		if (strchr(s, exit) != 0)
		{
			exit_cell.x = row;
			exit_cell.y = strchr(s, exit) - s;
		}
		if (strchr(s, entry) != 0)
		{
			begin_cell.x = row;
			begin_cell.y = strchr(s, entry) - s;
		}
	}
	rows = row;
	store = new char* [rows + 2];
	store[0] = new char[cols + 3];
	for (; !mazerows.empty(); row--)
	{
		store[row] = mazerows.pop();
	}
	store[rows + 1] = new char[cols + 3];
	store[0][cols + 2] = '\0';
	store[rows + 1][cols + 2] = '\0';
	for (col = 0; col <= cols + 1; col++)
	{
		store[0][col] = wall;
		store[rows + 1][col] = wall;
	}

}



void maze::pushUnvisited(int row, int col)
{
	if (store[row][col] == passable || store[row][col] == exit)
	{
		mazeStack.push(cell(row, col));
	}
 }

void maze::exit_maze()
{
	int row, col;
	current_cell = begin_cell;
	while (!(current_cell == exit_cell))
	{
		row = current_cell.x;
		col = current_cell.y;
		cout << *this;
		if (!(current_cell == begin_cell))
		{
			store[row][col] = visited;
		}
		pushUnvisited(row - 1, col);
		pushUnvisited(row + 1, col);
		pushUnvisited(row   , col-1);
		pushUnvisited(row , col + 1);
		if (mazeStack.empty())
		{
			cout << *this;
			cout << "failure\n";
			return;
		}
		else
		{
			current_cell = mazeStack.pop();
		}
	}
	cout << *this;
	cout << "出来啦" << endl;
}

ostream& operator<<(ostream& o, const maze& Maze)
{
	for (int row = 0; row <= Maze.rows + 1; row++)
	{
		o << Maze.store[row]<<endl;
	}
	o << endl;
	return o;
}

int main()
{
	maze().exit_maze();
	return 0;
}