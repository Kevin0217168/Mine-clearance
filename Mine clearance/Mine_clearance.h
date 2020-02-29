#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <string>
#include <fstream>
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
public:
	Mine_clearance();
	void TcharToChar(const TCHAR*, char*);
	void CharToTchar(const char*, TCHAR*);
	wchar_t* stringToTCHAR(const char*);
	char* TCHARToString(LPCTSTR);
	int draw_start();
	void setting(int);
	void draw_game();
	void draw_gameover();
	void start_game();
};


