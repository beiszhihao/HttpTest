
#include "Web.h"
#include <windows.h>
HWND hWnd;	//progman
HWND hwndButton;	//button
HWND hwndButton1;	//button
HWND hwndButton2;	//button
HWND hwndButton3;	//button
HWND hwndEdit;	//edit
HWND hwndEdit1;	//edit
HWND hwndEdit2;	//edit
HWND hwndEdit3;	//edit
//socket:
//ʹ��socket2.2�汾
#pragma comment(lib,"ws2_32.lib") 
//web��1.0
#pragma comment(lib,"WEB.lib") 
//#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
Web web;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//�ж���ϢID
	switch (uMsg){

	case WM_DESTROY:    // ����������Ϣ
		PostQuitMessage(0);   //  �����˳���Ϣ
		return 0;
	case WM_COMMAND:{
						char Http[1024] = { 0 };
						char Post[1024] = { 0 };
						char Debug[256] = { 0 };
						char *GetHttp = NULL;
						switch (LOWORD(wParam))
						{
						case 1:
						SendMessage(hwndEdit, WM_GETTEXT, 1024, (LPARAM)Debug);
						if (strlen(Debug) <= 0){
							MessageBox(hwnd, "����дHttp����ӿ�", 0, 0);
							return DefWindowProc(hwnd, uMsg, wParam, lParam);
						}
						SendMessage(hwndEdit1, 12, 0, (LPARAM)"");
							//��ȡhttp�ӿ�
							SendMessage(hwndEdit, WM_GETTEXT, 1024, (LPARAM)Http);
							//�ж�ѡ��״̬������post��get
							if (SendMessage(hwndButton1, BM_GETCHECK, 0, 0) == BST_CHECKED){
								//��ȡpost����
								SendMessage(hwndEdit3, WM_GETTEXT, 1024, (LPARAM)Post);
								//�ύ
								GetHttp = web.Post(Http, Post);
								if (GetHttp == NULL){
									MessageBox(hwnd, "�����޷��ύPost����", 0, 0);
								}
								
							}
							else{
								GetHttp = web.Get(Http);
								if (GetHttp == NULL){
									MessageBox(hwnd, "�����޷��ύGost����", 0, 0);
								}
							}
							//��ӡ����
							//�ж�ͷ�Ƿ�ѡ��
							if (SendMessage(hwndButton3, BM_GETCHECK, 0, 0) == BST_CHECKED){
								SendMessage(hwndEdit1, 12, 0, (LPARAM)web.GetRecvData());
								return DefWindowProc(hwnd, uMsg, wParam, lParam);
							}
							SendMessage(hwndEdit1, 12, 0, (LPARAM)GetHttp);
							break;
						case 20:{
									SetWindowPos(hwnd, NULL, 0, 0, 600, 600, SWP_NOMOVE);
									break;
						}
						case 21:{
									SetWindowPos(hwnd, NULL, 0, 0, 418, 600, SWP_NOMOVE);
						}
							break;
						}
	}

	}
	// ��������Ϣ����ȱʡ����Ϣ�������
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}
// 3��ע�ᴰ������
BOOL RegisterWindow(LPCSTR lpcWndName, HINSTANCE hInstance)
{
	ATOM nAtom = 0;
	// ���촴�����ڲ���
	WNDCLASS wndClass = { 0 };
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowProc;      // ָ�򴰿ڹ��̺���
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = lpcWndName;    // ע��Ĵ������ƣ����Ǳ��⣬�Ժ󴴽����ڸ��ݴ�ע������ƴ���
	nAtom = RegisterClass(&wndClass);
	return TRUE;
}
//�������ڣ�lpClassName һ�����Ѿ�ע����Ĵ������ͣ�
HWND CreateMyWindow(LPCTSTR lpClassName, HINSTANCE hInstance)
{
	HWND hWnd = NULL;
	// ��������
	hWnd = CreateWindow(lpClassName, "HTTP�ӿڲ��Թ���", WS_OVERLAPPEDWINDOW, 0, 0, 418, 600, NULL, NULL, hInstance, NULL);
	//������ǩ
	CreateWindow("static", "HTTP�ӿ�", WS_CHILD /*�Ӵ���*/ | WS_VISIBLE /*����ʱ��ʾ*/ | WS_BORDER /*���߿�*/ | SS_CENTER /*ˮƽ����*/ | SS_CENTERIMAGE /*��ֱ����*/, 1, 0, 400, 41, hWnd, NULL, hInstance, NULL);
	CreateWindow("static", "POST��������", WS_CHILD /*�Ӵ���*/ | WS_VISIBLE /*����ʱ��ʾ*/ | WS_BORDER /*���߿�*/ | SS_CENTER /*ˮƽ����*/ | SS_CENTERIMAGE /*��ֱ����*/, 400, 0, 180, 41, hWnd, NULL, hInstance, NULL);
	CreateWindow("static", "������Ϣ", WS_CHILD /*�Ӵ���*/ | WS_VISIBLE /*����ʱ��ʾ*/ | WS_BORDER /*���߿�*/ | SS_CENTER /*ˮƽ����*/ | SS_CENTERIMAGE /*��ֱ����*/, 1, 200, 400, 41, hWnd, NULL, hInstance, NULL);
	CreateWindow("static", "�˿ڣ�", WS_CHILD /*�Ӵ���*/ | WS_VISIBLE /*����ʱ��ʾ*/ | WS_BORDER /*���߿�*/ | SS_CENTER /*ˮƽ����*/ | SS_CENTERIMAGE /*��ֱ����*/, 1, 140, 41, 21, hWnd, NULL, hInstance, NULL);
	CreateWindow("static", "���󷽷���", WS_CHILD /*�Ӵ���*/ | WS_VISIBLE /*����ʱ��ʾ*/ | WS_BORDER /*���߿�*/ | SS_CENTER /*ˮƽ����*/ | SS_CENTERIMAGE /*��ֱ����*/, 80, 140, 80, 21, hWnd, NULL, hInstance, NULL);
	//�����༭��
	hwndEdit = CreateWindow("EDIT", "www.baidu.com/member.php?mod=logging&action=login&loginsubmit=yes&loginhash=LZKvG&inajax=1", WS_VISIBLE | WS_CHILD | WS_BORDER/*|DT_CENTER*/ | DT_VCENTER, 1, 40, 400, 80, hWnd, NULL, hInstance, NULL);
	hwndEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER/*|DT_CENTER*/ | DT_VCENTER, 1, 241, 400, 315, hWnd, NULL, hInstance, NULL);
	hwndEdit2 = CreateWindow("EDIT", "80", WS_VISIBLE | WS_CHILD | WS_BORDER/*|DT_CENTER*/ | DT_VCENTER, 41, 140, 31, 21, hWnd, NULL, hInstance, NULL);
	hwndEdit3 = CreateWindow("EDIT", "mod=logging&action=login&loginsubmit=yes&loginhash=LZKvG&inajax=1", WS_VISIBLE | WS_CHILD | WS_BORDER/*|DT_CENTER*/ | DT_VCENTER, 400, 40, 180, 80, hWnd, NULL, hInstance, NULL);
	//������ť
	hwndButton = CreateWindow("BUTTON", "Send", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 130, 165, 100, 30, hWnd, (HMENU)1, hInstance, NULL);
	hwndButton1 = CreateWindow("BUTTON", "POST", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP | WS_BORDER /*���߿�*/, 161, 140, 80, 21, hWnd, (HMENU)20, hInstance, NULL);
	hwndButton2 = CreateWindow("BUTTON", "GET", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON  | WS_BORDER /*���߿�*/, 245, 140, 80, 21, hWnd, (HMENU)21, hInstance, NULL);
	hwndButton3 = CreateWindow("BUTTON", "GetHand", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_BORDER /*���߿�*/,325, 140, 80, 21, hWnd, (HMENU)22, hInstance, NULL);
	SendMessage(hwndButton2, BM_SETCHECK, BST_CHECKED, 0);//����ѡ��
	SendMessage(hwndButton3, BM_SETCHECK, BST_CHECKED, 0);//����ѡ��
	return hWnd;
}
//��ʾ����
void DisplayMyWnd(HWND hWnd)
{
	//�����Ļ�ߴ�

	int scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT rect;
	GetWindowRect(hWnd, &rect);
	ShowWindow(hWnd, SW_SHOW);
	//��������rect���ֵ
	rect.left = (scrWidth - rect.right) / 2;
	rect.top = (scrHeight - rect.bottom) / 2;
	//�ƶ����ڵ�ָ����λ��
	SetWindowPos(hWnd, HWND_TOP, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);
	UpdateWindow(hWnd);
}

void doMessage()        // ��Ϣѭ��������
{
	MSG msg = { 0 };
	// ��ȡ��Ϣ
	while (GetMessage(&msg, NULL, 0, 0)) // �����յ�WM_QIUT��Ϣʱ��GetMessage��������0������ѭ��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); // �ɷ���Ϣ����WindowPro��������
	}
}

// ��ں���
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	HWND hWnd = NULL;
	LPCTSTR lpClassName = "MyWnd";  // ע�ᴰ�ڵ�����
	RegisterWindow(lpClassName, hInstance);
	hWnd = CreateMyWindow(lpClassName, hInstance);
	DisplayMyWnd(hWnd);
	doMessage();
	return 0;
}

