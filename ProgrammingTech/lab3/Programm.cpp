#include <iostream>
#include "Window.h"
#include "Element.h"
#include <commctrl.h>
#include "framework.h"
#include "resource.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {

    // DEBUG

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    // Main Window init

    Window *pMainWindow = new Window(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
	pMainWindow->InitListView();
	pMainWindow->InitListViewColumns();
    std::cout << "\n";

    Element* pElement1 = new Element("https://example.com", "user1", "password", "Sample notes 1");
	Element* pElement2 = new Element("https://another.com", "user2", "mypassword", "Sample notes 2");
    std::cout << "\n";

	pMainWindow->AddListViewItem(*pElement1);
	pMainWindow->AddListViewItem(*pElement2);

    // Child Window init

	ChildWindow* pChildWindow = new ChildWindow(pMainWindow->GetHwnd());

	// Main loop

    bool running = true;
    while (running) {
        running = pMainWindow->ProcessMessages();
        Sleep(10);
    }
    delete pMainWindow;

    // DEBUG

    if (f) fclose(f);
    FreeConsole();

    return 0;
}


