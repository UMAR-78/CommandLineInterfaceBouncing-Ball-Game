#include <iostream>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;

//*********************************************************Function Prototypes*******************************************************
void header();
void print(char maze[][107]);
void print_level2_maze(char maze2[][107]);
// Ball movement function
void movefirst_p_Down(char maze[][107], int &B_X, int &B_Y, int &score, int &health);
void movefirst_p_Up(char maze[][107], int &B_X, int &B_Y, int &score, int &health);
void movefirst_p_Right(char maze[][107], int &B_X, int &B_Y, int &score, int &health);
void movefirst_p_Left(char maze[][107], int &B_X, int &B_Y, int &score, int &health);
void gotoxy(int x, int y);
void load_level_1(char maze[][107], int rowsize, int colsize);
// Function to move spider up down left and right
void movemet_of_spider1(char maze[][107], string &direction, int &rowCount, int &colIdx, int &health, int &B_X, int &B_Y, char previouitem1);
void movemet_of_spider2(char maze[][107], string &direction2, int &rowCount2, int &colIdx2, int &B_X, int &B_Y, int &health);
void movemet_of_spider3(char maze[][107], string &direction3, int &colCount, int &rowIdx, int &B_X, int &B_Y, int &health);
void calculate_score(int &score);
void printscore(int &score);
void calculate_health(int &health);
void printhealth(int &health);
void fire_X(char maze[][107], int &enemyX, int &enemyY, int &fire_of_X_X, int &fire_of_X_Y, int &B_X, int &B_Y, int &health);
bool bounce_ball_right(char maze[][107], int &B_X, int &B_Y, int &score, int &health);
void bounce_ball_left(char maze[][107], int &B_X, int &B_Y, int &score, int &health);
// Functoin for random movement of spider
int random();
void random_movement(char maze[][107], int &rowidx4, int &colidx4, char &previousItem3, int &B_X, int &B_Y, int &health);
//*********************level changer
void level_changer(char maze[][107], int &B_X, int &B_Y, int &score, int &health, int &level, int &rowCount, int &colIdx, int &rowCount2, int &colIdx2, int &colCount, int &rowIdx, int &rowidx4, int &colidx4);
void load_level_2(char maze[][107]);
void print_level2_maze(char maze[][107]);

//************************************************************MAIN Function*********************************************************
main()
{
    int level = 1;
    char maze[24][107];

    // Coordinates of BALL B
    int B_X = 22;
    int B_Y = 3;
    // Coordinates of ball b in MAZE 2
    int ballx = 21;
    int bally = 9;
    // row and col size of the level 1 maze
    int rowsize = sizeof(maze) / sizeof(maze[0]);
    int colsize = sizeof(maze[0]) / sizeof(maze[0][0]);
    // index for the movement of spider 1
    int rowCount = 1;
    int colIdx = 24;
    // index for the movement of spder 2
    int rowCount2 = 1;
    int colIdx2 = 60;
    // indes for the movement of sprder 3
    int colCount = 72;
    int rowIdx = 14;
    // index for the random movement of spider4
    int rowidx4 = 2;
    int colidx4 = 6;

    // index for the fire of X
    int enemyX = 14;
    int enemyY = 44;

    int fire_of_X_X = enemyX;
    int fire_of_X_Y = enemyY;
    // Direction for the movement of the spider
    string direction = "down";
    string direction2 = "down";
    string direction3 = "left";
    // Score
    int score = 0;
    // For health
    int health = 5;
    // Bool type variable to start or break the loop
    bool gameRunning = 1;
    // For ghost
    char previouitem1 = ' ';
    char previouitem2 = ' ';
    char previouitem3 = ' ';
    char previousItem3 =' ';
    load_level_1(maze, rowsize, colsize);
    system("cls");
    print(maze);
    // system("color 9");

    while (gameRunning && health != 0)
    {
        Sleep(100);
        printhealth(health);
        printscore(score);
        movemet_of_spider1(maze, direction, rowCount, colIdx, health, B_X, B_Y, previouitem1);
        movemet_of_spider2(maze, direction2, rowCount2, colIdx2, B_X, B_Y, health);
        movemet_of_spider3(maze, direction3, colCount, rowIdx, B_X, B_Y, health);
        random_movement(maze, rowidx4, colidx4, previousItem3, B_X, B_Y, health);
        level_changer(maze, B_X, B_Y, score, health, level, rowCount, colIdx, rowCount2, colIdx2, colCount, rowIdx, rowidx4, colidx4);

        // fire function of enemy X
        fire_X(maze, enemyX, enemyY, fire_of_X_X, fire_of_X_Y, B_X, B_Y, health);

        // level_changer(maze, maze2, first_p_X, first_p_Y, score, health, gameRunning, level, rowsize2, colsize2);

        if (GetAsyncKeyState(VK_LEFT))
        {
            movefirst_p_Left(maze, B_X, B_Y, score, health);
        }
        // if right arrow key is pressed the player 1 A move right
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movefirst_p_Right(maze, B_X, B_Y, score, health);
        }
        // if left upward key is pressed the player 1 A move up
        if (GetAsyncKeyState(VK_UP))
        {
            movefirst_p_Up(maze, B_X, B_Y, score, health);
        }
        // if left downward arrow key is pressed the player 1 A move down
        if (GetAsyncKeyState(VK_DOWN))
        {
            movefirst_p_Down(maze, B_X, B_Y, score, health);
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
        if (GetAsyncKeyState(32))
        {
             bounce_ball_right(maze, B_X, B_Y, score, health);
        
                
            
        }
        if (GetAsyncKeyState(VK_SHIFT))
        {
            bounce_ball_left(maze, B_X, B_Y, score, health);
        }
    }

    if (health == 0 && score < 180)
    {
        gameRunning = 0;
        gotoxy(26, 26);

        cout
            << "SORRY YOU LOST";
    }

    else if (health >= 1 && score >= 180)
    {
        gameRunning = 0;
        gotoxy(26, 26);

        cout
            << "You won";
    }
}
//*******************************************************Function Definition*****************************************************
void calculate_score(int &score)
{
    score++;
}
void printscore(int &score)
{
    gotoxy(130, 4);
    cout << "Score = " << score;
}

void calculate_health(int &health)
{
    health--;
}
void printhealth(int &health)
{
    gotoxy(130, 5);
    cout << "Health = " << health;
}

// Function for the loading of the level 1
void load_level_1(char maze[][107], int rowsize, int colsize)
{
    fstream newfile;
    string record;
    newfile.open("level1.txt", ios::in);
    {
        for (int row = 0; row < rowsize; row++)
        {
            getline(newfile, record);
            for (int col = 0; col < colsize; col++)
            {
                maze[row][col] = record[col];
            }
        };
    }
}
void load_level_2(char maze[][107])
{
    fstream newfile;
    string record;
    newfile.open("level2.txt", ios::in);
    {
        for (int row = 0; row < 22; row++)
        {
            getline(newfile, record);
            for (int col = 0; col < 107; col++)
            {
                maze[row][col] = record[col];
            }
        };
    }
}
void print_level2_maze(char maze[][107])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 107; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

// Function to print something on the specific loaction
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
// Function to print on the maze
void print(char maze[][107])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 107; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}
// Function to print BALL B on the maze to the left side
void movefirst_p_Left(char maze[][107], int &B_X, int &B_Y, int &score, int &health)
{
    if (maze[B_X][B_Y - 1] == ' ' || maze[B_X][B_Y - 1] == '*')
    {
        // put the space on the location of B
        maze[B_X][B_Y] = ' ';
        gotoxy(B_Y, B_X);
        cout << " ";
        if (maze[B_X][B_Y - 1] == '*')
        {
            calculate_score(score);
        }

        B_Y = B_Y - 1;
        if (maze[B_X][B_Y - 1] == 'o')
        {
            calculate_health(health);
        }
        if (maze[B_X][B_Y - 1] == 'E')
        {
            score = score + 10;
        }

        // print the player B
        gotoxy(B_Y, B_X);
        cout << "B";
    }
}
// Function to print BALL B on the maze to the right side
void movefirst_p_Right(char maze[][107], int &B_X, int &B_Y, int &score, int &health)
{
    if (maze[B_X][B_Y + 1] == ' ' || maze[B_X][B_Y + 1] == '*')
    {
        // put the space on the location of B
        maze[B_X][B_Y] = ' ';
        gotoxy(B_Y, B_X);
        cout << " ";
        if (maze[B_X][B_Y + 1] == '*')
        {
            calculate_score(score);
        }
        B_Y = B_Y + 1;
        if (maze[B_X][B_Y + 1] == 'o')
        {
            calculate_health(health);
        }
        if (maze[B_X][B_Y + 1] == 'E')
        {
            score = score + 10;
        }

        // if right of the ball is space then ball will fall down
        if (maze[B_X][B_Y + 1] == ' ' && maze[B_X - 1][B_Y] == ' ')
        {
            movefirst_p_Down(maze, B_X, B_Y, score, health);
        }
        gotoxy(B_Y, B_X);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
        cout << "B";
    }
} // Function to print BALL B on the maze to the up side
void movefirst_p_Up(char maze[][107], int &B_X, int &B_Y, int &score, int &health)
{
    if (maze[B_X - 1][B_Y] == ' ' || maze[B_X - 1][B_Y] == '*')
    {
        // put the space on the location of B
        maze[B_X][B_Y] = ' ';
        gotoxy(B_Y, B_X);
        cout << " ";
        if (maze[B_X - 1][B_Y] == '*')
        {
            calculate_score(score);
        }
        B_X = B_X - 1;
        if (maze[B_X - 1][B_Y] == 'o')
        {
            calculate_health(health);
        }
        if (maze[B_X - 1][B_Y] == 'E')
        {
            score = score + 10;
        }

        // if there is the dot on the loctaion of B the score increases by 1

        gotoxy(B_Y, B_X);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);

        cout << "B";
    }
}
// Function to print BALL B on the maze to the down side
void movefirst_p_Down(char maze[][107], int &B_X, int &B_Y, int &score, int &health)
{
    if (maze[B_X + 1][B_Y] == ' ' || maze[B_X + 1][B_Y] == '*')
    {
        // put the space on the location of B
        maze[B_X][B_Y] = ' ';
        gotoxy(B_Y, B_X);
        cout << " ";
        if (maze[B_X + 1][B_Y] == '*')
        {
            calculate_score(score);
        }
        do
        {
            B_X = B_X + 1;
        } while (maze[B_X + 1][B_Y] == ' ' || maze[B_X + 1][B_Y] == '*');

        if (maze[B_X + 1][B_Y] == 'o')
        {
            calculate_health(health);
        }
        if (maze[B_X + 1][B_Y] == 'E')
        {
            score = score + 10;
        }

        gotoxy(B_Y, B_X);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);

        cout << "B";
    }
}
bool bounce_ball_right(char maze[][107], int &B_X, int &B_Y, int &score, int &health)
{
    for (int x = 0; x < 5; x++)
    {
        Sleep(60);
        movefirst_p_Up(maze, B_X, B_Y, score, health);
    }
    for (int x = 0; x < 2; x++)
    {
        Sleep(60);
        movefirst_p_Right(maze, B_X, B_Y, score, health);
    }
    for (int x = 0; x < 5; x++)
    {

        Sleep(60);
        movefirst_p_Down(maze, B_X, B_Y, score, health);
        Sleep(100);
    }
    return 0;
}
void bounce_ball_left(char maze[][107], int &B_X, int &B_Y, int &score, int &health)
{
    for (int x = 0; x < 5; x++)
    {
        Sleep(20);
        movefirst_p_Up(maze, B_X, B_Y, score, health);
    }
    for (int x = 0; x < 2; x++)
    {
        Sleep(20);
        movefirst_p_Left(maze, B_X, B_Y, score, health);
    }
    for (int x = 0; x < 6; x++)
    {

        Sleep(20);
        movefirst_p_Down(maze, B_X, B_Y, score, health);
        Sleep(100);
    }
}
// Fnuction to monve sppider
void movemet_of_spider1(char maze[][107], string &direction, int &rowCount, int &colIdx, int &health, int &B_X, int &B_Y, char previouitem1)
{ // Sleep(100);
    if (direction == "down")
    {

        if (maze[rowCount + 1][colIdx] == '#' || maze[rowCount + 1][colIdx] == '%' || maze[rowCount + 1][colIdx] == '|' || maze[rowCount + 1][colIdx] == '*' || maze[rowCount + 1][colIdx] == 'S')
        {
            direction = "up";
        }
        else
        {
            maze[rowCount][colIdx] = previouitem1;
            gotoxy(colIdx, rowCount);
            cout << previouitem1;
            // increment in row to print on the +1 index
            rowCount++;
            previouitem1 = maze[rowCount][colIdx];
            gotoxy(colIdx, rowCount);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << 'S';
            // To check ball index and spider index
            // if both are at same index then -health

            if (rowCount + 1 == B_X && colIdx == B_Y)
            {
                calculate_health(health);
            }
        }
    }
    else if (direction == "up")
    {

        maze[rowCount][colIdx] = ' ';
        gotoxy(colIdx, rowCount);
        cout << " ";
        rowCount--;
        gotoxy(colIdx, rowCount);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        cout << 'S';
        // To check ball index and spider index
        // if both are at same index then -health

        if (rowCount - 1 == B_X && colIdx == B_Y)
        {
            calculate_health(health);
        }
        if (maze[rowCount - 1][colIdx] == '#' || maze[rowCount - 1][colIdx] == '*' || maze[rowCount - 1][colIdx] == 'S')
        {
            direction = "down";
        }
    }
}
void movemet_of_spider2(char maze[][107], string &direction2, int &rowCount2, int &colIdx2, int &B_X, int &B_Y, int &health)
{
    if (direction2 == "down")
    {
        if (maze[rowCount2 + 1][colIdx2] == '#' || maze[rowCount2 + 1][colIdx2] == '%' || maze[rowCount2 + 1][colIdx2] == '|')
        {
            direction2 = "up";
        }
        else
        {
            gotoxy(colIdx2, rowCount2);
            cout << " ";
            rowCount2++;
            gotoxy(colIdx2, rowCount2);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << 'S';
            // To check ball index and spider index
            // if both are at same index then -health

            if (rowCount2 + 1 == B_X && colIdx2 == B_Y)
            {
                calculate_health(health);
            }
        }
    }
    else if (direction2 == "up")
    {
        gotoxy(colIdx2, rowCount2);
        cout << " ";
        rowCount2--;
        gotoxy(colIdx2, rowCount2);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        cout << 'S';
        // To check ball index and spider index
        // if both are at same index then -health

        if (rowCount2 - 1 == B_X && colIdx2 == B_Y)
        {
            calculate_health(health);
        }

        if (maze[rowCount2 - 1][colIdx2] == '#')
        {
            direction2 = "down";
        }
    }
}
void movemet_of_spider3(char maze[][107], string &direction3, int &colCount, int &rowIdx, int &B_X, int &B_Y, int &health)
{
    if (direction3 == "left")
    {
        if (maze[rowIdx][colCount + 1] != ' ')
        {
            direction3 = "right";
        }
        else
        {
            gotoxy(colCount, rowIdx);
            cout << " ";
            colCount++;
            gotoxy(colCount, rowIdx);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << 'S';
            // To check ball index and spider index
            // if both are at same index then -health
            if (rowIdx == B_X && colCount + 1 == B_Y)
            {
                calculate_health(health);
            }
        }
    }
    if (direction3 == "right")
    {

        gotoxy(colCount, rowIdx);
        cout << " ";
        colCount--;
        gotoxy(colCount, rowIdx);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);

        cout
            << 'S';
        // To check ball index and spider index
        // if both are at same index then -health

        if (rowIdx == B_X && colCount - 1 == B_Y)
        {
            calculate_health(health);
        }

        if (maze[rowIdx][colCount - 1] != ' ')
        {
            direction3 = "left";
        }
    }
}
void fire_X(char maze[][107], int &enemyX, int &enemyY, int &fire_of_X_X, int &fire_of_X_Y, int &B_X, int &B_Y, int &health)
{
    if (maze[fire_of_X_X][fire_of_X_Y - 1] == ' ')
    { // movmenet  from left to right decreases of bomb of enemy X
        fire_of_X_Y--;
        // locate enemy X bomb
        gotoxy(fire_of_X_Y, fire_of_X_X);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        cout << ".";
        // reset the orevious postion into blank(empty space)
        gotoxy(fire_of_X_Y + 1, fire_of_X_X);
        cout << " ";
        // to bring back fire if reached to |
        if (maze[fire_of_X_X][fire_of_X_Y - 1] == '|' || maze[fire_of_X_X][fire_of_X_Y - 1] == 'B')
        {
            // if fire reached the obstacle then reset the fire
            gotoxy(fire_of_X_Y, fire_of_X_X);
            cout << " ";
            fire_of_X_X = enemyX;
            fire_of_X_Y = enemyY;
        }
        if (fire_of_X_X == B_X && fire_of_X_Y == B_Y)
        {
            calculate_health(health);
        }
    }
}

int random()
{
    srand(time(0));
    int value = 1 + (rand() % 4);
    return value;
}
void random_movement(char maze[][107], int &rowidx4, int &colidx4, char &previousItem3, int &B_X, int &B_Y, int &health)

{
    int value = random();
    if (value == 1)

    { // move right
        if (maze[rowidx4][colidx4 + 1] == ' ')
        {
            gotoxy(colidx4, rowidx4);
            cout << " ";
            colidx4++;
            if (rowidx4 == B_X && colidx4 + 1 == B_Y)
            {
                calculate_health(health);
            }
            maze[rowidx4][colidx4] = ' ';
            gotoxy(colidx4, rowidx4);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << 'g';
        }
    }
    if (value == 2)
    { // move left
        if (maze[rowidx4][colidx4 - 1] == ' ')
        {
            gotoxy(colidx4, rowidx4);
            cout << " ";
            colidx4--;
            if (rowidx4 == B_X && colidx4 - 1 == B_Y)
            {
                calculate_health(health);
            }
            maze[rowidx4][colidx4] = ' ';

            gotoxy(colidx4, rowidx4);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << 'g';
        }
    }
    if (value == 3)
    { // move up
        if (maze[rowidx4 - 1][colidx4] == ' ')
        {
            gotoxy(colidx4, rowidx4);
            cout << " ";
            rowidx4--;
            if (rowidx4 - 1 == B_X && colidx4 == B_Y)
            {
                calculate_health(health);
            }
            maze[rowidx4][colidx4] = ' ';

            gotoxy(colidx4, rowidx4);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << 'g';
        }
    }
    if (value == 4)
    { // move down
        if (maze[rowidx4 + 1][colidx4] == ' ')
        {
            gotoxy(colidx4, rowidx4);
            cout << " ";
            rowidx4++;
            if (rowidx4 + 1 == B_X && colidx4 == B_Y)
            {
                calculate_health(health);
            }
            maze[rowidx4][colidx4] = ' ';

            gotoxy(colidx4, rowidx4);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << 'g';
        }
    }
}
void level_changer(char maze[][107], int &B_X, int &B_Y, int &score, int &health, int &level, int &rowCount, int &colIdx, int &rowCount2, int &colIdx2, int &colCount, int &rowIdx, int &rowidx4, int &colidx4)
{ // in case of find L which is level changer
    if ((maze[B_X + 1][B_Y] == 'L' || maze[B_X][B_Y + 1] == 'L') && score >= 84)
    {
        if (level == 1)
        {
            level = 2;
            B_X = 20;
            B_Y = 3;

            // index for the movement of spider 1
            rowCount = 2;
            colIdx = 5;
            // index for the movement of spder 2
            rowCount2 = 2;
            colIdx2 = 7;
            // indes for the movement of sprder 3
            colCount = 32;
            rowIdx = 8;
            // index for the random movement of spider4
            rowidx4 = 19;
            colidx4 = 90;

            system("cls");
            load_level_2(maze);
            print_level2_maze(maze);
        }
        else
        {
        }
    }
}