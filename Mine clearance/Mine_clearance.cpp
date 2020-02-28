#include "Mine_clearance.h"

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
	//// �ļ��������򿪻����ļ�
	//FILE* fp;
	//fp = fopen("cache.txt", "r");
	//if (fp != NULL) 
	//{
	//	// �ļ��򿪳ɹ�
	//}
	//else 
	//{
	//	// �ļ���ʧ��

	//}

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

	// �����Ѷ�ѡ��
	string difficult_list[5] = { " �ϴ�ѡ�� ",
		" ����(10*10) [10�ŵ���]",
		" �м�(16*16) [40�ŵ���]",
		" �߼�(30*25) [99�ŵ���]",
		" �汾˵��"
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
				drawtext(AnsiCharToWide((char*)(string(">>") + difficult_list[i]).data()), &draw_choose, DT_LEFT);
			}
			else 
			{
				settextcolor(RGB(112, 161, 255));
				drawtext(AnsiCharToWide((char*)(string("  ") + difficult_list[i]).data()), &draw_choose, DT_LEFT);
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