#include <windows.h>
#include <shellapi.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Get the path to the executable
    char exePath[MAX_PATH];
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    
    // Find the last backslash to get directory
    char* lastBackslash = strrchr(exePath, '\\');
    if (lastBackslash) {
        *lastBackslash = '\0';
    }

    // Build path to index.html
    std::string webPath = std::string(exePath) + "\\web\\index.html";
    
    // Open the HTML file with default browser
    ShellExecuteA(nullptr, "open", webPath.c_str(), nullptr, nullptr, SW_SHOW);

    return 0;
}
