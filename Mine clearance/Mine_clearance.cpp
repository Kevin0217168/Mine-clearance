#include "Mine_clearance.h"

// 开始界面背景颜色 比浅灰色再浅一点
#define CHOOSE_BG_COLOR RGB(206, 214, 224) 
// 开始界面大标题颜色 
#define CHOOSE_TITLE_COLOR RGB(83, 82, 237)
// 开始界面选中时颜色
#define CHOOSE_SELECTED_COLOR RGB(55, 66, 250)
// 开始界面未选中时颜色
#define CHOOSE_UNSELECTED_COLOR RGB(112, 161, 255)
// 游戏背景颜色 浅灰色
#define GAME_BG_COLOR RGB(223, 228, 234)
// 未打开方块颜色 蓝
#define UNOPEND_BLOCK_COLOR RGB(55, 66, 250)
// 已打开方块颜色 比浅灰色再深一点
#define OPENED_BLOCK_COLOR RGB(223, 228, 234)
// 游戏页面文字颜色
#define GAME_FONT_COLOR BLACK

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
	setbkcolor(CHOOSE_BG_COLOR);

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
		setfillcolor(CHOOSE_BG_COLOR);
		solidrectangle(0, 0, 500, 550);

		// 标题
		settextcolor(CHOOSE_TITLE_COLOR);
		settextstyle(80, 0, _T("微软雅黑"));
		
		drawtext(_T("扫 雷"), &title_rect, DT_CENTER);

		// 难度选择
		settextcolor(CHOOSE_TITLE_COLOR);
		settextstyle(40, 0, _T("微软雅黑"));
		
		drawtext(_T("--- 难度选择 ---"), &difficult_rect, DT_CENTER);

		// 绘制选项
		settextstyle(30, 0, _T("微软雅黑"));
		for (int i = 0; i < 5; i++) 
		{
			draw_choose.top += 50 * i;
			draw_choose.bottom += 50 * i;
			// 选择上时
			if (i == target)
			{
				settextcolor(CHOOSE_SELECTED_COLOR);
				drawtext(AnsiCharToWide((char*)(string(">>") + this->difficult_list[i]).data()), &draw_choose, DT_LEFT);
			}
			// 未选择上时
			else 
			{
				settextcolor(CHOOSE_UNSELECTED_COLOR);
				drawtext(AnsiCharToWide((char*)(string("  ") + this->difficult_list[i]).data()), &draw_choose, DT_LEFT);
			}
			draw_choose = choose_rect;
		}

		// 绘制说明
		settextcolor(CHOOSE_TITLE_COLOR);
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
	setfillcolor(CHOOSE_BG_COLOR);
	solidrectangle(0, 0, this->WIDTH, this->HIGHT);

	// 绘制游戏区域框
	setfillcolor(GAME_FONT_COLOR);
	rectangle(10, 60, this->WIDTH - 10, this->HIGHT - 10);

	// 绘制游戏时间
	settextcolor(GAME_FONT_COLOR);
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
			if (x_it->zhuangtai != 0)
			{
				switch (x_it->zhuangtai)
				{
				case 1:
					if (x_it->if_lei){
						// 雷
						setfillcolor(RED);
					}
					else {
						// 设置已打开填充色
						setfillcolor(OPENED_BLOCK_COLOR);
					}
					break;
				case 2:
					// 插旗
					setfillcolor(BLUE);
					break;
				case 3:
					// 疑问
					setfillcolor(GREEN);
					break;
				default:
					break;
				}
			}
			else 
			{
				// 设置未打开填充色
				setfillcolor(UNOPEND_BLOCK_COLOR);
			}
			fillrectangle(x_it->pos[0], x_it->pos[1], x_it->pos[0] + this->CELL, x_it->pos[1] + this->CELL);
			// 绘制周围雷数量
			if (x_it->zhuangtai == 1 && x_it->num)
			{
				// 设置背景色
				setbkcolor(GAME_BG_COLOR);
				settextcolor(BLUE);
				settextstyle(this->CELL / 2 + 8, 0, _T("微软雅黑"));
				TCHAR s[2];
				CharToTchar(to_string(x_it->num).data(), s);
				RECT num_rect = { x_it->pos[0] + 2, x_it->pos[1] + 2, x_it->pos[0] + this->CELL - 2, x_it->pos[1] + this->CELL - 2 };
				drawtext(s, &num_rect, DT_CENTER);
			}
		}
	}
	EndBatchDraw();
}

// 判断坐标是否落在方格范围内
inline bool Mine_clearance::if_pos_in_cell(int x, int y) {
	if (x > 10 && x < this->WIDTH - 10) {
		if (y > 60 && y < this->HIGHT - 10) {
			return true;
		}
	}
	return false;
}

// 通过物理坐标二分查找对应的方块
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

// 生成从MIX到MIN的随机数(不包含MAX)
int Mine_clearance::randint(int beg, int end) {
	srand(time(NULL));
	return (rand() % (end - beg)) + beg;
}

// 洗牌算法
void Mine_clearance::shuffle(vector<int>* arr)
{
	for (int i = arr->size() - 1; i >= 0; --i)
	{
		srand((unsigned)time(NULL));
		swap((*arr)[rand() % (i + 1)], (*arr)[i]);
	}
}

// 初始化雷区
void Mine_clearance::init_Bomb(vector<vector<Cell>>* map, Cell* paichu) {
	// 创建一个与地图数量一致的一维数组，用于布雷
	vector<int>* bomb_list = new vector<int>(this->CELL_COUNT_HIGHT * this->CELL_COUNT_WIDTH);
	// 将待布的雷都放在数组前
	for (int index = 0; index < this->BOMB_COUNT; index++) {
		(*bomb_list)[index] = 1;
	}
	// 打乱数组实现布雷
	shuffle(bomb_list);
	// 将分好雷的一维数组埋进二维数组里
	for (int y = 0; y < map->size(); y++) {
		for (int x = 0; x < (*map)[y].size(); x++) {
			if ((*bomb_list)[y * this->CELL_COUNT_WIDTH + x]) {
				(*map)[y][x].if_lei = (*bomb_list)[y * this->CELL_COUNT_WIDTH + x];
			}
		}
	}
	delete bomb_list;
	// 排除用户点下的方块一个方块内的雷
	if (paichu->if_lei) {
		int x, y;
		do {
			x = randint(0, this->CELL_COUNT_WIDTH);
			y = randint(0, this->CELL_COUNT_HIGHT);
		} while ((*map)[y][x].if_lei);
		paichu->if_lei = 0;
		(*map)[y][x].if_lei = 1;
	}
	// 遍历所有非雷方块，为方块填上数字
	init_bomb_near_block_num(map);
}

// 初始化雷边方格数字
void Mine_clearance::init_bomb_near_block_num(vector<vector<Cell>>* map) {
	// 遍历整个地图
	for (int y = 0; y < map->size(); y++) {
		for (int x = 0; x < (*map)[y].size(); x++) {
			// 如果该方格上有雷
			if ((*map)[y][x].if_lei) {
				// 遍历该方块周围的八个方块
				for (int i_y = 1; i_y >= -1; i_y--) {
					for (int i_x = 1; i_x >= -1; i_x--) {
						// 通过相对坐标计算出实际坐标
						int index_y = y - i_y;
						int index_x = x - i_x;
						// 判断坐标是否在地图范围内，并且不是雷
						if (!(i_y == 0 && i_x == 0) && index_y < this->CELL_COUNT_HIGHT && index_y >= 0 && index_x < this->CELL_COUNT_WIDTH && index_x >= 0 && (*map)[index_y][index_x].if_lei == 0) {
							// 将此方格的周围雷数+1
							(*map)[index_y][index_x].num += 1;
						}
					}
				}
			}
		}
	}
}

// 递归打开周围格子
void Mine_clearance::click_near_block(vector<vector<Cell>>* map, int y_b, int x_b) {
	
	if ((*map)[y_b][x_b].num != 0 || (*map)[y_b][x_b].zhuangtai == 1) {
		(*map)[y_b][x_b].zhuangtai = 1;
		return;
	}
	(*map)[y_b][x_b].zhuangtai = 1;
	for (int y = 1; y >= -1; y--) {
		for (int x = 1; x >= -1; x--) {
			int index_x = x_b - x;
			int index_y = y_b - y;
			// 判断坐标是否在地图范围内
			if (!(y == 0 && x == 0) && index_y < this->CELL_COUNT_HIGHT && index_y >= 0 && index_x < this->CELL_COUNT_WIDTH && index_x >= 0) {
				click_near_block(map, index_y, index_x);
			}
		}
	}
}

void Mine_clearance::show_map(vector<vector<Cell>>* map){
	// 遍历整个地图
	for (int y = 0; y < map->size(); y++) {
		for (int x = 0; x < (*map)[y].size(); x++) {
			if ((*map)[y][x].if_lei) {
				cout << "# ";
			}
			else if ((*map)[y][x].num){
				cout << (*map)[y][x].num << " ";
			}
			else {
				cout << "  ";
			}
		}
		cout << endl;
	}
}

void Mine_clearance::start_game()
{
	time_t start_seconds;
	start_seconds = time(NULL);
	// 初始化绘图窗口
	initgraph(this->WIDTH, this->HIGHT, SHOWCONSOLE);

	// 设置背景色
	setbkcolor(GAME_BG_COLOR);

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
	bool first_left = true;
	// 清空鼠标消息缓冲
	FlushMouseMsgBuffer();
	while (true)
	{
		// 绘制游戏界面并刷新
		draw_game(start_seconds, lei_count, cell_map);

		// 鼠标事件检测
		if (MouseHit()) 
		{
			// 获取鼠标消息
			MOUSEMSG msg = GetMouseMsg();
			// 检测是否在方格范围内
			if (if_pos_in_cell(msg.x, msg.y))
			{
				// 通过坐标查找出方块对象
				Cell* cell = choose(cell_map, msg.x, msg.y);
				// 检测是否左键单击
				if (msg.uMsg == WM_LBUTTONDOWN && cell->zhuangtai == 0)
				{
					// 如果为第一次点开方块，则开始布雷
					if (first_left) {
						init_Bomb(cell_map, cell);
						show_map(cell_map);
						first_left = false;
					}
					// 点击此方块，并递归查找周围可打开的方块打开
					click_near_block(cell_map, (int)((cell->pos[1] - 60) / this->CELL), (int)((cell->pos[0] - 10) / this->CELL));
				}
				// 检测是否左键双击
				if (msg.uMsg == WM_LBUTTONDBLCLK && cell->zhuangtai == 1) {
					cout << "double click!" << endl;
					click_near_block(cell_map, (int)((cell->pos[1] - 60) / this->CELL), (int)((cell->pos[0] - 10) / this->CELL));
				}
				// 检测是否按下右键，并且该方块未开启
				else if (msg.uMsg == WM_RBUTTONDOWN && cell->zhuangtai != 1) {
					// 进行插旗动作
					cell->zhuangtai += 1;
					if (cell->zhuangtai == 1) {
						cell->zhuangtai += 1;
					}
					else if (cell->zhuangtai == 4) {
						cell->zhuangtai = 0;
					}
				}
			}
			
		}
		// 控制Fps
		fps->delay();
	}
	delete fps;
}