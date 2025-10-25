#pragma once

#include <Windows.h>
#include <iostream>
#include "Element.h"
#include <vector>

const int MAIN_WINDOW_WIDTH = 1140; //LV_WIDTH + LV_PADDING_X * 2;
const int MAIN_WINDOW_HEIGHT = 460; //(LV_HEIGHT * 2) + LV_PADDING_Y * 2 + 40;

// CHILD_WINDOW_WIDTH = 400
// CHILD_WINDOW_HEIGHT = 460

const int LV_WIDTH = 740;
const int LV_HEIGHT = 200;
const int LV_PADDING_X = 0;
const int LV_PADDING_Y = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window {
	private:
		HINSTANCE hInstance;
		HWND hwnd;
		HWND listViewHwnd;
		HWND addButtonHwnd;
		HWND editButtonHwnd;
	public:

		// Main window
		
		Window(int WIDTH, int HEIGHT);
		~Window();

		bool ProcessMessages();
		HWND GetHwnd() const { return hwnd; }

		// Main window ListView

		bool InitListView();
		bool InitListViewColumns();
		bool AddListViewItem(Element element);
};

class ChildWindow{
	private:
		HINSTANCE hInstance;
		HWND hwnd;

		std::vector<HWND> CHILD_EDIT_HWNDS;
		std::vector<HWND> CHILD_BTN_HWNDS;
		std::vector<HWND> CHILD_STATIC_HWNDS;

	public:
		ChildWindow(HWND parentHwnd);
		~ChildWindow();
		bool ProcessMessages();
		HWND GetHwnd() const { return hwnd; }
};

