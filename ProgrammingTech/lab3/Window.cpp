#include "Window.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <iostream>
#include "Element.h"

const int ADD_BTN_ID = 1;
const int EDIT_BTN_ID = 2;

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
                case ADD_BTN_ID:
					std::cout << "Add button clicked" << std::endl;
                    break;

                case EDIT_BTN_ID:
					std::cout << "Edit button clicked" << std::endl;
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
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

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

    // add button

	int buttonPadding = 20;
    int buttonWidth = 100;
    int buttonHeight = 30;

    addButtonHwnd = CreateWindow(
        L"BUTTON",
        L"Add",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        LV_WIDTH - buttonPadding - buttonWidth,
        MAIN_WINDOW_HEIGHT - buttonHeight - buttonPadding,
        buttonWidth,
        buttonHeight,
        hwnd,
		(HMENU)ADD_BTN_ID,
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
        (HMENU)EDIT_BTN_ID,
        hInstance,
        NULL
    );

    if (hwnd && addButtonHwnd && editButtonHwnd) {
        ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);
    }
}

Window::~Window() {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
	UnregisterClass(CLASS_NAME, hInstance);
}

bool Window::ProcessMessages() {
    MSG msg = { };

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
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
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

ChildWindow::ChildWindow(HWND parentHwnd)
    : hInstance(GetModuleHandle(nullptr))
{
    const wchar_t CHILD_CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wndClass = { };

    wndClass.lpfnWndProc = ChildWindowProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = CHILD_CLASS_NAME;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wndClass);

    DWORD style = WS_CAPTION | WS_SYSMENU | WS_CHILD;

    int width = MAIN_WINDOW_WIDTH - LV_WIDTH;
    int height = MAIN_WINDOW_HEIGHT;

    hwnd = CreateWindowExW(
        0,
        CHILD_CLASS_NAME,
        L"Child Window",
        style,
        LV_WIDTH,
        0,
        width,
        height,
        parentHwnd,
        NULL,
        hInstance,
        NULL
    );
    if (hwnd) {
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
    }
}

ChildWindow::~ChildWindow() {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    UnregisterClass(CLASS_NAME, hInstance);
}
