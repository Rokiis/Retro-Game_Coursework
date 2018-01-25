#include <iostream>
#include <windows.h>
using namespace std;

void col(char* x) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (x == "r")
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
	else if (x == "b")
		SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);		//function I created that allows you to choose a colour based on letter of colour
	else if (x == "g")
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	else if (x == "y")
		SetConsoleTextAttribute(h, 0x6 | FOREGROUND_INTENSITY); 
	else if (x == "w")
		SetConsoleTextAttribute(h, 0xF | FOREGROUND_INTENSITY);
	else if (x == "p")
		SetConsoleTextAttribute(h, 0xD | FOREGROUND_INTENSITY);
	else if (x == "lb")
		SetConsoleTextAttribute(h, 11 | FOREGROUND_INTENSITY);

}

int main() 
{
	cout << "hello world" << endl;
	col("r");				
	cout << "hello world" << endl;
	col("g");						//example usage of function
	cout << "hello world" << endl;
	col("b");
	cout << "hello world" << endl;
	col("y");
	cout << "hello world" << endl;
	col("w");
	cout << "hello world" << endl;
	col("p");
	cout << "hello world" << endl;
	col("lb");
	cout << "hello world" << endl;
	cout << "" << endl;
	col("r"); cout << "@"; col("g"); cout << "~^~v~" << endl;

	system("pause");
	return 0;
}
