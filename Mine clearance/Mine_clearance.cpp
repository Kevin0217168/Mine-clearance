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

void Mine_clearance::draw_start()
{
	initgraph(500, 600);
	// ��ô��ھ��
	HWND hWnd = GetHWnd();
	// ʹ�� API �����޸Ĵ�������
	char s[] = "Mine clearance--Difficult to choose";
	TCHAR a[35];
	CharToTchar(s, a);
	SetWindowText(hWnd, a);

	// ���ñ���ɫ
	setbkcolor(RGB(206, 214, 224));
	// ����
	settextcolor(RGB(83, 82, 237));
	settextstyle(50, 0, _T("΢���ź�"));
	static RECT title_rect = { 80, 100, 400,130 };
	drawtext(_T("ɨ ��"), &title_rect, DT_CENTER);

	// �Ѷ�ѡ��
	settextcolor(RGB(83, 82, 237));
	settextstyle(40, 0, _T("΢���ź�"));
	static RECT title_rect = { 100, 160, 400,200 };
	drawtext(_T("--- �Ѷ�ѡ�� ---"), &title_rect, DT_CENTER);
}

