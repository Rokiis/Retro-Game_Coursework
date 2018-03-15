#include "money_rush.h"
#include "sqlite3.h"

using namespace std;

//global variable stores the end game score
int finalpoints = 0;

//main function opens the detabase, updates the score information in the db with the game score
int main()
{
    playerclass s;
    s.start();
    int rc;
    sqlite3 *db;
    rc = sqlite3_open("stux_base.db", &db);
    sqlite3_stmt * stmt;
    string sqlSelect = "UPDATE minigameScores SET patrykGame = (?3) WHERE name = 'Nick'";
    sqlite3_prepare(db, sqlSelect.c_str(), sqlSelect.size(), &stmt, nullptr);
    sqlite3_bind_int(stmt, 3, finalpoints);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

playerpart::playerpart(int col, int row)
{
    x=col;
    y=row;
}

playerpart::playerpart()
{
    x=0;
    y=0;
}

playerclass::playerclass()
{
    initscr(); //initialises screen
    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho(); 
    curs_set(0); //turns off cursor
    getmaxyx(stdscr, maxheight, maxwidth); //determines and sets coord for eadges of terminal window
    //initialise few varaibles
    partchar='@';
    topchar='-';
    botchar='_';
    sidechar='|';
    dollar='$';
    enemy='*';
    dollars.x=0;
    dollars.y=0;
    for(int i=0;i<1;i++) 
        player.push_back(playerpart(maxwidth/2,maxheight/2));
    points=0;
    lives=3;
    del=110000;
    get=false;
    shot=false;
    direction='s';
    srand(time(NULL));
    putdollars();
    putenemies();
    //creates the edges of the map
    for(int i=0;i<maxwidth-1;i++)
    {
        move(0,i);
        addch(topchar);
    }
    for(int i=0;i<maxwidth-1;i++)
    {
        move(maxheight-2,i);
        addch(botchar);
    }  
    for(int i=0;i<maxheight-1;i++)
    {
        move(i,0);
        addch(sidechar);
    }
    for(int i=0;i<maxheight-1;i++)
    {
        move(i,maxwidth-2);
        addch(sidechar);
    }
    //draws the player
    for(int i=0; i<player.size();i++)
    {
        move(player[i].y,player[i].x);
        addch(partchar);
    }
    //write the points and lives to the screen
    move(maxheight-1,0);
    printw("Points: ");
    move(maxheight-1, 8);
    printw("%d", points);
    move(maxheight-1, 13);
    printw("Lives: ");
    move(maxheight-1, 20);
    printw("%d", lives);
    move(dollars.y,dollars.x);
    addch(dollar);
    refresh();    
}

playerclass::~playerclass()
{
    //wait for user
    nodelay(stdscr,false);
    getch();
    endwin();
}

void playerclass::putdollars()
{
    while(1)
    {
        //generate 2 random numbers, checks if it's in the player's coordinates or outside the terminal
        int tmpx=rand()%maxwidth+1;
        int tmpy=rand()%maxheight+1;
        for(int i=0;i<player.size();i++)
            if(player[i].x==tmpx && player[i].y==tmpy)
                continue;
        if(tmpx>=maxwidth-2 || tmpy>=maxheight-3)
            continue;
        //set the random coordinates to dollar coordinates
        dollars.x=tmpx;
        dollars.y=tmpy;
        break;
     }
    //draw the dollars in the random coordinates
     move(dollars.y,dollars.x);
     addch(dollar);
     refresh();
}

void playerclass::putenemies()
{
    while(1)
    {
        //generate 2 random numbers, checks if it's in the player's coordinates or outside the terminal
        int tmpx2=rand()%maxwidth+1;
        int tmpy2=rand()%maxheight+1;
        for(int i=0;i<player.size();i++)
            if(player[i].x==tmpx2 && player[i].y==tmpy2)
                continue;
        if(tmpx2>=maxwidth-2 || tmpy2>=maxheight-3)
            continue;
        //set the random coordinates to enemy coordinates
        enemies.x=tmpx2;
        enemies.y=tmpy2;
        break;
    }
    //draw the enemy in the random coordinates
    move(enemies.y,enemies.x);
    addch(enemy);
    refresh();
}

bool playerclass::collision()
{
    //check if player has the same coordinates as enemy - if they collided
    if(player[0].x==enemies.x && player[0].y==enemies.y)
    {
        //creates new enemy in another location, updates player lives and prints info on screen
        shot=true;
        putenemies();
        lives-=1;
        move(maxheight-1,20);
        printw("%d",lives);
    }
    //checks if player has collided with a wall
    if(player[0].x==maxwidth-2 or player[0].x==1 or player[0].y==0 or player[0].y==maxheight-2)
    {
        //updates player lives and write onto the screen
        lives-=1;
        move(maxheight-1,20);
        printw("%d",lives);
    }
    
    

    //checks if the player has collided with a dollar
    if(player[0].x==dollars.x && player[0].y==dollars.y)
    {
        //generates another dollar on the screen, updates and write points on screen
        //every 20 points increases player movement 
        get=true;
        putdollars();
        points+=40;
        move(maxheight-1,8);
        printw("%d",points);
        if((points%20)==0)
            del-=1500;
    }else
        get=false;
    return false;

}


void playerclass::moveplayer()
{
    int tmp=getch();
    switch(tmp)
    {
        //changes state of variable direction according to the key pressed to keep info of player movement
        case KEY_LEFT:
            direction='l';
            break;
        case KEY_RIGHT:
            direction='r';
            break;
        case KEY_UP:
            direction='u';
            break;
        case KEY_DOWN:
            direction='d';
            break;
        case KEY_BACKSPACE:
            direction='q';
            break;
    }
    if(!collision())
    {
        //updates the fields behind the player to empty strings
        move(player[player.size()-1].y,player[player.size()-1].x);
        addch(' ');
        refresh();
        player.pop_back();
    }
    
    
    //when player hit the edges, moves player in opposite direction
    if(player[0].x==maxwidth-2)
        direction='l';
    if(player[0].x==1)
        direction='r';
    refresh();
    if(player[0].y==0)
        direction='d';
    if(player[0].y==maxheight-2)
        direction='u';
    refresh();
    
    //the direction of the player movement changes the position of player accordingly
    if(direction=='l')
        player.insert(player.begin(),playerpart(player[0].x-1,player[0].y));
    else if(direction=='r')
        player.insert(player.begin(),playerpart(player[0].x+1,player[0].y));
    else if(direction=='u')
        player.insert(player.begin(),playerpart(player[0].x,player[0].y-1));
    else if(direction=='d')
        player.insert(player.begin(),playerpart(player[0].x,player[0].y+1));
    else if(direction=='s')
        player.insert(player.begin(),playerpart(player[0].x,player[0].y));
    move(player[0].y,player[0].x);
    addch(partchar);
    refresh();
    
    

        
}

void playerclass::start()
{
    while(1)
    {
        if(lives==0)
        {
            //if player dies, prints game message and points
            clear();
            move(maxheight/2,maxwidth/2);
            finalpoints = points;
            printw("Game Over");
            move(maxheight/2+1,maxwidth/2-5);
            printw("Your points are: %d", finalpoints);
            break;
        }
        if(points==2000)
        {
            //when player gethers 2k points, clears screen and prints message and points
            clear();
            move(maxheight/2,maxwidth/2);
            finalpoints = points;
            printw("You Won!");
            move(maxheight/2+1,maxwidth/2-5);
            printw("Your points are: %d", finalpoints);
            break;
        }
        //backspace stop the game and exits after keypress
        moveplayer();
        if(direction=='q')
            break;
        usleep(del);
    }
}
