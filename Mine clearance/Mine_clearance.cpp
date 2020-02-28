#include "Mine_clearance.h"

//将TCHAR转为char   
//*tchar是TCHAR类型指针，*_char是char类型指针   
void Mine_clearance::TcharToChar(const TCHAR* tchar, char* _char)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void Mine_clearance::CharToTchar(const char* _char, TCHAR* tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

void Mine_clearance::draw_start()
{
	initgraph(500, 600);
	// 获得窗口句柄
	HWND hWnd = GetHWnd();
	// 使用 API 函数修改窗口名称
	char s[] = "Mine clearance--Difficult to choose";
	TCHAR a[35];
	CharToTchar(s, a);
	SetWindowText(hWnd, a);

	// 设置背景色
	setbkcolor(RGB(206, 214, 224));
	// 标题
	settextcolor(RGB(83, 82, 237));
	settextstyle(50, 0, _T("微软雅黑"));
	static RECT title_rect = { 80, 100, 400,130 };
	drawtext(_T("扫 雷"), &title_rect, DT_CENTER);

	// 难度选择
	settextcolor(RGB(83, 82, 237));
	settextstyle(40, 0, _T("微软雅黑"));
	static RECT title_rect = { 100, 160, 400,200 };
	drawtext(_T("--- 难度选择 ---"), &title_rect, DT_CENTER);
}

