#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include "sqlite3.h"
using namespace std;
void PrintMessage(string message, bool printTop = true, bool printBottom = true)//print message between borders
{
    if (printTop)//draw top frame
    {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    }
    else
    {
        cout << "|";
    }
    bool front = true;//fill the front and the back with blank space so everything will be centered
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();
 
    if (printBottom)//draw bottom frame
    {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
}
void DrawHangman(int guessCount = 0)//draw the actual hangman based on number of errors made
{
   
    if (guessCount >= 1)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);
 
    if (guessCount == 2)
        PrintMessage("/  ", false, false);
   
    if (guessCount == 3)
        PrintMessage("/| ", false, false);
 
    if (guessCount >= 4)
        PrintMessage("/|\\", false, false);
    else
        PrintMessage("", false, false);
 
    if (guessCount >= 5)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);
 
    if (guessCount == 7)
        PrintMessage("/", false, false);
 
    if (guessCount >= 8)
        PrintMessage("/ \\", false, false);
    else
        PrintMessage("", false, false);
}
void PrintLetters(string input, char from, char to)//Print letters with placeholders until it prints the whole word
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    PrintMessage(s, false, false);
}
void PrintAvailableLetters(string taken)//print the available letters
{
    PrintMessage("Alphabet");
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
}
bool PrintWordAndCheckWin(string word, string guessed)//checks if player has won and prints the word
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    PrintMessage(s, false);
    return won;
}
string LoadRandomWord(string path)//function to generate random word
{
    int lineCount = 0;
    string word;
    vector<string> v;//using a vector as words may have different size
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);
 
        int randomLine = rand() % v.size();//actual random function
 
        word = v.at(randomLine);//word becomes the random word 
        reader.close();
    }
    return word;
}
int TriesLeft(string word, string guessed)//return number of errors
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
            error++;
    }
    return error;
}
int main()
{
    srand(time(0));
    string guesses;
    string wordToGuess;
    wordToGuess = LoadRandomWord("words.txt");
    int tries = 0;
    int score=0;
    bool win = false;
     int rc;
   char *mistake;
    do
    {
        system("clear"); //replace with system("clear"); if you run Linux or MacOS
        PrintMessage("HANGMAN");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("Guess the word");
        win = PrintWordAndCheckWin(wordToGuess, guesses);
 
        if (win)
            break;
 
        char x;
        cout << ">"; cin >> x;
        x= toupper(x);
        if (guesses.find(x) == string::npos)
            guesses += x;
 
        tries = TriesLeft(wordToGuess, guesses);
 
    } while (tries <9);
     score=100-10*tries;//calculating score
     std::string scoretopr = std::to_string(score);//convert score to string
    if (win){
        PrintMessage("YOU WON!");
        PrintMessage("Your score is: "+scoretopr);}//printing score
    else{
        PrintMessage("GAME OVER");
        PrintMessage("Your score is: "+scoretopr);}
      
 
   
   sqlite3 *db;//Open the database
   rc = sqlite3_open("stux_base.db", &db);
   sqlite3_stmt * stmt = nullptr;
   string sqlSelect ="UPDATE minigameScores SET  hagnman="+scoretopr+" WHERE name = 'Nick';";//update the score on hangman minigame
   sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
   sqlite3_step(stmt); 
    PrintMessage("Score Updated to database");
   sqlite3_finalize(stmt);
   sqlite3_close(db);//close database
    //system("pause"); //Linux or MacOS so remove it
    
    getchar();
    return 0;
}

////g++ --std=c++14 test.cpp -o test -lcurses
