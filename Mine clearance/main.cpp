#include <iostream>
#include "Mine_clearance.h"


using namespace std;

int main(void)
{
	//initgraph(500, 500);
	//// 定义字符串缓冲区，并接收用户输入
	//TCHAR s[10];
	//InputBox(s, 10, _T("请输入半径"));
	//char a[10];
	//TcharToChar(s, a);
	//cout << atoi(a) + 1 << endl;

	Mine_clearance game;
	cout << game.draw_start();

	return 0;
}