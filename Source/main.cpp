#pragma once
#include <Windows.h>
#include <windows.h>
#include "resource.h"
#include "Shape.h"
#include <windowsx.h>
#include "Header.h"
#include <vector>
#include <fstream>
using namespace std;

vector <CShape*> manghinh;
bool check;
POINT diembd;
POINT diemkt;
POINT dichuyen;
CShape* shape = NULL;
Mode type = line;
int style = 0;
int size = 1;
COLORREF color;
BOOL OpenFile(HWND hwnd, WCHAR str[]);
BOOL SaveFile(HWND hwnd, WCHAR str[]);
void saveToBinaryFile(string filePath);
void loadFromBinaryFile(string filePath);
COLORREF MyCreateColor(HWND hwnd)
{
	CHOOSECOLOR cc;
	static COLORREF crCustClr[16];
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)crCustClr;
	cc.rgbResult = RGB(0, 0, 0);
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	ChooseColor(&cc);
	return cc.rgbResult;
}
void VeHinh(POINT& bd,POINT& kt)
{
	if (abs(bd.x - kt.x) > abs(bd.y - kt.y))
	{
		if (bd.x > kt.x)
			kt.x = bd.x - abs(bd.y - kt.y);
		else
			kt.x = bd.x + abs(bd.y - kt.y);
	}
	else
	{
		if (bd.y > kt.y)
			kt.y = bd.y - abs(bd.x - kt.x);
		else
			kt.y = bd.y + abs(bd.x - kt.x);
	}
}

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, int Show)
{
	MSG	msg;
	HWND hwnd;
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Paint";
	wc.hInstance = hIns;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(hIns,MAKEINTRESOURCE(IDI_ICON1));
	RegisterClass(&wc);
	hwnd = CreateWindow(L"Paint", L"Paint", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hIns, NULL);
	ShowWindow(hwnd, Show);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

HPEN pen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HMENU menu;
	static int select = ID_DRAWSHAPE_LINE;
	static WCHAR str[255];
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
					diembd.x = GET_X_LPARAM(lParam);
					diembd.y = GET_Y_LPARAM(lParam);
					shape = Paint::create(type);
					check = true;
					SetCapture(hwnd);
	}
		break;
	case WM_MOUSEMOVE:
	{
						 if (check == true)
						 {
							 dichuyen.x = GET_X_LPARAM(lParam);
							 dichuyen.y = GET_Y_LPARAM(lParam);
							 if (type == rectangle || type == ellipse)
								 if (wParam&MK_SHIFT)							
									VeHinh(diembd,dichuyen);
							 InvalidateRect(hwnd, NULL, FALSE);
						 }
	}
		break;
	case WM_LBUTTONUP:
	{
						 ReleaseCapture();
						 check = false;
						 diemkt.x = GET_X_LPARAM(lParam);
						 diemkt.y = GET_Y_LPARAM(lParam);
						 HPEN pen = CreatePen(style, size, color);
						 HBRUSH brush = GetStockBrush(NULL_BRUSH);
						 shape = Paint::create(type);
						 if (type == rectangle || type == ellipse)
							if (wParam&MK_SHIFT)							
							 		VeHinh(diembd,diemkt);
						 shape->SetData(diembd, diemkt,pen,brush);
						 manghinh.push_back(shape);
						 InvalidateRect(hwnd, NULL, FALSE);
	}
		break;
	case WM_PAINT:
	{
					 hdc = BeginPaint(hwnd, &ps);
					 RECT rect;
					 GetClientRect(hwnd, &rect);
					 HDC hdc1 = CreateCompatibleDC(hdc);
					 HBITMAP bitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
					 SelectObject(hdc1, bitmap);
					 FillRect(hdc1, &rect, (HBRUSH)(COLOR_WINDOW + 1));
					 HPEN pen = CreatePen(style, size, color);
					 SelectObject(hdc1, pen);
					 HBRUSH brush = GetStockBrush(NULL_BRUSH);
					 SelectObject(hdc1, brush);
					 for (int i = 0; i < manghinh.size(); i++)
					 {
						 manghinh[i]->Draw(hdc1);
					 }
					 if (check == true)
					 {
						 HPEN pen = CreatePen(style, size, color);
						 HBRUSH brush = GetStockBrush(NULL_BRUSH);
						 shape->SetData(diembd, dichuyen,pen,brush);
						 shape->Draw(hdc1);
					 }
					 BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdc1, 0, 0, SRCCOPY);
					 EndPaint(hwnd, &ps);
	}
		break;
	case WM_COMMAND:
	{
					   menu = GetMenu(hwnd);
					   int id = LOWORD(wParam);
					   int event = HIWORD(wParam);
					   switch (id)
					   {
					   case ID_FILE_NEW:
						   manghinh.clear();
						   InvalidateRect(hwnd, NULL, TRUE);
						   break;
					   case ID_FILE_OPEN:
						   loadFromBinaryFile("data.bin");
						   InvalidateRect(hwnd, NULL, TRUE);
						   break;
					   case ID_FILE_SAVE:
						  // if (SaveFile(hwnd, str))
							   saveToBinaryFile("data.bin");
						   break;
					   case ID_FILE_EXIT:
						   DestroyWindow(hwnd);
						   break;
					   case ID_EDIT_UNDO:
						   manghinh.pop_back();
						   InvalidateRect(hwnd, NULL, TRUE);
						   break;
					   case ID_EDIT_CLEAR:
						   manghinh.clear();
						   InvalidateRect(hwnd, NULL, TRUE);
					   case ID_DRAWSHAPE_LINE:
						   type = line;
						   break;
					   case ID_DRAWSHAPE_RECTANGLE:
						   type = rectangle;
						   break;
					   case ID_DRAWSHAPE_ELLIPSE:
						   type = ellipse;
						   break;
					   case ID_STYLE_DASH:
						   style = PS_DASH;
						   break;
					   case ID_STYLE_DOT:
						   style = PS_DOT;
						   break;
					   case ID_STYLE_SOLID:
						   style = PS_SOLID;
						   break;
					   case ID_STYLE_DASHDOT:
						   style = PS_DASHDOT;
						   break;
					   case ID_SIZE_1:
						   size = 1;
						   break;
					   case ID_SIZE_2:
						   size = 2;
						   break;
					   case ID_SIZE_3:
						   size = 3;
						   break;
					   case ID_SIZE_4:
						   size = 4;
						   break;
					   case ID_SIZE_5:
						   size = 5;
						   break;
					  case ID_COLOR:
						   color = MyCreateColor(hwnd);
						   break;
					   }
					   CheckMenuItem(menu, select, MF_UNCHECKED);
					   select = LOWORD(wParam);
					   CheckMenuItem(menu, select, MF_CHECKED);

	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

BOOL OpenFile(HWND hwnd, WCHAR str[])
{
	OPENFILENAMEW file = { 0 };
	WCHAR sz[255];
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	file.hwndOwner = hwnd;
	file.lStructSize = sizeof(file);
	file.lpstrFile = sz;
	file.lpstrFile[0] = L'\0';
	file.lpstrFilter = L"image(*.png)\0*.png\0All Files (*.*)\0*.*\0";
	file.nMaxFile = sizeof(sz);
	file.nFilterIndex = 1;
	if (!GetOpenFileName(&file))
		return FALSE;
	wcscpy(str, file.lpstrFile);
	return TRUE;
}
BOOL SaveFile(HWND hwnd, WCHAR str[])
{
	OPENFILENAMEW filename = { 0 };
	WCHAR sz[255] = L"*.png";
	filename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	filename.hwndOwner = hwnd;
	filename.lStructSize = sizeof(filename);
	filename.lpstrFile = sz;
	filename.lpstrFilter = L"image(*.png)\0*.png\0All Files (*.*)\0*.*\0";
	filename.nMaxFile = sizeof(sz);
	filename.nFilterIndex = 1;
	if (!GetSaveFileName(&filename))
		return FALSE;
	wcscpy(str, filename.lpstrFile);
	return TRUE;
}

void saveToBinaryFile(string filePath) 
{
	ofstream out;
	out.open(filePath, std::iostream::out | std::iostream::binary | std::iostream::trunc);
	if (out.is_open()) {
		int kt = manghinh.size();
		out.write(reinterpret_cast<const char *>(&kt), sizeof(kt));
		for (CShape* hinh : manghinh) {
			int loai = hinh->gettype();
			out.write(reinterpret_cast<const char*>(&loai), sizeof(loai));
			/*HPEN but = hinh->getpen();
			out.write(reinterpret_cast<const char*>(&but), sizeof(HPEN));*/
			/*HBRUSH co = hinh->getbrush();
			out.write(reinterpret_cast<const char*>(&co), sizeof(HBRUSH));*/
			RECT* toado = hinh->getPoint();
			out.write(reinterpret_cast<const char*>(toado), sizeof(RECT));
		}
	}
	out.close();
}

void loadFromBinaryFile(string filePath)
{
	ifstream in;
	in.open(filePath, std::iostream::in | std::iostream::binary);

	if (in.is_open()) {
		char* buffer = new char[255];
		int kt;
		in.read(buffer, sizeof(kt));

		kt = buffer[0];
		manghinh.clear();


		for (int i = 0; i < kt; i++)
		{
			char* item_buff = new char[255];

			CShape* shape = NULL;

			int type;
			in.read(item_buff, sizeof(type));
			type = item_buff[0];
			/*COLORREF color;
			in.read(item_buff, sizeof(HPEN));
			int style = item_buff[0];
			int size = item_buff[1];
			color = item_buff[2];
			int r = GetRValue(color);
			color = item_buff[3];
			int g = GetGValue(color);
			color = item_buff[4];
			int b = GetBValue(color);
			color = RGB(r, g, b);
			HPEN pen = CreatePen(style, 1,color);
			*/
			shape = Paint::create((Mode)type);
			RECT* rect;
			in.read(item_buff, sizeof(RECT));
			rect = reinterpret_cast<RECT*>(item_buff);
			POINT bd,kt;
			bd.x = rect->left; bd.y = rect->top; kt.x = rect->right; kt.y = rect->bottom;
			HPEN pen = CreatePen(0, 1, RGB(0,0,0));
			HBRUSH brush = GetStockBrush(NULL_BRUSH);
			shape->SetData(bd,kt,pen,brush);
			manghinh.push_back(shape);

			delete[] item_buff;
			item_buff = NULL;
		}
		delete[] buffer;
	}
	in.close();
}