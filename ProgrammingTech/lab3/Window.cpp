#include "Window.h"
#include "WinUser.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <iostream>
#include "Element.h"
#include "Windowsx.h"

const long long MAIN_ADD_BTN_ID = 1;
const long long MAIN_EDIT_BTN_ID = 2;

const long long CHILD_EDIT_ID = 3;
const long long CHILD_TEST_BTN_ID = 4;

const int buttonPadding = 20;
const int buttonWidth = 100;
const int buttonHeight = 30;

HWND childHwnd;
HWND mainHwnd;
HWND test;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_COMMAND:
        {
            if ((HIWORD(wParam) == BN_CLICKED) && (lParam != 0))
            {
                switch (LOWORD(wParam))
                {
                case MAIN_ADD_BTN_ID:
                    ShowWindow(childHwnd, SW_SHOW);
                    //UpdateWindow(childHwnd);
                    break;

                case MAIN_EDIT_BTN_ID:
                    break;
                }
            }
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(int WIDTH, int HEIGHT)
    : hInstance(GetModuleHandle(nullptr))
{
    const wchar_t CLASS_NAME[] = L"Main Window";

	listViewHwnd = NULL;
	addButtonHwnd = NULL;
	editButtonHwnd = NULL;

    WNDCLASS wndClass = { };

    wndClass.lpfnWndProc = WindowProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    int width = WIDTH;
    int height = HEIGHT;

    RECT rect{};
	rect.left = 100;
    rect.top = 100;
    rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, FALSE);

    // Main window

    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Main Window",
        style,
        rect.left, 
        rect.top,
        rect.right - rect.left, 
        rect.bottom - rect.top,
        NULL,
        NULL,
        hInstance,
        NULL
    );

	mainHwnd = hwnd;

    // add button

    addButtonHwnd = CreateWindow(
        L"BUTTON",
        L"Add",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        LV_WIDTH - buttonPadding - buttonWidth,
        MAIN_WINDOW_HEIGHT - buttonHeight - buttonPadding,
        buttonWidth,
        buttonHeight,
        hwnd,
		(HMENU)MAIN_ADD_BTN_ID,
        hInstance,
		NULL
    );

    // edit button

    editButtonHwnd = CreateWindow(
        L"BUTTON",
        L"Edit",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        LV_WIDTH - ((buttonWidth + buttonPadding) * 2),
        MAIN_WINDOW_HEIGHT - buttonHeight - buttonPadding,
        buttonWidth,
        buttonHeight,
        hwnd,
        (HMENU)MAIN_EDIT_BTN_ID,
        hInstance,
        NULL
    );


    if (!hwnd) {
        std::cout << "Window creation : Failure" << std::endl;
        return;
    }
    std::cout << "Window creation : Success" << std::endl;

    if (!addButtonHwnd) {
        std::cout << "addButton creation : Failure" << std::endl;
        return;
    }
    std::cout << "addButton creation : Success" << std::endl;

    if (!editButtonHwnd) {
        std::cout << "editButton creation : Failure" << std::endl;
        return;
    }
    std::cout << "editButton creation : Success" << std::endl;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

Window::~Window() {
    const wchar_t CLASS_NAME[] = L"Main Window";
	UnregisterClass(CLASS_NAME, hInstance);
}

bool Window::ProcessMessages() {
    MSG msg = { };

    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
    {
        if (msg.message == WM_QUIT || msg.message == WM_DESTROY) {
			return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

bool Window::InitListView() {
	HWND parentHwnd = Window::GetHwnd();
    listViewHwnd = CreateWindow(
        WC_LISTVIEW,
        L"ListView",
		WS_CHILD | WS_VISIBLE | LVS_REPORT,
        LV_PADDING_X,
        LV_PADDING_Y,
        LV_WIDTH,
        LV_HEIGHT,
        parentHwnd,
        NULL,
        hInstance,
        NULL
	);

    if (!listViewHwnd) {
		std::cout << "Error creating ListView" << std::endl;
        return false;
    }

    ListView_SetExtendedListViewStyle(listViewHwnd,
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	std::cout << "InitListView : Success" << std::endl;
    return true;
}

bool Window::InitListViewColumns()
{
    const struct { const wchar_t* text; int width; } columns[] = {
        {L"URL", 200},
        {L"Login", 150},
        {L"Password", 150},
        {L"Notes", 240}
    };

    for (int i = 0; i < 4; i++) {
        LVCOLUMN lvCol = { };
        lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
        lvCol.fmt = LVCFMT_CENTER;
        lvCol.cx = columns[i].width;
		lvCol.iSubItem = i;
        lvCol.pszText = (LPWSTR)columns[i].text;
        if (ListView_InsertColumn(listViewHwnd, i, &lvCol) == -1) {
			std::cout << "Error inserting column " << i << std::endl;
            return false;
        }
    }
	std::cout << "InitListViewColumns : Success" << std::endl;
    return true;
}

bool Window::AddListViewItem(Element element) {
    LVITEM lvItem = { };
    lvItem.mask = LVIF_TEXT;

	std::string url = element.get_url();
    std::string login = element.get_login();
    std::string password = element.get_password();
    std::string notes = element.get_notes();

	std::wstring wUrl(url.begin(), url.end());
    std::wstring wLogin(login.begin(), login.end());
    std::wstring wPassword(password.begin(), password.end());
    std::wstring wNotes(notes.begin(), notes.end());

    // url

    lvItem.iItem = ListView_GetItemCount(listViewHwnd);
	lvItem.pszText = &wUrl[0];
    if (ListView_InsertItem(listViewHwnd, &lvItem) == -1) {
        std::cout << "Error inserting ListView item. URL" << std::endl;
        return false;
    }

    // login

    lvItem.iSubItem = 1;
	lvItem.pszText = &wLogin[0];
    if (ListView_SetItem(listViewHwnd, &lvItem) == -1) {
        std::cout << "Error inserting ListView item. LOGIN" << std::endl;
        return false;
    }

    // password

    lvItem.iSubItem = 2;
    lvItem.pszText = &wPassword[0];
    if (ListView_SetItem(listViewHwnd, &lvItem) == -1) {
        std::cout << "Error inserting ListView item. password" << std::endl;
        return false;
    }

    // notes

    lvItem.iSubItem = 3;
    lvItem.pszText = &wNotes[0];
    if (ListView_SetItem(listViewHwnd, &lvItem) == -1) {
        std::cout << "Error inserting ListView item. notes" << std::endl;
        return false;
    }

 
	std::cout << "Added ListView item: " << url << ", " << login << ", " << password << ", " << notes << std::endl;
    return true;
}

LRESULT CALLBACK ChildWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        return 0;
    case WM_CLOSE:
        ShowWindow(hwnd, SW_HIDE);
        return 0;
    case WM_COMMAND:
        {
            if ((HIWORD(wParam) == BN_CLICKED) && (lParam != 0))
            {
                switch (LOWORD(wParam))
                {
                case CHILD_TEST_BTN_ID:
					std::cout << "Test button clicked in Child Window" << std::endl;
                    break;
                }
            }
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

ChildWindow::ChildWindow(HWND parentHwnd)
    : hInstance(GetModuleHandle(nullptr))
{
    const wchar_t CHILD_CLASS_NAME[] = L"Child Window";

    passEditHwnd = NULL;
    testHwnd = NULL;

    WNDCLASS wndClass = { };

    wndClass.lpfnWndProc = ChildWindowProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = CHILD_CLASS_NAME;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wndClass);

    DWORD style = WS_CAPTION | WS_SYSMENU | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    int windowWidth = MAIN_WINDOW_WIDTH - LV_WIDTH;
    int windowHeight = MAIN_WINDOW_HEIGHT;

    hwnd = CreateWindowExW(
        0,
        CHILD_CLASS_NAME,
        L"Child Window",
        style,
        LV_WIDTH,
        0,
        windowWidth,
        windowHeight,
        parentHwnd,
        NULL,
        hInstance,
        NULL
    );

	childHwnd = hwnd;

    if (!hwnd) {
		std::cout << "\nChild window creation : Failure" << std::endl;
        return;
    }
    std::cout << "\nChild window creation : Success" << std::endl;

    passEditHwnd = CreateWindow(
        L"EDIT",
        L"jjjj",
        WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP,
        (windowWidth / 2) - (buttonWidth / 2),
        (windowHeight / 4) * 3,
        buttonWidth,
        buttonHeight,
        hwnd,
        (HMENU)CHILD_EDIT_ID,
        hInstance,
        NULL
    );

    test = passEditHwnd;

    testHwnd = CreateWindow(
        L"BUTTON",
        L"test",
        WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD,
        (windowWidth / 2) - (buttonWidth / 2),
        windowHeight / 2,
        buttonWidth,
        buttonHeight,
        hwnd,
        (HMENU)4,
        hInstance,
        NULL
    );

    if (!passEditHwnd) {
        std::cout << "passEdit creation : Failure" << std::endl;
        return;
    }
    std::cout << "passEdit creation : Success" << std::endl;

    if (!testHwnd) {
        std::cout << "testHwnd creation : Failure" << std::endl;
        return;
    }
    std::cout << "testHwnd creation : Success" << std::endl;
}

bool ChildWindow::ProcessMessages() {
    MSG msg = { };

    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

ChildWindow::~ChildWindow() {
    const wchar_t CLASS_NAME[] = L"Child Window";
    UnregisterClass(CLASS_NAME, hInstance);
}