#include <iostream>
#include "Mine_clearance.h"


using namespace std;

int main(void)
{
	//initgraph(500, 500);
	//// �����ַ������������������û�����
	//TCHAR s[10];
	//InputBox(s, 10, _T("������뾶"));
	//char a[10];
	//TcharToChar(s, a);
	//cout << atoi(a) + 1 << endl;

	Mine_clearance game;
	cout << game.draw_start();

	return 0;
}