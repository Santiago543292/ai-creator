#include <windows.h>
#include <shellapi.h>

// Simple message box that opens the web interface
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Get executable directory
    char exePath[MAX_PATH];
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    
    // Find last backslash
    char* lastSlash = strrchr(exePath, '\\');
    if (lastSlash) {
        *lastSlash = '\0';
    }

    // Build path to index.html
    char webPath[MAX_PATH];
    sprintf_s(webPath, MAX_PATH, "%s\\web\\index.html", exePath);

    // Try to open the HTML file with default browser
    ShellExecuteA(nullptr, "open", webPath, nullptr, nullptr, SW_SHOW);

    // Wait a bit
    Sleep(1000);

    return 0;
}
