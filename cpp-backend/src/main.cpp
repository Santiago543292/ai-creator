#include <windows.h>
#include <shellapi.h>
#include <cstdio>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Step 1: Get executable directory
    char exePath[MAX_PATH];
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    
    char* lastBackslash = strrchr(exePath, '\\');
    if (lastBackslash) {
        *lastBackslash = '\0';
    }

    // Step 2: Build path to index.html
    char webPath[MAX_PATH];
    sprintf_s(webPath, MAX_PATH, "%s\\web\\index.html", exePath);

    // Step 3: Check if file exists
    DWORD attribs = GetFileAttributesA(webPath);
    if (attribs == INVALID_FILE_ATTRIBUTES) {
        char errorMsg[512];
        sprintf_s(errorMsg, 512, "ERROR: Web files not found!\n\nLooking for:\n%s\n\nMake sure the 'web' folder exists in the same directory as this executable.", webPath);
        MessageBoxA(nullptr, errorMsg, "QIX - AI Creator Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Step 4: Open the HTML file
    HINSTANCE result = ShellExecuteA(nullptr, "open", webPath, nullptr, nullptr, SW_SHOW);
    
    if ((int)result <= 32) {
        char errorMsg[512];
        sprintf_s(errorMsg, 512, "ERROR: Failed to open browser!\n\nError code: %d\n\nTrying alternative method...", (int)result);
        MessageBoxA(nullptr, errorMsg, "QIX - AI Creator Error", MB_OK | MB_ICONWARNING);
        
        // Try alternative: use file:// protocol
        char fileUrl[MAX_PATH];
        sprintf_s(fileUrl, MAX_PATH, "file:///%s", webPath);
        
        // Replace backslashes with forward slashes
        for (int i = 0; fileUrl[i]; i++) {
            if (fileUrl[i] == '\\') {
                fileUrl[i] = '/';
            }
        }
        
        ShellExecuteA(nullptr, "open", fileUrl, nullptr, nullptr, SW_SHOW);
    }

    return 0;
}
