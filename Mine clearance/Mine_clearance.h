#include <iostream>
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include <string>
#include <tchar.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
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

	struct Cell
	{
		// 方格的行和列坐标
		int pos[2];
		// 方格的状态，0:未打开, 1:已打开, 3:插旗, 4:疑问
		int zhuangtai = 0;
		// 是否为雷，0：不为雷，1：为雷
		int if_lei = 0;
		// 方格上显示的数字，代表周围雷的数量
		int num = 0;
	};
public:
	Mine_clearance();
	void TcharToChar(const TCHAR*, char*);
	void CharToTchar(const char*, TCHAR*);
	wchar_t* stringToTCHAR(const char*);
	char* TCHARToString(LPCTSTR);
	inline bool if_pos_in_cell(int x, int y);
	inline Cell* choose(vector<vector<Cell>>* map, int x, int y);
	void init_Bomb(vector<vector<Cell>>* map, Cell* paichu);
	int draw_start();
	void setting(int);
	void draw_game(time_t, int, vector<vector<Cell>>*);
	//void draw_game(time_t, int, vector<vector<Cell>>*);
	void draw_gameover();
	void start_game();
};
