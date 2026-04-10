#include <windows.h>
#include <shellapi.h>
#include <string>
#include <sstream>

// Global variables
HWND hProgressBar = nullptr;
HWND hStatusText = nullptr;

void UpdateStatus(const char* message) {
    if (hStatusText) {
        SetWindowTextA(hStatusText, message);
    }
}

void UpdateProgress(int value) {
    if (hProgressBar) {
        SendMessage(hProgressBar, PBM_SETPOS, (WPARAM)value, 0);
    }
}

LRESULT CALLBACK LoadingWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Create progress bar
            hProgressBar = CreateWindowA(
                PROGRESS_CLASSA,
                nullptr,
                WS_CHILD | WS_VISIBLE,
                50, 100, 300, 30,
                hwnd, nullptr, GetModuleHandleA(nullptr), nullptr
            );
            SendMessage(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
            SendMessage(hProgressBar, PBM_SETSTEP, (WPARAM)1, 0);

            // Create status text
            hStatusText = CreateWindowA(
                "STATIC",
                "Initializing...",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                50, 150, 300, 50,
                hwnd, nullptr, GetModuleHandleA(nullptr), nullptr
            );

            // Set font
            HFONT hFont = CreateFontA(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                      DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
            SendMessage(hStatusText, WM_SETFONT, (WPARAM)hFont, TRUE);

            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Draw background
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

            // Draw title
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(0, 255, 136)); // Neon green
            HFONT hFont = CreateFontA(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                      DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
            SelectObject(hdc, hFont);
            TextOutA(hdc, 50, 30, "QIX - AI Creator", 15);
            DeleteObject(hFont);

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register window class
    WNDCLASSA wc = {};
    wc.lpfnWndProc = LoadingWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "AICreatorLoadingWindow";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);

    if (!RegisterClassA(&wc)) {
        MessageBoxA(nullptr, "Failed to register window class", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Create loading window
    HWND hWnd = CreateWindowA(
        "AICreatorLoadingWindow",
        "QIX - AI Creator",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) {
        MessageBoxA(nullptr, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // Step 1: Get executable path
    UpdateStatus("Step 1: Locating files...");
    UpdateProgress(20);
    Sleep(500);

    char exePath[MAX_PATH];
    if (!GetModuleFileNameA(nullptr, exePath, MAX_PATH)) {
        UpdateStatus("ERROR: Failed to get module path");
        UpdateProgress(0);
        Sleep(3000);
        DestroyWindow(hWnd);
        return 1;
    }

    // Step 2: Build web path
    UpdateStatus("Step 2: Building path...");
    UpdateProgress(40);
    Sleep(500);

    char* lastBackslash = strrchr(exePath, '\\');
    if (lastBackslash) {
        *lastBackslash = '\0';
    }

    std::string webPath = std::string(exePath) + "\\web\\index.html";

    // Step 3: Verify file exists
    UpdateStatus("Step 3: Verifying files...");
    UpdateProgress(60);
    Sleep(500);

    DWORD attribs = GetFileAttributesA(webPath.c_str());
    if (attribs == INVALID_FILE_ATTRIBUTES) {
        std::string errorMsg = "ERROR: File not found at:\n" + webPath;
        UpdateStatus(errorMsg.c_str());
        UpdateProgress(0);
        Sleep(5000);
        DestroyWindow(hWnd);
        return 1;
    }

    // Step 4: Open browser
    UpdateStatus("Step 4: Opening browser...");
    UpdateProgress(80);
    Sleep(500);

    HINSTANCE result = ShellExecuteA(nullptr, "open", webPath.c_str(), nullptr, nullptr, SW_SHOW);
    if ((int)result <= 32) {
        std::string errorMsg = "ERROR: Failed to open file\nError code: " + std::to_string((int)result);
        UpdateStatus(errorMsg.c_str());
        UpdateProgress(0);
        Sleep(5000);
        DestroyWindow(hWnd);
        return 1;
    }

    // Step 5: Complete
    UpdateStatus("Success! Browser opening...");
    UpdateProgress(100);
    Sleep(2000);

    // Close loading window
    DestroyWindow(hWnd);

    return 0;
}
