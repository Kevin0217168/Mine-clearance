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

// stringToTCHAR
/* wBuf 申明为指针即可。*/
wchar_t* Mine_clearance::stringToTCHAR(const char* buffer)
{
	size_t len = strlen(buffer);
	size_t wlen = MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), NULL, 0);
	wchar_t* wBuf = new wchar_t[wlen + 1];
	MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), wBuf, int(wlen));
	return wBuf;
}
//char* Mine_clearance::TCHARToString(LPCTSTR lpString)
//{
//	UINT len = wcslen(lpString) * 2;
//	char* buf = (char*)malloc(len);
//	UINT i = wcstombs(buf, lpString, len);
//	return buf;
//}
wchar_t* AnsiCharToWide(char* pChar)
{
	if (!pChar) return NULL;
	wchar_t* pszBuf = NULL;
	int needWChar = MultiByteToWideChar(CP_ACP, 0, pChar, -1, NULL, 0);
	if (needWChar > 0) {
		pszBuf = new wchar_t[needWChar + 1];
		ZeroMemory(pszBuf, (needWChar + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, pChar, -1, pszBuf, needWChar);
	}

	return pszBuf;
}

int Mine_clearance::draw_start()
{
	//// 文件操作，打开缓存文件
	//FILE* fp;
	//fp = fopen("cache.txt", "r");
	//if (fp != NULL) 
	//{
	//	// 文件打开成功
	//}
	//else 
	//{
	//	// 文件打开失败

	//}

	// 初始化绘图窗口
	initgraph(500, 540, SHOWCONSOLE);
	// 获得窗口句柄
	HWND hWnd = GetHWnd();
	// 使用 API 函数修改窗口名称
	char s[] = "Mine clearance--Difficult to choose";
	TCHAR a[35];
	CharToTchar(s, a);
	SetWindowText(hWnd, a);

	// 设置背景色
	setbkcolor(RGB(206, 214, 224));

	// 设置难度选项
	string difficult_list[5] = { " 上次选择 ",
		" 初级(10*10) [10颗地雷]",
		" 中级(16*16) [40颗地雷]",
		" 高级(30*25) [99颗地雷]",
		" 版本说明"
	};

	static RECT title_rect = { 80, 50, 420, 130 };
	static RECT difficult_rect = { 100, 160, 400,200 };
	static RECT choose_rect = { 100, 220, 400, 280 };
	static RECT note_rect = { 20, 500, 520, 580 };

	fps_limit* fps = new fps_limit(60);
	int ch;
	int target = 0;
	RECT draw_choose = choose_rect;
	string title;
	BeginBatchDraw();
	while (true) {
		// 背景
		setfillcolor(RGB(206, 214, 224));
		solidrectangle(0, 0, 500, 550);

		// 标题
		settextcolor(RGB(83, 82, 237));
		settextstyle(80, 0, _T("微软雅黑"));
		
		drawtext(_T("扫 雷"), &title_rect, DT_CENTER);

		// 难度选择
		settextcolor(RGB(83, 82, 237));
		settextstyle(40, 0, _T("微软雅黑"));
		
		drawtext(_T("--- 难度选择 ---"), &difficult_rect, DT_CENTER);

		// 绘制选项
		settextstyle(30, 0, _T("微软雅黑"));
		for (int i = 0; i < 5; i++) 
		{
			draw_choose.top += 50 * i;
			draw_choose.bottom += 50 * i;
			if (i == target)
			{
				settextcolor(RGB(55, 66, 250));
				drawtext(AnsiCharToWide((char*)(string(">>") + difficult_list[i]).data()), &draw_choose, DT_LEFT);
			}
			else 
			{
				settextcolor(RGB(112, 161, 255));
				drawtext(AnsiCharToWide((char*)(string("  ") + difficult_list[i]).data()), &draw_choose, DT_LEFT);
			}
			draw_choose = choose_rect;
		}

		// 绘制说明
		settextcolor(RGB(83, 82, 237));
		settextstyle(30, 0, _T("微软雅黑"));
		drawtext(_T("键盘上下键选择游戏难度，空格或回车确认"), &note_rect, DT_LEFT);

		// 键盘事件判断
		if (_kbhit()) {
			// 按下空格键继续
			ch = _getch();
			// 上：72，选项上翻
			if (ch == 72) 
			{
				if (target != 0) 
				{
					target -= 1;
				}
				
			}
			// 下：80，选项下翻
			else if (ch == 80) {
				if (target != 4)
				{
					target += 1;
				}
			}
			// 空格键：32，确定
			else if (ch == 32)
			{
				break;
			}
		}
		FlushBatchDraw();
		fps->delay();
	}
	EndBatchDraw();
	delete fps;
	closegraph();
	return target;
}