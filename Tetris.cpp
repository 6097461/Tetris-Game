#include "Tetris.h"
#include "Controller.h"
#include "Tetromino.h"
//#include "GhostTetromino.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

Tetris::Tetris(double number,Point reference_pos, int key_esc, int key_right, int key_left, int key_rotate, int key_down, int key_space) : reference_pos_(reference_pos) 
{ 
	tetrisnumber_ = number;
	running_ = true; 
    cur_tetromino_ = NULL;
    next_tetromino_ = NULL;
    start_time_ = clock();
    falling_speed_ = 0.8;

    SetCursorInvisible();

    controller_.SetController(key_esc, key_right, key_left, key_rotate, key_down, key_space);
    DrawBoard();
    GenerateNextTetromino();
    GetCurTetrominoFromNext();
    GenerateNextTetromino();
    cur_tetromino_->Draw(reference_pos_);
    next_tetromino_->Draw(reference_pos_);		
    score_.Print(reference_pos_);
}

void Tetris::DrawBoard(void)
{
    int i;
	Point::GotoXY(reference_pos_);
           cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";
   
	for(i=1;i<22;i++)
	{
		if(i==21)
		{
			 Point::GotoXY(reference_pos_+ Point(0, i));
           cout << "▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦";
		}
		else if(i==7||i==11)
		{
			 Point::GotoXY(reference_pos_+ Point(0, i));
			 cout<<"▦                    ▦▦▦▦▦▦▦▦";
		}
		else
		{
			Point::GotoXY(reference_pos_+ Point(0, i));
			 cout<<"▦                    ▦            ▦";
		}

		}
	if (tetrisnumber_ == 1.0)
	{
		Point::GotoXY(reference_pos_ + Point(25, 12));
		cout << "R: → ";
		Point::GotoXY(reference_pos_ + Point(25, 14));
		cout << "L: ←";
		Point::GotoXY(reference_pos_ + Point(25, 16));
		cout << "ROTATE: ↑";
		Point::GotoXY(reference_pos_ + Point(25, 18));
		cout << "DOWN:↓";
		Point::GotoXY(reference_pos_ + Point(25, 20));
		cout << "DROP: space";
	}
	else if (tetrisnumber_ == 2.0)
	{
		Point::GotoXY(reference_pos_ + Point(25, 12));
		cout << "R: d ";
		Point::GotoXY(reference_pos_ + Point(25, 14));
		cout << "L: a";
		Point::GotoXY(reference_pos_ + Point(25, 16));
		cout << "ROTATE: w";
		Point::GotoXY(reference_pos_ + Point(25, 18));
		cout << "DOWN:s";
		Point::GotoXY(reference_pos_ + Point(25, 20));
		cout << "DROP: space";
	}
	else if (tetrisnumber_ == 2.1)
	{
		Point::GotoXY(reference_pos_ + Point(25, 12));
		cout << "R: → ";
		Point::GotoXY(reference_pos_ + Point(25, 14));
		cout << "L: ←";
		Point::GotoXY(reference_pos_ + Point(25, 16));
		cout << "ROTATE: ↑";
		Point::GotoXY(reference_pos_ + Point(25, 18));
		cout << "DOWN:↓";
		Point::GotoXY(reference_pos_ + Point(25, 20));
		cout << "DROP: /";
	}
}


void Tetris::Run(void)
{
    while (running_) 
    {
        RunStep();
    }
}

void Tetris::RunStep(void)
{
    if (kbhit()) 
    {
        int key = Controller::GetKey();
        KeyHandler(key);
    }
    else 
    {
        NormalStep();		
    }
}

bool Tetris::KeyHandler(int key)
{
    if (key == controller_.Getkey_esc()) 
    {
        running_ = false;
        return true;
    }
    else if (key == controller_.Getkey_right()) 
    {
        cur_tetromino_->MoveRight(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_left()) 
    {
        cur_tetromino_->MoveLeft(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_rotate()) 
    {
        cur_tetromino_->Rotate(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_down()) 
    {
        cur_tetromino_->MoveDown(reference_pos_);
      
        return true;
    }
	else if (key == controller_.Getkey_space())
	{
		cur_tetromino_->GoBottom(reference_pos_);
		PrepareNextStep();
		
		return true;
	}

    return false;
}

void Tetris::NormalStep(void)
{
    if (GetDiffTime() >= falling_speed_) 
    {
        if (cur_tetromino_->MoveDown(reference_pos_)) 
        {
            start_time_ = clock();
        }
        else 
        {	// 끝까지 내려왔음. 후처리
            PrepareNextStep();
						
        }
    }
}

void Tetris::PrepareNextStep(void)
{
	static int a = 0;
    cur_tetromino_->MarkCurTetrominoPos(reference_pos_);
    
    int EraseLineCount = board_.CheckLineFull(reference_pos_); 
    
	if (EraseLineCount == 1 || EraseLineCount>4)
	{
		score_.UpdateScore(reference_pos_, EraseLineCount );
	}
	else if (EraseLineCount==2)
	{
		score_.UpdateScore(reference_pos_, EraseLineCount+20);
		Point::GotoXY(reference_pos_ + Point(9, 9));
		cout << "BONUS+20!!";
		Sleep(2000);
		Point::GotoXY(reference_pos_ + Point(9, 9));
		cout << "          ";
	}
	else if (EraseLineCount == 3)
	{
		score_.UpdateScore(reference_pos_, EraseLineCount + 30);
		Point::GotoXY(reference_pos_ + Point(9, 9));
		cout << "BONUS+30!!";
		Sleep(2000);
		Point::GotoXY(reference_pos_ + Point(9, 9));
		cout << "          ";
	}
	else if (EraseLineCount == 4)
	{
		score_.UpdateScore(reference_pos_, EraseLineCount+50);
		Point::GotoXY(reference_pos_ + Point(9, 9));
		cout << "BONUS+50!!";
		Sleep(2000);
		Point::GotoXY(reference_pos_ + Point(9, 9));
		cout << "          ";
	}//점수계산방법변동
	if (score_.scor() >=30 &&a==0)
	{
		Point::GotoXY(reference_pos_ + Point(2,9));
		cout << "last stage~speed up!";
		Sleep(3000);
		Point::GotoXY(reference_pos_ + Point(2,9));
		cout << "                    ";
		falling_speed_ = 0.4;
		a = 1;
	}
	 
	 if (score_.scor() >= 60)
	{
		running_ = false;
		Point::GotoXY(reference_pos_ + Point(10, 10));
		cout << "stage clear !!!";
		getch();

	}//스테이지
	
	    if (cur_tetromino_->CheckEndCondition()) 
    {
        running_ = false;
        Point::GotoXY(reference_pos_ + Point(10, 10));
        cout << "The game is over !!!";
        getch();
    }
    else 
    {
        next_tetromino_->Tetromino::Erase(reference_pos_);		
        GetCurTetrominoFromNext();
        cur_tetromino_->Draw(reference_pos_);
        GenerateNextTetromino();
        next_tetromino_->Draw(reference_pos_);
    }
    start_time_ = clock();
}

void Tetris::GenerateNextTetromino(void)
{
    TETROMINO_TYPE tetromino_type = (TETROMINO_TYPE) (rand() % TETROMINO_TYPE_COUNT);
    //if (rand() % 10 == 0)           // GhostTetromino
    //    next_tetromino_ = new GhostTetromino(&board_, tetromino_type);
    //else
    next_tetromino_ = new Tetromino(&board_, tetromino_type);
    next_tetromino_->SetCenterPos(g_next_tetromino_init_pos);
	
}

void Tetris::GetCurTetrominoFromNext(void)
{
	if (cur_tetromino_ != NULL)
		delete cur_tetromino_;// cur_tetromino_의 값이 NULL이 아니라면 delete
	cur_tetromino_ = next_tetromino_;
    // next_tetromino_의 테트로미노를 cur_tetromino_로 가져옴
	cur_tetromino_->SetCenterPos(g_cur_tetromino_init_pos);
    // cur_tetromino_의 시작 위치 setting    

}

double Tetris::GetDiffTime(void)
{
    clock_t CurTime;
    CurTime = clock();	//time(&CurTime);
    return ((double) (CurTime - start_time_) / CLOCKS_PER_SEC);
}

// Utility
void Tetris::SetCursorInvisible(void)	// 화면 커서를 안 보이게 함
{
    CONSOLE_CURSOR_INFO ci = { 10, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

