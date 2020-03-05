#include <iostream>
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
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
	// �����Ѷ�ѡ��
	string difficult_list[5] = { " �ϴ�ѡ��",
	" ����(10*10) [10�ŵ���]",
	" �м�(16*16) [40�ŵ���]",
	" �߼�(30*25) [99�ŵ���]",
	" �汾˵��"
	};

	struct Cell
	{
		// ������к�������
		int pos[2];
		// �����״̬��0:δ��, 1:�Ѵ�, 3:����, 4:����
		int zhuangtai = 0;
		// �Ƿ�Ϊ�ף�0����Ϊ�ף�1��Ϊ��
		int if_lei = 0;
		// ��������ʾ�����֣�������Χ�׵�����
		int num = 0;
	};
	void show_map(vector<vector<Cell>>* map);
public:
	Mine_clearance();
	// Tcharת��ΪChar
	void TcharToChar(const TCHAR*, char*);
	// Charת��ΪTchar
	void CharToTchar(const char*, TCHAR*);
	// charת��ΪTCHAR��֧������
	wchar_t* stringToTCHAR(const char*);
	// �ж������Ƿ����ڷ���Χ��
	inline bool if_pos_in_cell(int x, int y);
	// ͨ������������ֲ��Ҷ�Ӧ�ķ���
	inline Cell* choose(vector<vector<Cell>>* map, int x, int y);
	// ���ɴ�MIX��MIN�������
	int randint(int min, int max);
	// ϴ���㷨
	void shuffle(vector<int>* arr);
	// ��ʼ���ױ߷�������
	void init_bomb_near_block_num(vector<vector<Cell>>* map);
	// ��ʼ������ �����㷨
	void init_Bomb(vector<vector<Cell>>* map, Cell* paichu);
	// ������Ϸ��ʼ����
	int draw_start();
	// ������Ϸ����
	void setting(int);
	// ������Ϸ����
	void draw_game(time_t, int, vector<vector<Cell>>*);
	// ������Ϸ��������
	void draw_gameover();
	// ��Ϸ��ʼ��ں���
	void start_game();
};
