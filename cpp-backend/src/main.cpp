#include <windows.h>
#include <string>
#include <vector>

// Forward declarations
class MainWindow;
static MainWindow* g_pMainWindow = nullptr;

// Color constants (QIX Branding)
const COLORREF COLOR_DARK_BG = RGB(20, 20, 25);      // Dark background
const COLORREF COLOR_NEON_GREEN = RGB(0, 221, 0);    // Neon green accent
const COLORREF COLOR_TEXT = RGB(200, 200, 200);      // Light text
const COLORREF COLOR_BUTTON = RGB(40, 40, 50);       // Button background

// Control IDs
enum ControlID {
    ID_HOME_BTN = 1001,
    ID_DASHBOARD_BTN = 1002,
    ID_CREATE_AI_BTN = 1003,
    ID_MODELS_BTN = 1004,
    ID_SETTINGS_BTN = 1005,
    ID_CONTENT_AREA = 2000,
    ID_TITLE_TEXT = 2001
};

// Page types
enum PageType {
    PAGE_HOME = 0,
    PAGE_DASHBOARD = 1,
    PAGE_CREATE_AI = 2,
    PAGE_MODELS = 3,
    PAGE_SETTINGS = 4
};

class MainWindow {
private:
    HWND hwnd_;
    HWND hSidebar_;
    HWND hContentArea_;
    HWND hNavButtons_[5];
    PageType currentPage_;
    HBRUSH hBrushDark_;
    HBRUSH hBrushButton_;
    HFONT hFontTitle_;
    HFONT hFontNormal_;

public:
    MainWindow() : hwnd_(nullptr), currentPage_(PAGE_HOME) {
        // Create brushes
        hBrushDark_ = CreateSolidBrush(COLOR_DARK_BG);
        hBrushButton_ = CreateSolidBrush(COLOR_BUTTON);
        
        // Create fonts
        hFontTitle_ = CreateFontA(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
                                   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                                   DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
        hFontNormal_ = CreateFontA(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                    DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
    }

    ~MainWindow() {
        if (hBrushDark_) DeleteObject(hBrushDark_);
        if (hBrushButton_) DeleteObject(hBrushButton_);
        if (hFontTitle_) DeleteObject(hFontTitle_);
        if (hFontNormal_) DeleteObject(hFontNormal_);
    }

    bool Initialize() {
        // Register window class
        WNDCLASSA wc = {};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandleA(nullptr);
        wc.lpszClassName = "AICreatorMainWindow";
        wc.hbrBackground = hBrushDark_;
        wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);

        if (!RegisterClassA(&wc)) {
            return false;
        }

        // Create main window
        hwnd_ = CreateWindowExA(
            0,
            "AICreatorMainWindow",
            "AI Creator - Intelligent AI Generation Platform",
            WS_OVERLAPPEDWINDOW,
            100, 100, 1200, 800,
            nullptr, nullptr, wc.hInstance, this
        );

        if (!hwnd_) {
            return false;
        }

        // Create sidebar
        CreateSidebar();
        
        // Create content area
        hContentArea_ = CreateWindowExA(
            0, "STATIC", "",
            WS_CHILD | WS_VISIBLE,
            200, 0, 1000, 800,
            hwnd_, (HMENU)ID_CONTENT_AREA, GetModuleHandleA(nullptr), nullptr
        );

        // Show home page
        ShowPage(PAGE_HOME);

        return true;
    }

    void CreateSidebar() {
        // Sidebar background
        hSidebar_ = CreateWindowExA(
            0, "STATIC", "",
            WS_CHILD | WS_VISIBLE,
            0, 0, 200, 800,
            hwnd_, nullptr, GetModuleHandleA(nullptr), nullptr
        );

        // Navigation buttons
        const char* btnLabels[] = { "Home", "Dashboard", "Create AI", "Models", "Settings" };
        int btnIDs[] = { ID_HOME_BTN, ID_DASHBOARD_BTN, ID_CREATE_AI_BTN, ID_MODELS_BTN, ID_SETTINGS_BTN };

        for (int i = 0; i < 5; i++) {
            hNavButtons_[i] = CreateWindowExA(
                0, "BUTTON", btnLabels[i],
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10, 60 + (i * 60), 180, 50,
                hwnd_, (HMENU)btnIDs[i], GetModuleHandleA(nullptr), nullptr
            );

            SendMessageA(hNavButtons_[i], WM_SETFONT, (WPARAM)hFontNormal_, TRUE);
        }
    }

    void ShowPage(PageType page) {
        currentPage_ = page;

        // Clear content area
        RECT rect;
        GetClientRect(hContentArea_, &rect);
        FillRect(GetDC(hContentArea_), &rect, hBrushDark_);

        // Draw page content
        HDC hdc = GetDC(hContentArea_);
        SetBkColor(hdc, COLOR_DARK_BG);
        SetTextColor(hdc, COLOR_NEON_GREEN);

        switch (page) {
            case PAGE_HOME:
                DrawHomePage(hdc);
                break;
            case PAGE_DASHBOARD:
                DrawDashboardPage(hdc);
                break;
            case PAGE_CREATE_AI:
                DrawCreateAIPage(hdc);
                break;
            case PAGE_MODELS:
                DrawModelsPage(hdc);
                break;
            case PAGE_SETTINGS:
                DrawSettingsPage(hdc);
                break;
        }

        ReleaseDC(hContentArea_, hdc);
    }

    void DrawHomePage(HDC hdc) {
        SelectObject(hdc, hFontTitle_);
        TextOutA(hdc, 50, 50, "Welcome to AI Creator", 21);

        SelectObject(hdc, hFontNormal_);
        SetTextColor(hdc, COLOR_TEXT);
        TextOutA(hdc, 50, 120, "Create, train, and deploy AI models with ease.", 45);
        TextOutA(hdc, 50, 160, "Get started by creating a new AI model.", 39);
        TextOutA(hdc, 50, 200, "Use the navigation menu on the left to explore features.", 54);
    }

    void DrawDashboardPage(HDC hdc) {
        SelectObject(hdc, hFontTitle_);
        TextOutA(hdc, 50, 50, "Dashboard", 9);

        SelectObject(hdc, hFontNormal_);
        SetTextColor(hdc, COLOR_TEXT);
        TextOutA(hdc, 50, 120, "Active Models: 0", 15);
        TextOutA(hdc, 50, 160, "Total Trained: 0", 15);
        TextOutA(hdc, 50, 200, "System Status: Ready", 20);
    }

    void DrawCreateAIPage(HDC hdc) {
        SelectObject(hdc, hFontTitle_);
        TextOutA(hdc, 50, 50, "Create New AI Model", 18);

        SelectObject(hdc, hFontNormal_);
        SetTextColor(hdc, COLOR_TEXT);
        TextOutA(hdc, 50, 120, "Model Name:", 11);
        TextOutA(hdc, 50, 170, "Algorithm:", 10);
        TextOutA(hdc, 50, 220, "Framework:", 10);
    }

    void DrawModelsPage(HDC hdc) {
        SelectObject(hdc, hFontTitle_);
        TextOutA(hdc, 50, 50, "AI Models", 9);

        SelectObject(hdc, hFontNormal_);
        SetTextColor(hdc, COLOR_TEXT);
        TextOutA(hdc, 50, 120, "No models created yet.", 22);
        TextOutA(hdc, 50, 160, "Create a new model to get started.", 33);
    }

    void DrawSettingsPage(HDC hdc) {
        SelectObject(hdc, hFontTitle_);
        TextOutA(hdc, 50, 50, "Settings", 8);

        SelectObject(hdc, hFontNormal_);
        SetTextColor(hdc, COLOR_TEXT);
        TextOutA(hdc, 50, 120, "Theme: Dark (QIX Branding)", 26);
        TextOutA(hdc, 50, 160, "Auto-save: Enabled", 18);
        TextOutA(hdc, 50, 200, "Version: 1.0.0", 14);
    }

    void OnButtonClick(int buttonID) {
        switch (buttonID) {
            case ID_HOME_BTN:
                ShowPage(PAGE_HOME);
                break;
            case ID_DASHBOARD_BTN:
                ShowPage(PAGE_DASHBOARD);
                break;
            case ID_CREATE_AI_BTN:
                ShowPage(PAGE_CREATE_AI);
                break;
            case ID_MODELS_BTN:
                ShowPage(PAGE_MODELS);
                break;
            case ID_SETTINGS_BTN:
                ShowPage(PAGE_SETTINGS);
                break;
        }
    }

    HWND GetHwnd() const { return hwnd_; }

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        MainWindow* pThis = nullptr;

        if (msg == WM_CREATE) {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pThis = reinterpret_cast<MainWindow*>(pCreate->lpCreateParams);
            SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        } else {
            pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
        }

        if (!pThis) return DefWindowProcA(hwnd, msg, wParam, lParam);

        switch (msg) {
            case WM_COMMAND:
                pThis->OnButtonClick(LOWORD(wParam));
                return 0;

            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                FillRect(hdc, &ps.rcPaint, pThis->hBrushDark_);
                EndPaint(hwnd, &ps);
                return 0;
            }

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            default:
                return DefWindowProcA(hwnd, msg, wParam, lParam);
        }
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MainWindow mainWindow;
    
    if (!mainWindow.Initialize()) {
        MessageBoxA(nullptr, "Failed to initialize main window", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(mainWindow.GetHwnd(), nCmdShow);
    UpdateWindow(mainWindow.GetHwnd());

    // Message loop
    MSG msg = {};
    while (GetMessageA(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return (int)msg.wParam;
}
