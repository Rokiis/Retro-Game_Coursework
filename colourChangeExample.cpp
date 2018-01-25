#include <iostream>
#include <windows.h>
using namespace std;

void colour(char x) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (x == 'r')
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	else if (x == 'b')
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);		//function I created that allows you to choose a colour based on letter of colour
	else if (x == 'g')
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

}

int main() 
{
	cout << "hello world" << endl;
	colour('r');				
	cout << "hello world" << endl;
	colour('g');						//example usage of function
	cout << "hello world" << endl;
	colour('b');
	cout << "hello world" << endl;

	system("pause");
	return 0;
}
