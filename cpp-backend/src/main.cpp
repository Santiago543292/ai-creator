#include <windows.h>
#include <shellapi.h>
#include <string>

// QIX Color Scheme
const COLORREF COLOR_DARK_BG = RGB(10, 10, 10);
const COLORREF COLOR_NEON_GREEN = RGB(0, 255, 136);

class MainWindow {
private:
    HWND hwnd_;
    HBRUSH hBrushDark_;
    HFONT hFontTitle_;

public:
    MainWindow() : hwnd_(nullptr) {
        hBrushDark_ = CreateSolidBrush(COLOR_DARK_BG);
        hFontTitle_ = CreateFontA(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                   DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
    }

    ~MainWindow() {
        if (hBrushDark_) DeleteObject(hBrushDark_);
        if (hFontTitle_) DeleteObject(hFontTitle_);
    }

    bool Initialize() {
        WNDCLASSA wc = {};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandleA(nullptr);
        wc.lpszClassName = "AICreatorMainWindow";
        wc.hbrBackground = hBrushDark_;
        wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);

        if (!RegisterClassA(&wc)) return false;

        hwnd_ = CreateWindowExA(
            0,
            "AICreatorMainWindow",
            "QIX - AI Creator Platform",
            WS_OVERLAPPEDWINDOW,
            0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
            nullptr, nullptr, wc.hInstance, this
        );

        return hwnd_ != nullptr;
    }

    void DrawLoadingScreen(HDC hdc) {
        RECT clientRect;
        GetClientRect(hwnd_, &clientRect);
        
        FillRect(hdc, &clientRect, hBrushDark_);

        // Draw title
        SetBkColor(hdc, COLOR_DARK_BG);
        SetTextColor(hdc, COLOR_NEON_GREEN);
        SelectObject(hdc, hFontTitle_);
        
        const char* title = "QIX - AI Creator Platform";
        TextOutA(hdc, clientRect.right / 2 - 200, clientRect.bottom / 2 - 100, title, strlen(title));

        // Draw loading message
        HFONT hFontNormal = CreateFontA(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
        SelectObject(hdc, hFontNormal);
        SetTextColor(hdc, RGB(200, 200, 200));
        
        const char* msg = "Launching web interface...";
        TextOutA(hdc, clientRect.right / 2 - 150, clientRect.bottom / 2 + 50, msg, strlen(msg));
        
        DeleteObject(hFontNormal);
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
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                pThis->DrawLoadingScreen(hdc);
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

// Simple HTTP server to serve the web files
class SimpleWebServer {
public:
    static bool StartServer() {
        // For now, we'll open the web interface directly
        // In a real implementation, this would start a local web server
        return true;
    }

    static void OpenWebInterface() {
        // Get the directory where the executable is located
        char exePath[MAX_PATH];
        GetModuleFileNameA(nullptr, exePath, MAX_PATH);
        
        // Find the last backslash
        char* lastBackslash = strrchr(exePath, '\\');
        if (lastBackslash) {
            *lastBackslash = '\0';
        }

        // Construct path to index.html
        std::string webPath = std::string(exePath) + "\\web\\index.html";
        
        // Try to open the web interface
        // First, try to open with default browser
        ShellExecuteA(nullptr, "open", webPath.c_str(), nullptr, nullptr, SW_SHOW);
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MainWindow mainWindow;
    
    if (!mainWindow.Initialize()) {
        MessageBoxA(nullptr, "Failed to initialize application", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(mainWindow.GetHwnd(), SW_MAXIMIZE);
    UpdateWindow(mainWindow.GetHwnd());

    // Start the web server
    SimpleWebServer::StartServer();

    // Give the window a moment to display
    Sleep(1000);

    // Open the web interface
    SimpleWebServer::OpenWebInterface();

    // Message loop
    MSG msg = {};
    while (GetMessageA(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return (int)msg.wParam;
}
