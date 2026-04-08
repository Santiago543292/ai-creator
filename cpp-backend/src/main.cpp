#include <windows.h>
#include <shellapi.h>
#include <string>
#include <thread>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
    
    // Launch the web interface immediately in a separate thread
    std::thread launchThread([webPath]() {
        ShellExecuteA(nullptr, "open", webPath.c_str(), nullptr, nullptr, SW_SHOW);
    });
    launchThread.detach();

    return 0;
}
