#include "Mine_clearance.h"

Mine_clearance::Mine_clearance()
{

}


//��TCHARתΪchar   
//*tchar��TCHAR����ָ�룬*_char��char����ָ��   
void Mine_clearance::TcharToChar(const TCHAR* tchar, char* _char)
{
	int iLength;
	//��ȡ�ֽڳ���   
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//��tcharֵ����_char
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void Mine_clearance::CharToTchar(const char* _char, TCHAR* tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

// stringToTCHAR
/* wBuf ����Ϊָ�뼴�ɡ�*/
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
	// �ļ��������򿪻����ļ�
	ifstream inFile("chage.dll", ios::in);
	if (inFile)
	{
		// �ļ��򿪳ɹ�
		// ��ȡ�ϴ�ѡ����Ϣ
		inFile >> chage;
	}

	// ��ʼ����ͼ����
	initgraph(500, 540, SHOWCONSOLE);
	// ��ô��ھ��
	HWND hWnd = GetHWnd();
	// ʹ�� API �����޸Ĵ�������
	char s[] = "Mine clearance--Difficult to choose";
	TCHAR a[35];
	CharToTchar(s, a);
	SetWindowText(hWnd, a);

	// ���ñ���ɫ
	setbkcolor(RGB(206, 214, 224));

	if (chage == NULL)
	{
		this->difficult_list[0] += "����";
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
		// ����
		setfillcolor(RGB(206, 214, 224));
		solidrectangle(0, 0, 500, 550);

		// ����
		settextcolor(RGB(83, 82, 237));
		settextstyle(80, 0, _T("΢���ź�"));
		
		drawtext(_T("ɨ ��"), &title_rect, DT_CENTER);

		// �Ѷ�ѡ��
		settextcolor(RGB(83, 82, 237));
		settextstyle(40, 0, _T("΢���ź�"));
		
		drawtext(_T("--- �Ѷ�ѡ�� ---"), &difficult_rect, DT_CENTER);

		// ����ѡ��
		settextstyle(30, 0, _T("΢���ź�"));
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

		// ����˵��
		settextcolor(RGB(83, 82, 237));
		settextstyle(30, 0, _T("΢���ź�"));
		drawtext(_T("�������¼�ѡ����Ϸ�Ѷȣ��ո��س�ȷ��"), &note_rect, DT_LEFT);

		// �����¼��ж�
		if (_kbhit()) {
			// ���¿ո������
			ch = _getch();
			// �ϣ�72��ѡ���Ϸ�
			if (ch == 72) 
			{
				if (target != 0) 
				{
					target -= 1;
				}
			}
			// �£�80��ѡ���·�
			else if (ch == 80) {
				if (target != 4)
				{
					target += 1;
				}
			}
			// �ո����32��ȷ��
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
		// �˴���ʾ��Ϸ˵��
		// ...��������
		// Ȼ�󷵻�
		draw_start();
	}
	this->HIGHT = 60 + this->CELL_COUNT_HIGHT * this->CELL + 10;
	this->WIDTH = 10 + this->CELL_COUNT_WIDTH * this->CELL;
}

void Mine_clearance::draw_game(time_t start_seconds)
{
	BeginBatchDraw();

	// ���Ʊ���
	setfillcolor(RGB(206, 214, 224));
	solidrectangle(0, 0, this->WIDTH, this->HIGHT);

	// ������Ϸ�����
	setfillcolor(BLACK);
	rectangle(10, 60, this->WIDTH - 10, this->HIGHT - 10);

	// ������Ϸʱ��
	setfillcolor(BLACK);
	settextstyle(30, 0, _T("΢���ź�"));
	static RECT time_rect = { 20, 10, (this->WIDTH / 2) - 10, 40 };
	long int sub_scoends = time(NULL) - start_seconds;
	string minutes = to_string((int)(sub_scoends / 60));
	string seconds = to_string(sub_scoends % 60);
	drawtext(AnsiCharToWide((char*)(string("ʱ��: ") + minutes + string(":") + seconds).data()), &time_rect, DT_LEFT);

	// ������Ϸʣ������


	EndBatchDraw();
}

void Mine_clearance::start_game()
{
	time_t start_seconds;
	start_seconds = time(NULL);
	// ��ʼ����ͼ����
	initgraph(this->WIDTH, this->HIGHT, SHOWCONSOLE);

	// ���ñ���ɫ
	setbkcolor(RGB(206, 214, 224));

	fps_limit* fps = new fps_limit(60);
	while (true) 
	{
		draw_game(start_seconds);
		fps->delay();
	}
	delete fps;
}