#include "Mine_clearance.h"

Mine_clearance::Mine_clearance()
{
}


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
	int chage = NULL;
	// 文件操作，打开缓存文件
	ifstream inFile("chage.dll", ios::in);
	if (inFile)
	{
		// 文件打开成功
		// 读取上次选择信息
		inFile >> chage;
	}

	// 初始化绘图窗口
	initgraph(500, 540, SHOWCONSOLE);
	// 获得窗口句柄
	HWND hWnd = GetHWnd();
	// 使用 API 函数修改窗口名称
	char s[] = "Mine clearance--Difficult to choose";
	TCHAR a[36];
	CharToTchar(s, a);
	SetWindowText(hWnd, a);

	// 设置背景色
	setbkcolor(RGB(206, 214, 224));

	if (chage == NULL)
	{
		this->difficult_list[0] += "暂无";
	}
	else 
	{
		this->difficult_list[0] += this->difficult_list[chage].substr(0,12);
	}

	static RECT title_rect = { 80, 50, 420, 130 };
	static RECT difficult_rect = { 100, 160, 400,200 };
	static RECT choose_rect = { 100, 220, 400, 280 };
	static RECT note_rect = { 20, 500, 520, 580 };

	fps_limit* fps = new fps_limit(60);
	int ch;
	RECT draw_choose = choose_rect;
	string title;
	int target = 0;
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
				drawtext(AnsiCharToWide((char*)(string(">>") + this->difficult_list[i]).data()), &draw_choose, DT_LEFT);
			}
			else 
			{
				settextcolor(RGB(112, 161, 255));
				drawtext(AnsiCharToWide((char*)(string("  ") + this->difficult_list[i]).data()), &draw_choose, DT_LEFT);
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
				if (!(target == 0 && chage == NULL)) 
				{
					break;
				}
			}
		}
		FlushBatchDraw();
		fps->delay();
	}
	EndBatchDraw();
	if (target == 0)
	{
		target = chage;
	}
	ofstream outfile("chage.dll", ios::out);
	if (outfile) 
	{
		outfile << target;
	}
	delete fps;
	closegraph();
	return target;
}

void Mine_clearance::setting(int target)
{
	switch (target)
	{
	case 1:
		this->CELL_COUNT_WIDTH = 10;
		this->CELL_COUNT_HIGHT = 10;
		this->CELL_COUNT = 100;
		this->BOMB_COUNT = 10;
		this->CELL = 30;
		break;
	case 2:
		this->CELL_COUNT_WIDTH = 16;
		this->CELL_COUNT_HIGHT = 16;
		this->CELL_COUNT = 256;
		this->BOMB_COUNT = 40;
		this->CELL = 25;
		break;
	case 3:
		this->CELL_COUNT_WIDTH = 30;
		this->CELL_COUNT_HIGHT = 25;
		this->CELL_COUNT = 750;
		this->BOMB_COUNT = 99;
		this->CELL = 20;
		break;
	default:
		// 此处显示游戏说明
		// ...巴拉巴拉
		// 然后返回
		draw_start();
	}
	this->HIGHT = 60 + this->CELL_COUNT_HIGHT * this->CELL + 10;
	this->WIDTH = 20 + this->CELL_COUNT_WIDTH * this->CELL;
}

void Mine_clearance::draw_game(time_t start_seconds, int lei_count, vector<vector<Cell>>* cell_map)
{
	BeginBatchDraw();

	// 绘制背景
	setfillcolor(RGB(206, 214, 224));
	solidrectangle(0, 0, this->WIDTH, this->HIGHT);

	// 绘制游戏区域框
	setfillcolor(BLACK);
	rectangle(10, 60, this->WIDTH - 10, this->HIGHT - 10);

	// 绘制游戏时间
	setfillcolor(BLACK);
	settextstyle(30, 0, _T("微软雅黑"));
	static RECT time_rect = { 20, 10, (this->WIDTH / 2) - 10, 40 };
	long int sub_scoends = time(NULL) - start_seconds;
	string minutes = to_string((int)(sub_scoends / 60));
	string seconds = to_string(sub_scoends % 60);
	drawtext(AnsiCharToWide((char*)(string("时间: ") + minutes + string(" : ") + seconds).data()), &time_rect, DT_LEFT);

	// 绘制游戏剩余雷数
	static RECT lei_rect = { (this->WIDTH / 2) + 10, 10, this->WIDTH - 20, 40 };
	drawtext(AnsiCharToWide((char*)(string("剩余雷数: ") + to_string(lei_count)).data()), &lei_rect, DT_RIGHT);

	// 绘制游戏地图
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	for (vector<vector<Cell>>::iterator y_it = cell_map->begin(); y_it < cell_map->end(); ++y_it)
	{
		for (vector<Cell>::iterator x_it = y_it->begin(); x_it < y_it->end(); ++x_it) 
		{
			if (x_it->zhuangtai)
			{
				// 设置已打开填充色
				setfillcolor(RGB(223, 228, 234));
			}
			else 
			{
				// 设置未打开填充色
				setfillcolor(RGB(55, 66, 250));
			}
			fillrectangle(x_it->pos[0], x_it->pos[1], x_it->pos[0] + this->CELL, x_it->pos[1] + this->CELL);
		}
	}
	EndBatchDraw();
}

inline bool Mine_clearance::if_pos_in_cell(int x, int y) {
	if (x > 10 && x < this->WIDTH - 10) {
		if (y > 60 && y < this->HIGHT - 10) {
			return true;
		}
	}
	return false;
}

inline Mine_clearance::Cell* Mine_clearance::choose(vector<vector<Cell>>* map, int x, int y) {
	// 每行查找
	int max = map->size()-1;
	int min = 0;
	int index;
	while (true) {
		index = (int)((max + min) / 2);
		if ((*map)[index][0].pos[1] <= y && (*map)[index][0].pos[1] + this->CELL > y) {
			break;
		}
		else if ((*map)[index][0].pos[1] > y) {
			max = index - 1;
		}
		else {
			min = index + 1;
		}
	}
	// 每列查找
	max = (*map)[index].size() - 1;
	min = 0;
	int x_index = 0;
	while (true) {
		x_index = (int)((max + min) / 2);
		if ((*map)[index][x_index].pos[0] <= x && (*map)[index][x_index].pos[0] + this->CELL > x) {
			return &(*map)[index][x_index];
		}
		else if ((*map)[index][x_index].pos[0] > x) {
			max = x_index - 1;
		}
		else {
			min = x_index + 1;
		}
	}
}

void Mine_clearance::init_Bomb(vector<vector<Cell>>* map, Cell* paichu) {
	/*for (vector<vector<Cell>>::iterator y_it = map->begin(); y_it < map->size(); ++y_it) {
		for ()
	}*/
}

void Mine_clearance::start_game()
{
	time_t start_seconds;
	start_seconds = time(NULL);
	// 初始化绘图窗口
	initgraph(this->WIDTH, this->HIGHT, SHOWCONSOLE);

	// 设置背景色
	setbkcolor(RGB(206, 214, 224));

	// 构建游戏地图
	vector<vector<Cell>>* cell_map = new vector<vector<Cell>>(this->CELL_COUNT_HIGHT, vector<Cell>(this->CELL_COUNT_WIDTH));
	cout << sizeof(*cell_map) << endl;
	// 初始化游戏地图
	for (int y = 0; y < this->CELL_COUNT_HIGHT; y++) 
	{
		for (int x = 0; x < this->CELL_COUNT_WIDTH; x++) 
		{
			(*cell_map)[y][x].pos[0] = 10 + this->CELL * x;
			(*cell_map)[y][x].pos[1] = 60 + this->CELL * y;
		}
	}

	// 游戏主循环
	int lei_count = this->BOMB_COUNT;
	fps_limit* fps = new fps_limit(200);
	// 清空鼠标消息缓冲
	FlushMouseMsgBuffer();
	while (true)
	{
		draw_game(start_seconds, lei_count, cell_map);

		// 鼠标事件检测
		if (MouseHit()) 
		{
			// 获取鼠标消息
			MOUSEMSG msg = GetMouseMsg();
			// 检测是否在方格范围内
			if (if_pos_in_cell(msg.x, msg.y))
			{
				Cell* cell = choose(cell_map, msg.x, msg.y);
				// 检测是否左键单击
				if (msg.uMsg == WM_LBUTTONDOWN == cell->zhuangtai == 0)
				{
					cell->zhuangtai = 1;
				}
				// 检测是否左键双击
				if (msg.uMsg == WM_LBUTTONDBLCLK && cell->zhuangtai == 1) {
					cout << "double click!" << endl;
				}
				// 检测是否按下右键
				else if (msg.mkRButton) {

				}
			}
			
		}

		fps->delay();
	}
	delete fps;
}