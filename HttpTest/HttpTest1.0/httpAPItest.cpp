
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
//使用socket2.2版本
#pragma comment(lib,"ws2_32.lib") 
//web库1.0
#pragma comment(lib,"WEB.lib") 
//#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
Web web;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//判断消息ID
	switch (uMsg){

	case WM_DESTROY:    // 窗口销毁消息
		PostQuitMessage(0);   //  发送退出消息
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
							MessageBox(hwnd, "请填写Http请求接口", 0, 0);
							return DefWindowProc(hwnd, uMsg, wParam, lParam);
						}
						SendMessage(hwndEdit1, 12, 0, (LPARAM)"");
							//获取http接口
							SendMessage(hwndEdit, WM_GETTEXT, 1024, (LPARAM)Http);
							//判断选中状态来调用post和get
							if (SendMessage(hwndButton1, BM_GETCHECK, 0, 0) == BST_CHECKED){
								//获取post数据
								SendMessage(hwndEdit3, WM_GETTEXT, 1024, (LPARAM)Post);
								//提交
								GetHttp = web.Post(Http, Post);
								if (GetHttp == NULL){
									MessageBox(hwnd, "错误，无法提交Post请求", 0, 0);
								}
								
							}
							else{
								GetHttp = web.Get(Http);
								if (GetHttp == NULL){
									MessageBox(hwnd, "错误，无法提交Gost请求", 0, 0);
								}
							}
							//打印数据
							//判断头是否选中
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
	// 其他的消息调用缺省的消息处理程序
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}
// 3、注册窗口类型
BOOL RegisterWindow(LPCSTR lpcWndName, HINSTANCE hInstance)
{
	ATOM nAtom = 0;
	// 构造创建窗口参数
	WNDCLASS wndClass = { 0 };
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowProc;      // 指向窗口过程函数
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = lpcWndName;    // 注册的窗口名称，并非标题，以后创建窗口根据此注册的名称创建
	nAtom = RegisterClass(&wndClass);
	return TRUE;
}
//创建窗口（lpClassName 一定是已经注册过的窗口类型）
HWND CreateMyWindow(LPCTSTR lpClassName, HINSTANCE hInstance)
{
	HWND hWnd = NULL;
	// 创建窗口
	hWnd = CreateWindow(lpClassName, "HTTP接口测试工具", WS_OVERLAPPEDWINDOW, 0, 0, 418, 600, NULL, NULL, hInstance, NULL);
	//创建标签
	CreateWindow("static", "HTTP接口", WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/, 1, 0, 400, 41, hWnd, NULL, hInstance, NULL);
	CreateWindow("static", "POST请求数据", WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/, 400, 0, 180, 41, hWnd, NULL, hInstance, NULL);
	CreateWindow("static", "返回信息", WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/, 1, 200, 400, 41, hWnd, NULL, hInstance, NULL);
	CreateWindow("static", "端口：", WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/, 1, 140, 41, 21, hWnd, NULL, hInstance, NULL);
	CreateWindow("static", "请求方法：", WS_CHILD /*子窗口*/ | WS_VISIBLE /*创建时显示*/ | WS_BORDER /*带边框*/ | SS_CENTER /*水平居中*/ | SS_CENTERIMAGE /*垂直居中*/, 80, 140, 80, 21, hWnd, NULL, hInstance, NULL);
	//创建编辑框
	hwndEdit = CreateWindow("EDIT", "www.baidu.com/member.php?mod=logging&action=login&loginsubmit=yes&loginhash=LZKvG&inajax=1", WS_VISIBLE | WS_CHILD | WS_BORDER/*|DT_CENTER*/ | DT_VCENTER, 1, 40, 400, 80, hWnd, NULL, hInstance, NULL);
	hwndEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER/*|DT_CENTER*/ | DT_VCENTER, 1, 241, 400, 315, hWnd, NULL, hInstance, NULL);
	hwndEdit2 = CreateWindow("EDIT", "80", WS_VISIBLE | WS_CHILD | WS_BORDER/*|DT_CENTER*/ | DT_VCENTER, 41, 140, 31, 21, hWnd, NULL, hInstance, NULL);
	hwndEdit3 = CreateWindow("EDIT", "mod=logging&action=login&loginsubmit=yes&loginhash=LZKvG&inajax=1", WS_VISIBLE | WS_CHILD | WS_BORDER/*|DT_CENTER*/ | DT_VCENTER, 400, 40, 180, 80, hWnd, NULL, hInstance, NULL);
	//创建按钮
	hwndButton = CreateWindow("BUTTON", "Send", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 130, 165, 100, 30, hWnd, (HMENU)1, hInstance, NULL);
	hwndButton1 = CreateWindow("BUTTON", "POST", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP | WS_BORDER /*带边框*/, 161, 140, 80, 21, hWnd, (HMENU)20, hInstance, NULL);
	hwndButton2 = CreateWindow("BUTTON", "GET", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON  | WS_BORDER /*带边框*/, 245, 140, 80, 21, hWnd, (HMENU)21, hInstance, NULL);
	hwndButton3 = CreateWindow("BUTTON", "GetHand", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_BORDER /*带边框*/,325, 140, 80, 21, hWnd, (HMENU)22, hInstance, NULL);
	SendMessage(hwndButton2, BM_SETCHECK, BST_CHECKED, 0);//设置选中
	SendMessage(hwndButton3, BM_SETCHECK, BST_CHECKED, 0);//设置选中
	return hWnd;
}
//显示窗口
void DisplayMyWnd(HWND hWnd)
{
	//获得屏幕尺寸

	int scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT rect;
	GetWindowRect(hWnd, &rect);
	ShowWindow(hWnd, SW_SHOW);
	//重新设置rect里的值
	rect.left = (scrWidth - rect.right) / 2;
	rect.top = (scrHeight - rect.bottom) / 2;
	//移动窗口到指定的位置
	SetWindowPos(hWnd, HWND_TOP, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);
	UpdateWindow(hWnd);
}

void doMessage()        // 消息循环处理函数
{
	MSG msg = { 0 };
	// 获取消息
	while (GetMessage(&msg, NULL, 0, 0)) // 当接收到WM_QIUT消息时，GetMessage函数返回0，结束循环
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); // 派发消息，到WindowPro函数处理
	}
}

// 入口函数
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	HWND hWnd = NULL;
	LPCTSTR lpClassName = "MyWnd";  // 注册窗口的名称
	RegisterWindow(lpClassName, hInstance);
	hWnd = CreateMyWindow(lpClassName, hInstance);
	DisplayMyWnd(hWnd);
	doMessage();
	return 0;
}

