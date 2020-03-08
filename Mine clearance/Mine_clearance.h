#include <iostream>        // ��׼�������
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>         // �����¼���ȡ
#include <string>          // �ַ�������
#include <tchar.h>         // GuI�ַ���
#include <stdlib.h>        // C�����ڴ��
#include <fstream>         // �ļ��������
#include <ctime>           // Cʱ���
#include <vector>          // ��̬�����
#include "Fps.h"           // ����FPS������
#include <algorithm>       // �㷨��

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
	int CELL_UNOPENED_COUNT = CELL_COUNT;
	int FAILED_BOOL = false;
	// �����Ѷ�ѡ��
	string difficult_list[5] = { " �ϴ�ѡ��",
	" ����(9 * 9) [10�ŵ���]",
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
	// ���캯��
	Mine_clearance();
	// Tcharת��ΪChar
	void TcharToChar(const TCHAR*, char*);
	// Charת��ΪTchar
	void CharToTchar(const char*, TCHAR*);
	// charת��ΪTCHAR��֧������
	wchar_t* stringToTCHAR(const char*);
	// ֧������ת��
	wchar_t* AnsiCharToWide(char* pChar);
	// �ж������Ƿ����ڷ���Χ��
	inline bool if_pos_in_cell(int, int);
	// ͨ������������ֲ��Ҷ�Ӧ�ķ���
	inline Cell* choose(vector<vector<Cell>>*, int, int);
	// ���ɴ�MIX��MIN�������
	int randint(int, int);
	// ϴ���㷨
	void shuffle(vector<int>*);
	// ��ʼ���ױ߷�������
	void init_bomb_near_block_num(vector<vector<Cell>>*);
	// ��ʼ������ �����㷨
	void init_Bomb(vector<vector<Cell>>*, int, int);
	// �ݹ����Χ����
	void click_near_block(vector<vector<Cell>>*, int, int, bool);
	// ������Ϸ��ʼ����
	int draw_start();
	// ������Ϸ����
	void setting(int);
	// �û��Զ�����Ϸ����
	// ÿ�з����� ÿ�з����� ը���� ÿ������Ĵ�С
	void user_setting(int, int, int, int);
	// ������Ϸ����
	void draw_game(time_t, int, vector<vector<Cell>>*);
	// ������Ϸ��������
	void draw_Gameover(TCHAR*, TCHAR*, TCHAR*, TCHAR*, bool);
	// ��Ϸ��ʼ��ں���
	int start_game();
};
