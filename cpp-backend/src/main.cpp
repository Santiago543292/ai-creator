#include <windows.h>
#include <shellapi.h>
#include <string>

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
    
    // Launch the web interface
    HINSTANCE result = ShellExecuteA(nullptr, "open", webPath.c_str(), nullptr, nullptr, SW_SHOW);
    
    // Check if ShellExecute succeeded (returns > 32 on success)
    if ((int)result <= 32) {
        // If opening HTML file fails, try opening with file:// protocol
        std::string fileUrl = "file:///" + webPath;
        // Replace backslashes with forward slashes for URL
        for (size_t i = 0; i < fileUrl.length(); i++) {
            if (fileUrl[i] == '\\') {
                fileUrl[i] = '/';
            }
        }
        ShellExecuteA(nullptr, "open", fileUrl.c_str(), nullptr, nullptr, SW_SHOW);
    }

    // Keep the application running for a moment to ensure the browser launches
    Sleep(500);

    return 0;
}
