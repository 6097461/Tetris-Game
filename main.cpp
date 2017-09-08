#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
#include "Tetris.h"
#include <windows.h>
 #include <MMSystem.h>
 #pragma comment(lib, "winmm.lib")
int main()
{
	PlaySound(TEXT("mario.wav"), NULL, SND_ASYNC | SND_LOOP);
	srand(time(NULL));		// ���� �߻��� �ʱ�ȭ
	int input;
	cout << ">>>>>>>> Testris <<<<<<<<" << endl;
	cout << ">> 1�ο�, 2�ο� ���� : ";
	cin >> input;

	system("cls");

	if (input == 1)         // 1�ο� 
    {			
		Tetris tetris(1.0,Point(0, 0));
		tetris.Run();
	}
	else                    // 2�ο�
    {		
		Tetris tetris1(2.0,Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's',KEY_SPACE);
		Tetris tetris2(2.1,Point(38, 0), 'p',KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN,'/');

		while (tetris1.IsRunning() || tetris2.IsRunning()) 
        {
			bool key1 = false;
			bool key2 = false;

			if (kbhit())    // Ű �Է��� �ִٸ� 
            {		
				int key = Controller::GetKey();					
				if (tetris1.IsRunning())
					key1 = tetris1.KeyHandler(key);
				if (tetris2.IsRunning() && !key1)
					key2 = tetris2.KeyHandler(key);				
			}

			if (tetris1.IsRunning() && !key1)
				tetris1.NormalStep();
			if (tetris2.IsRunning() && !key2)
				tetris2.NormalStep();			
		}        
	}

    return 0;
}

/*
int main()
{
	srand(time(NULL));
	Tetris tetris;
	tetris.Run();

    return 0;
}
*/