#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, score;
int tailX[100], tailY[100];
int nTail;
int bonus = 2;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
int nFruit = 1;
struct fruit
{
    int x,y;
};

//MODE PREMIUM
bool premium = false;
struct money
{
    int x,y;     // if u get money score increase 50
};
struct fire
{
    int x, y;   //if u get fire game over
};

fruit fruit;
money money;
fire fire;

//MEMORY VARIABLES
int record;
fstream memory;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruit.x = rand() % width;
    fruit.y = rand() % height;
    if(premium)
    {
        do
		{
			money.x = rand() % width;
       	 	money.y = rand() % height;
		}
		while(money.x == fire.x && money.y == fire.y);
    }
    score = 0;
    //MEMORY READING
    memory.open("memory.txt",ios::in);
    memory >> record;
    memory.close();
}
void Draw()
{
    system("cls"); //system("clear");
    //top of the board
    for (int i = 0; i < width+2; i++)
        cout << "_";
    cout << endl;
// the board
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "O";
            else	if(premium && i == money.y && j == money.x)
                cout << '$';
            else 	if(premium && i == fire.y && j == fire.x)
                cout << 'x';
            else    if (i == fruit.y && j == fruit.x)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1 )
                cout << "|";

        }
        cout << endl;
    }

//bottom of the board
    for(int k = 0; k < width + 2; k++)
        cout << "*";
    cout << endl;
    cout << "Score:" << score << endl;
    cout << "Record:" << record << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case '1':
            dir = LEFT;
            break;
        case '3':
            dir = RIGHT;
            break;
        case '5':
            dir = UP;
            break;
        case '2':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        case '+': 
			premium = true; 
			break;
		case '-':
			system("PAUSE");
			break;
        }
    }
}
void Logic()
{
    // tail movement
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
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
    // snake movement
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
    //mode premium
    if(premium)
    {
        if (x >= width) x = 0; else if (x < 0) x = width - 1;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;

        if (x == money.x && y == money.y)
        {
            score += 50;
            money.x = rand() % width;
            money.y = rand() % height;

            for(int h = 0; h<nFruit; h++)
            {
                do
                {
                    fire.x = rand() % width;
                    fire.y = rand() % height;
                }
                while((fire.x == fruit.x && fire.y == fruit.y) || (fire.x == money.x && fire.y == money.y));
            }

        
        }
        
        if (x == fire.x && y == fire.y)
        {
            gameOver = true;
        }
    }
    else        //basic mode
    {
        if (x > width || x < 0 || y > height || y < 0)
            gameOver = true;
    }

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    for(int h = 0; h<nFruit; h++)
    {
        if (x == fruit.x&& y == fruit.y)
        {
            score += 10;
            fruit.x = rand() % width;
            fruit.y = rand() % height;
            nTail++;
        }
    }


}
void Memory()
{
    system("PAUSE");
    system("cls");
    if(score > record)
    {
        memory.open("memory.txt",ios::out);
        memory.clear();
        memory << score;
        memory.close();
        cout << "***NEW RECORD***\n\n\n";
        record = score;
    }
    cout << "YOUR SCORE: " << score;
    cout << "\n\n\nRECORD: " << record << "\n\n\n\n\n\n";
}



int main()
{
    Setup();
    while (!gameOver)
    {
        cout <<"\n\n\nSNAKE\n\n\n";
        Draw();
        Input();
        Logic();
        Sleep(20); //sleep(10);
    }
    Memory();
    system("PAUSE");
    return 0;
}
