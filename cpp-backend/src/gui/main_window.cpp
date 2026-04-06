#include "gui/main_window.h"
#include "gui/home_page.h"
#include "gui/ui_utils.h"
#include <commctrl.h>
#include <sstream>

#pragma comment(lib, "comctl32.lib")

namespace AICreator {
namespace GUI {

// Static window map for message routing
static MainWindow* g_mainWindow = nullptr;

MainWindow::MainWindow()
    : hwnd_(nullptr), hInstance_(GetModuleHandleW(nullptr)), current_page_(0) {
    g_mainWindow = this;
}

MainWindow::~MainWindow() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
    }
}

bool MainWindow::initialize() {
    // Register window class
    const wchar_t* CLASS_NAME = L"AICreatorMainWindow";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = MainWindow::windowProc;
    wc.hInstance = hInstance_;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(UIUtils::COLOR_DARK_BG);
    wc.style = CS_VREDRAW | CS_HREDRAW;

    if (!RegisterClassW(&wc)) {
        return false;
    }

    // Create main window
    hwnd_ = CreateWindowExW(
        0,
        CLASS_NAME,
        L"AI Creator - Intelligent AI Generation Platform",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1200, 800,
        nullptr, nullptr,
        hInstance_,
        nullptr
    );

    if (!hwnd_) {
        return false;
    }

    // Create UI elements
    createMenuBar();
    createToolbar();
    createPages();
    createStatusBar();

    return true;
}

void MainWindow::show() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_SHOW);
        UpdateWindow(hwnd_);
    }
}

void MainWindow::hide() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_HIDE);
    }
}

void MainWindow::close() {
    if (hwnd_) {
        PostMessageW(hwnd_, WM_CLOSE, 0, 0);
    }
}

void MainWindow::showHomePage() {
    if (home_page_) {
        home_page_->show();
    }
    current_page_ = 0;
}

void MainWindow::showDashboardPage() {
    if (dashboard_page_) {
        dashboard_page_->show();
    }
    current_page_ = 1;
}

void MainWindow::showCreateAIPage() {
    if (create_ai_page_) {
        create_ai_page_->show();
    }
    current_page_ = 2;
}

void MainWindow::showModelsPage() {
    if (models_page_) {
        models_page_->show();
    }
    current_page_ = 3;
}

void MainWindow::showSettingsPage() {
    if (settings_page_) {
        settings_page_->show();
    }
    current_page_ = 4;
}

int MainWindow::run() {
    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK MainWindow::windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (g_mainWindow) {
        return g_mainWindow->handleMessage(msg, wParam, lParam);
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT MainWindow::handleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            return 0;

        case WM_COMMAND: {
            int id = LOWORD(wParam);
            switch (id) {
                case 1001: showHomePage(); break;
                case 1002: showDashboardPage(); break;
                case 1003: showCreateAIPage(); break;
                case 1004: showModelsPage(); break;
                case 1005: showSettingsPage(); break;
                case 1006: PostMessageW(hwnd_, WM_CLOSE, 0, 0); break;
            }
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd_, &ps);
            FillRect(hdc, &ps.rcPaint, CreateSolidBrush(UIUtils::COLOR_DARK_BG));
            EndPaint(hwnd_, &ps);
            return 0;
        }

        case WM_CLOSE:
            DestroyWindow(hwnd_);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProcW(hwnd_, msg, wParam, lParam);
    }
}

void MainWindow::createMenuBar() {
    HMENU hMenu = CreateMenuW();
    HMENU hFileMenu = CreatePopupMenuW();
    HMENU hViewMenu = CreatePopupMenuW();
    HMENU hHelpMenu = CreatePopupMenuW();

    // File menu
    AppendMenuW(hFileMenu, MFT_STRING, 1006, L"E&xit");

    // View menu
    AppendMenuW(hViewMenu, MFT_STRING, 1001, L"&Home");
    AppendMenuW(hViewMenu, MFT_SEPARATOR, 0, nullptr);
    AppendMenuW(hViewMenu, MFT_STRING, 1002, L"&Dashboard");
    AppendMenuW(hViewMenu, MFT_STRING, 1003, L"&Create AI");
    AppendMenuW(hViewMenu, MFT_STRING, 1004, L"&Models");
    AppendMenuW(hViewMenu, MFT_STRING, 1005, L"&Settings");

    // Help menu
    AppendMenuW(hHelpMenu, MFT_STRING, 2001, L"&About");
    AppendMenuW(hHelpMenu, MFT_STRING, 2002, L"&Documentation");

    // Add menus to menu bar
    AppendMenuW(hMenu, MFT_POPUP, (UINT_PTR)hFileMenu, L"&File");
    AppendMenuW(hMenu, MFT_POPUP, (UINT_PTR)hViewMenu, L"&View");
    AppendMenuW(hMenu, MFT_POPUP, (UINT_PTR)hHelpMenu, L"&Help");

    SetMenuW(hwnd_, hMenu);
}

void MainWindow::createToolbar() {
    // Toolbar will be created with buttons for navigation
    // This is a placeholder for toolbar implementation
}

void MainWindow::createPages() {
    home_page_ = std::make_unique<HomePage>(hwnd_);
    dashboard_page_ = std::make_unique<DashboardPage>(hwnd_);
    create_ai_page_ = std::make_unique<CreateAIPage>(hwnd_);
    models_page_ = std::make_unique<ModelsPage>(hwnd_);
    settings_page_ = std::make_unique<SettingsPage>(hwnd_);

    // Show home page by default
    showHomePage();
}

void MainWindow::createStatusBar() {
    // Status bar will show application status
    // This is a placeholder for status bar implementation
}

void MainWindow::layoutPages() {
    // Layout pages in the main window area
    // This is a placeholder for layout implementation
}

} // namespace GUI
} // namespace AICreator
