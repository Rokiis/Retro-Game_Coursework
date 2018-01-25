//first game
//d.jones
#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;
 
bool gameOver;
bool cheatMode;
const int width = 40;           //game field size
const int height = 20;
int x, y, heartX, heartY, score;    //snake head (x,y) and heart positioning
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //movement
eDirection dir;
 
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    heartX = rand() % width;
    heartY = rand() % height;
    score = 0;
}
void Draw() {
    system("cls"); //clears screen
    for (int i = 0; i <= width + 1; i++) {
        cout << "@";
    }
    cout << endl;
    for (int i = 0; i <= height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0)
                cout << "@";
            if (i == y && j == x && cheatMode == true)
                cout << "X";
            else if (i == y && j == x)
                cout << "O";
            else if (i == heartY && j == heartX)
                cout << "0";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "@";
        }
        cout << endl;
    }
    for (int i = 0; i <= width + 1; i++)
        cout << "@";
    cout << endl;
    cout << "Points: " << score << endl;
    if (cheatMode == true)
        cout << "Cheatmode enabled..." << endl;
}
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':       //hotkeys
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            gameOver = true;
            break;
        case 'c':
            cheatMode = true;
            break;
        case 'l':
            if (cheatMode == true)
                score += 9999999;
        }
    }
}
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2Y, prev2X;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if (x > width || x < 0 || y > height || y < 0)    //uncomment to make walls lethal
    //gameOver = true;
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    if (x == heartX && y == heartY)     //if snake head (x,y) touches item, score increases by 10
    {
        score += 10;
        heartX = rand() % width;
        heartY = rand() % height;
        nTail++;
    }
}
int main() {
    Setup();
    while (!gameOver) {
        if (dir == LEFT || dir == RIGHT)
        {
            Sleep(5);
        }
        Sleep(20);
        if (dir == UP || dir == DOWN)           //fixes glitch with up/down being faster than left/right
        {
            Sleep(60);
        }
        Draw();
        Input();
        Logic();
    }
    return 0;
}