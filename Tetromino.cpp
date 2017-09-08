#include "Tetromino.h"
#include <iostream>
#include <windows.h>
using namespace std;

Point g_tetromino_pattern[7][4][4] =
{
    { { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) } },  // I
    { { Point(0, 1), Point(0, 0), Point(0, -1), Point(-1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, 1) },
      { Point(0, 1), Point(0, 0), Point(1, 1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(1, -1) } },  // J
    { { Point(-1, 1), Point(0, 1), Point(0, 0), Point(0, -1) }, { Point(1, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(0, -1), Point(1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, -1) } }, // L
    { { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) },
      { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) } },  // O
    { { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) },
      { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) } },  // S
    { { Point(0, 1), Point(-1, 0), Point(0, 0), Point(0, -1) }, { Point(0, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(0, -1) } },  // T
    { { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) },
      { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) } }  // Z
};

Tetromino::Tetromino(Board *board, TETROMINO_TYPE type) : board_(board), type_(type)
{
    rotate_ = 0;
}

void Tetromino::Draw(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
	{
		Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		if ((center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() < 20)
		{

			if (type_ == TETROMINO_I)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "■";
			}
			else if (type_ == TETROMINO_J)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "■";
			}
			else if (type_ == TETROMINO_O)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
				cout << "■";
			}
			else if (type_ == TETROMINO_Z)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "■";
			}
			else if (type_ == TETROMINO_S)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_INTENSITY);
				cout << "■";
			}
			else if (type_ == TETROMINO_T)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE |FOREGROUND_INTENSITY);
				cout << "■";
			}
			else if (type_ == TETROMINO_L)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE |FOREGROUND_INTENSITY);
				cout << "■";
			}
		}
		
	
	}


}

void Tetromino::Erase(Point reference_pos)
{
	for(int i=0;i<4;i++)
	{
	Point::GotoXY(reference_pos+Point::GetScrPosFromCurPos(center_pos_+g_tetromino_pattern[type_][rotate_][i]));
		if((center_pos_+g_tetromino_pattern[type_][rotate_][i]).GetY() < 20)
			cout<<" ";
	}
}

void Tetromino::SetCenterPos(Point pos)
{
    center_pos_ = pos;
}

bool Tetromino::MoveDown(Point reference_pos)
{
	center_pos_.SetY(center_pos_.GetY() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		Erase(reference_pos);
		center_pos_.SetY(center_pos_.GetY() - 1);
		Draw(reference_pos);
		return true;
		
	}
	else
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		return false;
	}
    return true;
}

void Tetromino::MoveRight(Point reference_pos)
{
    center_pos_.SetX(center_pos_.GetX() + 1);

    if (CheckValidPos())
    {
        center_pos_.SetX(center_pos_.GetX() - 1);
        Erase(reference_pos);
        center_pos_.SetX(center_pos_.GetX() + 1);
        Draw(reference_pos);
    }
    else
    {
        center_pos_.SetX(center_pos_.GetX() - 1);
    }
}

void Tetromino::MoveLeft(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() - 1);

	if (CheckValidPos())
	  {
		center_pos_.SetX(center_pos_.GetX() + 1);
		Erase(reference_pos);
		center_pos_.SetX(center_pos_.GetX() - 1);
		Draw(reference_pos);
		}
	else
	{

		center_pos_.SetX(center_pos_.GetX() + 1);
	}

}

void Tetromino::Rotate(Point reference_pos)
{
	int temp = rotate_;
	Point temp_center = center_pos_;
	rotate_ = (rotate_ + 1) % ROTATE_COUNT;

	if (CheckValidPos())
	{
		rotate_ = temp;
		Erase(reference_pos);
		rotate_ = (rotate_ + 1) % ROTATE_COUNT;
		Draw(reference_pos);
	}
	else                                              
	{
		rotate_ = temp;
		MoveLeft(reference_pos);
		if (center_pos_.GetX() == temp_center.GetX())   
		{
			MoveRight(reference_pos);
			if (type_== 0)	//테트로미노 아이						
				MoveRight(reference_pos);
			Rotate(reference_pos);
		}
		else
			Rotate(reference_pos);
	}
}

void Tetromino::GoBottom(Point reference_pos)
{
    while (MoveDown(reference_pos))
    {
        Sleep(10);
    }
}

bool Tetromino::CheckValidPos(void)
{
    for (int i = 0; i < 4; i++)
    {
        Point cur_pos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

        if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
            return false;
        if (cur_pos.GetY() < 0)
            return false;
        if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
            return false;
    }

    return true;
}

void Tetromino::MarkCurTetrominoPos(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
		{
			board_->SetState(center_pos_ + g_tetromino_pattern[type_][rotate_][i], 1);

		}// board_ 2차원 배열에서 테트로미노의 4개의 각 점 위치를 mark하기
    
}

bool Tetromino::CheckEndCondition(void)
{
	for (int i = 0; i < 4; i++)
	{

		if (center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY() >= 20)
			return true;
	}
	return false;
   
}
