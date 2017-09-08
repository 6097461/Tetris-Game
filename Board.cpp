#include <iostream>
#include <windows.h>
#include "Board.h"
using namespace std;

Board::Board()
{
	int i, j;

	for (i = 0; i < 10; i++) 
    {
		for (j = 0; j < 20; j++)
			board_[i][j] = EMPTY;
	}
}

int Board::GetState(Point pos)
{ 
	return board_[pos.GetX()][pos.GetY()]; 
}

void Board::SetState(Point pos, int state) 
{ 
	board_[pos.GetX()][pos.GetY()] = state;	
}

int Board::CheckLineFull(Point reference_pos)
{
	int count = 0;
	for (int i = 0; i < 20; i++)
	{
		int a = 1;
		while (a)
		{
			for (int j = 0; j < 10; j++)
			{
				if (board_[j][i] == EMPTY)
					a = 0;
			}
			if (a == 1)
			{
				Delete(i, reference_pos);
				count++;
	
			}
			
		}
	

	}
	return count;
}
	
	

	void Board::Delete(int hang, Point reference_pos)//라인 삭제함수
	{
		
		for (int j = hang; j < 19; j++)
		{
			Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(0, j)));
			for (int i = 0; i < 10; i++)
			{
				
				board_[i][j] = board_[i][j + 1];
				if (board_[i][j] != EMPTY)
					cout << "■";
				else
				{
					cout << "  ";

				}
			}
		}
		
	}