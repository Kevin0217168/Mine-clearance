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
	void show_map(vector<vector<Cell>>* map);
public:
	Mine_clearance();
	// Tchar转换为Char
	void TcharToChar(const TCHAR*, char*);
	// Char转换为Tchar
	void CharToTchar(const char*, TCHAR*);
	// char转换为TCHAR，支持中文
	wchar_t* stringToTCHAR(const char*);
	// 判断坐标是否落在方格范围内
	inline bool if_pos_in_cell(int x, int y);
	// 通过物理坐标二分查找对应的方块
	inline Cell* choose(vector<vector<Cell>>* map, int x, int y);
	// 生成从MIX到MIN的随机数
	int randint(int min, int max);
	// 洗牌算法
	void shuffle(vector<int>* arr);
	// 初始化雷边方格数字
	void init_bomb_near_block_num(vector<vector<Cell>>* map);
	// 初始化雷区 布雷算法
	void init_Bomb(vector<vector<Cell>>* map, Cell* paichu);
	// 绘制游戏开始界面
	int draw_start();
	// 设置游戏参数
	void setting(int);
	// 绘制游戏界面
	void draw_game(time_t, int, vector<vector<Cell>>*);
	// 绘制游戏结束界面
	void draw_gameover();
	// 游戏开始入口函数
	void start_game();
};
