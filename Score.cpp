#include <iostream>
#include <iomanip>
#include<windows.h>//Sleep ÇÔ¼ö
using namespace std;
#include "Score.h"

Score::Score()
{
    score_ = 0;
    score_pos_ = Point(28, 9);
}

void Score::Print(Point reference_pos)
{
    Point::GotoXY(reference_pos + score_pos_);
    cout << "    ";
    Point::GotoXY(reference_pos + score_pos_);
    cout << setw(5) << score_;
}

void Score::UpdateScore(Point reference_pos, int increment)
{	
		score_ += increment;
		Print(reference_pos);
		
}