#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
#include "Fps.h"

using namespace std;


#pragma once
class Mine_clearance
{
private: 
	int HIGHT = NULL;
	int WIDTH = NULL;
	int CELL = NULL;
	int CELL_COUNT = NULL;
	int CELL_COUNT_WIDTH = NULL;
	int CELL_COUNT_HIGHT = NULL;
	int BOMB_COUNT = NULL;
	// �����Ѷ�ѡ��
	string difficult_list[5] = { " �ϴ�ѡ��",
		" ����(10*10) [10�ŵ���]",
		" �м�(16*16) [40�ŵ���]",
		" �߼�(30*25) [99�ŵ���]",
		" �汾˵��"
	};
public:
	Mine_clearance();
	void TcharToChar(const TCHAR*, char*);
	void CharToTchar(const char*, TCHAR*);
	wchar_t* stringToTCHAR(const char*);
	char* TCHARToString(LPCTSTR);
	int draw_start();
	void setting(int);
	void draw_game(time_t);
	void draw_gameover();
	void start_game();
};


