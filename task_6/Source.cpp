#include <iostream>
#include <conio.h>
#include <string>
#include <list>

using namespace std;
void x_print(char x, int n_times)
{
	for (int i = 0; i < n_times; i++)
	{
		cout << x;
	}
}
int print_cl(pair<int, int> init, int remain, int size)
{
	if (init.second <= remain)
	{
		cout << init.first;
		x_print('x', init.second - 1);
		remain -= init.second;
		cout << "|";
	}
	else
	{
		int rest = init.second - remain;//rest shows how many cells have to be reserved in the next line
		cout << init.first;
		x_print('x', remain - 1);
		cout << "|" << endl << "|";
		x_print('x', rest);
		cout << "|";
		remain = size - rest;
	}
	return remain;
}


int main()
{
	list < pair<int, int>> memory;
	
	string command;
	int capacity, line_size;
	int position, size;
	cout << "Set capacity and line size please: " << endl;
	cin >> capacity >> line_size;
	
	cout << "Now you can work with memory manager. Type 'help' to see a list of commands and additional information." << endl;
	while (command != "exit")
	{
		cin >> command;
		if (command == "allocate")
		{
			cin >> size;
			auto init = memory.begin();//previous to insertion
			auto next = memory.begin();
			if (!memory.empty()) ++next;
			while (next != memory.end())
			{
				if ((*next).first - ((*init).second + (*init).first) >= size)//to check if we can push in between the two old clasters
				{
					break;
				}
				init++;
				next++;
			}
			if (memory.empty())
			{
				position = 0;
				cout << position << endl;
				memory.insert(next, make_pair(position, size));
			}
			else
			{
				position = (*init).first + (*init).second;
				if ((*init).first + (*init).second + size > capacity)
				{
					cout << "Memory is full" << endl;
				}
				else
				{
					cout << position << endl;
					memory.insert(next, make_pair(position, size));
				}
			}
			
			
		}

		if (command == "help")
		{
			cout << "Available commands :\nhelp - show this help\nexit - exit this program\nprint - print memory blocks map\n";
			cout << "allocate <num> - allocate claster with <num> cells\n free <num> - delete claster beginning in the <num> position\n";
		}
		if (command == "exit")
		{
			break;
		}
		if(command == "free")
		{
			int pos;
			cin >> pos;
			for (auto it = memory.begin(); it != memory.end(); ++it)
			{
				if ((*it).first == pos)
				{
					memory.remove(*it);
					break;
				}
			}
		}

		if (command == "print")
		{
			int remain;
			cout << endl;
			if (memory.empty())
			{
				int count = capacity;
				
				while (count != 0)
				{
					int repetitions = line_size;

					if (count < line_size)
					{
						repetitions = count;
					}
					cout << "|";
					x_print(' ', repetitions);
					cout << "|" << endl;
					remain -= repetitions;

				}
				
			}
			else
			{
				remain = line_size;
				
					cout << "|" ;
					auto init = memory.begin();
					auto next = ++memory.begin();

					while (next != memory.end())
					{
						if ((*init).first == 0)
						{
							
							remain = print_cl(*init, remain, line_size);
							
						}

						else
						{
							if (init == memory.begin())
							{
								x_print(' ', (*init).first);
								cout << "|";
								remain = line_size - (*init).first;
								
								remain = print_cl( *init, remain, line_size);
								
							}
							else
							{
								
								remain = print_cl(*init, remain, line_size);
							}

						}

						if (remain == 0)
						{
							cout << endl;
							cout << "|";
							remain = line_size;
						}
						int space = (*next).first - ((*init).first + (*init).second  + 1);
						if (space > 0)
						{
							x_print(' ', space);
							remain -= space;
							
						}
						init++;
						++next;
					}
					remain = print_cl(*init, remain, line_size);
					int rest = capacity - ((*init).first + (*init).second);
					while (rest != 0)
					{
						if (remain == 0)
						{
							cout << "|" << endl << "|";
							remain = line_size;
						}
						cout << ' ';
						rest--;
						remain--;
					}
					cout << "|";
				
			}
			cout << endl;
			
		}
	}
	
	


	_getch();
	return 0;
}