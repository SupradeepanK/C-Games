#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ESC 27

void Move_Ship(int move);
void Move_Ship_Horizontally(int moveX);	//Moves ship horizontally instead of vertically
void gotoXY(int x, int y);
void gotoXY(int x, int y, string text);
void WaitKey();
void ShowConsoleCursor(bool showFlag);	//Makes the cursor invisible for smoother graphics

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int main()
{
	cout << "Enter <1> to control ship vertically or\n";
	cout << "Enter <2> to control ship horizontally.\n";
	char userInput;
	cin >> userInput;
	
	gotoXY(0,0,"                                        ");	//Clear previous text
	gotoXY(0,1,"                                        ");	//Clear previous text
	gotoXY(0,2," ");											//Clear previous text
	
	if (userInput == '1')
	{
		int move = 16;
		gotoXY(23,35, "Use the UP\\DOWN arrow keys to move the ship. Space bar to fire. ESC to quit");
		ShowConsoleCursor(false);
		Move_Ship(move);
	}
	else
	{
		int moveX = 35;
		gotoXY(23,35, "Use the Left\\Right arrow keys to move the ship. Space bar to fire. ESC to quit");
		ShowConsoleCursor(false);
		Move_Ship_Horizontally(moveX);
	}
}

void Move_Ship(int move)
{
	int ch, x;

	gotoXY(116, move, "<");
	do
	{
		ch = _getch();
		
		switch(ch) //Replace zero space with space to the left right up or down.
		{

		case UP:
			if(move - 1 > 0) // To keep it from going off the top
			{
				gotoXY(116, move, " ");
				move--;
				gotoXY(116, move, "<");
			}
			break;
		case DOWN:
			if(move + 1 < 35) // Same except off the bottom
			{
				gotoXY(116, move, " ");
				move++;
				gotoXY(116, move, "<");
			}
			break;
		case SPACE: // Fire the missile
			for(x=115;x > 1;x--)
			{
				gotoXY(x,move,"=");
				Sleep(5);
				gotoXY(x,move," ");
				Sleep(5);
			}
			break;
		}
	}while(ch!=ESC); // Quits the program
}

void Move_Ship_Horizontally(int moveX)
{
	
	const int MAX_X = 70;
	int ch, y = 40;
	gotoXY(moveX, y, "^");
	
	do
	{
		ch = _getch();
		
		switch(ch) //Replace zero space with space to the left right up or down.
		{

		case LEFT:
			if( moveX - 1 >= 0) // To keep it from going off the left
			{
				gotoXY(moveX, y, " ");
				--moveX;
				gotoXY(moveX, y, "^");
			}
			break;
			
		case RIGHT:
			if( moveX + 1 <  MAX_X) // To keep it from going off the right
			{
				gotoXY(moveX, y, " ");
				++moveX;
				gotoXY(moveX, y, "^");
			}
			break;
			
		case SPACE: // Fire the missile
			int xBullet = moveX;
			
			for( int i = y - 1; i > -1; --i)		
			{
				gotoXY(xBullet, i, "*");
				Sleep(100);
				gotoXY(xBullet, i, " ");
			}
			break;
		}
	}while(ch!=ESC); // Quits the program
}

void gotoXY(int x, int y) // Positions the cursor
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void gotoXY(int x, int y, string text) // Same but lets you print text at the location 
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << text;
}

void ShowConsoleCursor(bool showFlag)
{
    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set cursor visibility on/off
    SetConsoleCursorInfo(console, &cursorInfo);
}
