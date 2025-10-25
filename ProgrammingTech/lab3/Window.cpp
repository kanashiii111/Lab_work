#include "Window.h"
#include "WinUser.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <iostream>
#include "Element.h"
#include "Windowsx.h"

const long long MAIN_ADD_BTN_ID = 1;
const long long MAIN_EDIT_BTN_ID = 2;

const long long CHILD_URL_EDIT_ID = 3;
const long long CHILD_LOGIN_EDIT_ID = 4;
const long long CHILD_PASS_EDIT_ID = 5;
const long long CHILD_NOTES_EDIT_ID = 6;

const long long CHILD_EDIT_IDS[4] = {
    CHILD_URL_EDIT_ID,
    CHILD_LOGIN_EDIT_ID,
    CHILD_PASS_EDIT_ID,
    CHILD_NOTES_EDIT_ID
};

const long long CHILD_CLOSE_BTN_ID = 7;
const long long CHILD_SAVE_BTN_ID = 8;
const long long CHILD_CANCEL_BTN_ID = 9;
const long long CHILD_GENPASS_BTN_ID = 10;

const long long CHILD_BTN_IDS[4] = {
    CHILD_CLOSE_BTN_ID,
    CHILD_SAVE_BTN_ID,
    CHILD_CANCEL_BTN_ID,
    CHILD_GENPASS_BTN_ID
};

const long long CHILD_STATIC_ID = 11;
const long long CHILD_STATIC_URL_ID = 12;
const long long CHILD_STATIC_LOGIN_ID = 13;
const long long CHILD_STATIC_PASS_ID = 14;
const long long CHILD_STATIC_NOTES_ID = 15;

const long long CHILD_STATIC_IDS[5] = {
    CHILD_STATIC_ID,
    CHILD_STATIC_URL_ID,
    CHILD_STATIC_LOGIN_ID,
    CHILD_STATIC_PASS_ID,
    CHILD_STATIC_NOTES_ID
};

const int buttonPadding = 20;
const int buttonWidth = 100;
const int buttonHeight = 30;

const int childStaticHeight = 20;
const int childStaticWidth = 100;

HWND childHwnd;
HWND mainHwnd;

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

    std::cout << "<--------MAIN WINDOW-------->\n" << std::endl;

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

    if (!hwnd) {
        std::cout << "Window creation : Failure" << std::endl;
        return;
    }
    std::cout << "Window creation : Success" << std::endl;

	mainHwnd = hwnd;

    std::cout << "\nBUTTONS\n" << std::endl;

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

    if (!addButtonHwnd) {
        std::cout << "addButton creation : Failure" << std::endl;
        return;
    }
    std::cout << "addButton creation : Success" << std::endl;

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
            if ((HIWORD(wParam) == BN_CLICKED) && (lParam != 0)) {

                switch (LOWORD(wParam)) {

                case CHILD_CLOSE_BTN_ID:
                    ShowWindow(hwnd, SW_HIDE);
                    break;
                case CHILD_CANCEL_BTN_ID:
                    ShowWindow(hwnd, SW_HIDE);
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

    // EDITS

    HWND urlEditHwnd = NULL;
    HWND loginEditHwnd = NULL;
    HWND passEditHwnd = NULL;
    HWND notesEditHwnd = NULL;

    CHILD_EDIT_HWNDS = { urlEditHwnd, loginEditHwnd, passEditHwnd, notesEditHwnd };

    // BUTTONS

    HWND saveButtonHwnd = NULL;
    HWND cancelButtonHwnd = NULL;
    HWND closeButtonHwnd = NULL;
    HWND genPassButtonHwnd = NULL;

    CHILD_BTN_HWNDS = { saveButtonHwnd, cancelButtonHwnd, closeButtonHwnd, genPassButtonHwnd };

    // STATICS

    HWND staticHwnd = NULL;
    HWND staticUrlHwnd = NULL;
    HWND staticLoginHwnd = NULL;
    HWND staticPassHwnd = NULL;
    HWND staticNotesHwnd = NULL;

    CHILD_STATIC_HWNDS = { staticHwnd, staticUrlHwnd, staticLoginHwnd, staticPassHwnd, staticNotesHwnd };

	// WINDOW CLASS

    WNDCLASS wndClass = { };

    wndClass.lpfnWndProc = ChildWindowProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = CHILD_CLASS_NAME;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wndClass);

    DWORD style = WS_SYSMENU | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER;

    int windowWidth = MAIN_WINDOW_WIDTH - LV_WIDTH;
    int windowHeight = MAIN_WINDOW_HEIGHT;

    // Window

    std::cout << "\n<--------CHILD WINDOW-------->\n" << std::endl;

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

    childHwnd = hwnd; // GLOBAL

    if (!hwnd) {
        std::cout << "Child window creation : Failure" << std::endl;
        return;
    }
    std::cout << "Child window creation : Success" << std::endl;



    std::cout << "\nEDITS\n" << std::endl;



    int CHILD_EDIT_Y_POSITIONS[4] = {
        (windowHeight / 10) * 2,
        (windowHeight / 10) * 3 + 10,
        (windowHeight / 10) * 4 + 20,
        (windowHeight / 10) * 5 + 30
    };

    std::string CHILD_EDIT_DEBUG_NAMES[4] = {
        "URL Edit",
        "Login Edit",
        "Password Edit",
        "Notes Edit"
    };

    for (int i = 0; i < CHILD_EDIT_HWNDS.size(); i++) {
        CHILD_EDIT_HWNDS[i] = CreateWindow(
            L"EDIT",
            L"",
            WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP,
            0,
            CHILD_EDIT_Y_POSITIONS[i],
            buttonWidth * 3,
            buttonHeight,
            hwnd,
            (HMENU)CHILD_EDIT_IDS[i],
            hInstance,
            NULL
        );
        if (!CHILD_EDIT_HWNDS[i]) {
            std::cout << "Edit creation (Name: " << CHILD_EDIT_DEBUG_NAMES[i] << ") : Failure" << std::endl;
            return;
        }
        std::cout << "Edit creation (Name: " << CHILD_EDIT_DEBUG_NAMES[i] << ") : Success" << std::endl;
    }


    std::cout << "\nBUTTONS\n" << std::endl;


    int CHILD_BTN_X_POSITIONS[4] = {
        windowWidth - buttonWidth,
        buttonWidth,
        buttonWidth * 2,
        buttonWidth * 3
    };

    int CHILD_BTN_Y_POSITIONS[4] = {
        0,
        windowHeight - buttonHeight,
        windowHeight - buttonHeight,
        (windowHeight / 10) * 4 + 20
    };

    int CHILD_BTN_WIDTHS[4] = {
        buttonWidth,
        buttonWidth,
        buttonWidth,
        buttonWidth / 2
    };

    int CHILD_BTN_HEIGHTS[4] = {
        buttonHeight,
        buttonHeight,
        buttonHeight,
        buttonHeight
    };

    const wchar_t* CHILD_BTN_WINDOW_NAMES[4] = {
        L"X",
        L"SAVE",
        L"CANCEL",
        L"GEN"
    };

    std::string CHILD_BTN_DEBUG_NAMES[4] = {
        "Close Button",
        "Save Button",
        "Cancel Button",
        "Generate Password Button"
    };

    for (int i = 0; i < CHILD_BTN_HWNDS.size(); i++) {
        CHILD_BTN_HWNDS[i] = CreateWindow(
            L"BUTTON",
            CHILD_BTN_WINDOW_NAMES[i],
            WS_BORDER | WS_TABSTOP | WS_VISIBLE | WS_CHILD,
            CHILD_BTN_X_POSITIONS[i],
            CHILD_BTN_Y_POSITIONS[i],
            CHILD_BTN_WIDTHS[i],
            CHILD_BTN_HEIGHTS[i],
            hwnd,
            (HMENU)CHILD_BTN_IDS[i],
            hInstance,
            NULL
        );
        if (!CHILD_BTN_HWNDS[i]) {
            std::cout << "Edit creation (Name: " << CHILD_BTN_DEBUG_NAMES[i] << ") : Failure" << std::endl;
            return;
        }
        std::cout << "Edit creation (Name: " << CHILD_BTN_DEBUG_NAMES[i] << ") : Success" << std::endl;
    }



    std::cout << "\nSTATICS\n" << std::endl;



    int CHILD_STATIC_X_POSITIONS[5] = {
        0,
        0,
        0,
        0,
        0
    };

    int CHILD_STATIC_Y_POSITIONS[5] = {
        0,
        ((windowHeight / 10) * 2) - 20,
        ((windowHeight / 10) * 3) - 10,
        ((windowHeight / 10) * 4),
        ((windowHeight / 10) * 5) + 10
    };

    int CHILD_STATIC_WIDTHS[5] = {
        buttonWidth,
        childStaticWidth,
        childStaticWidth,
        childStaticWidth,
        childStaticWidth
    };

    int CHILD_STATIC_HEIGHTS[5] = {
        buttonHeight,
        childStaticHeight,
        childStaticHeight,
        childStaticHeight,
        childStaticHeight
    };

    const wchar_t* CHILD_STATIC_WINDOW_NAMES[5] = {
        L"New Login",
        L"URL",
        L"LOGIN",
        L"PASSWORD",
        L"NOTES"
    };

    std::string CHILD_STATIC_DEBUG_NAMES[5] = {
        "Window static",
        "URL static",
        "Login static",
        "Password static",
        "Notes static"
    };

    for (int i = 0; i < CHILD_STATIC_HWNDS.size(); i++) {
        CHILD_STATIC_HWNDS[i] = CreateWindow(
            L"STATIC",
            CHILD_STATIC_WINDOW_NAMES[i],
            WS_BORDER | SS_CENTER | WS_VISIBLE | WS_CHILD,
            CHILD_STATIC_X_POSITIONS[i],
            CHILD_STATIC_Y_POSITIONS[i],
            CHILD_STATIC_WIDTHS[i],
            CHILD_STATIC_HEIGHTS[i],
            hwnd,
            (HMENU)CHILD_STATIC_IDS[i],
            hInstance,
            NULL
        );
        if (!CHILD_STATIC_HWNDS[i]) {
            std::cout << "Static creation (Name: " << CHILD_STATIC_DEBUG_NAMES[i] << ") : Failure" << std::endl;
            return;
        }
        std::cout << "Static creation (Name: " << CHILD_STATIC_DEBUG_NAMES[i] << ") : Success" << std::endl;
    }
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