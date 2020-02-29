#include <graphics.h>      // 引用图形库头文件
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
	// 设置难度选项
	string difficult_list[5] = { " 上次选择",
		" 初级(10*10) [10颗地雷]",
		" 中级(16*16) [40颗地雷]",
		" 高级(30*25) [99颗地雷]",
		" 版本说明"
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


