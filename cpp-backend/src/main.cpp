#include <windows.h>
#include <shellapi.h>
#include <cstdio>

bool FileExists(const char* path) {
    DWORD attribs = GetFileAttributesA(path);
    return (attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY));
}

bool DirectoryExists(const char* path) {
    DWORD attribs = GetFileAttributesA(path);
    return (attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char exePath[MAX_PATH];
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    
    // Get directory containing exe
    char* lastBackslash = strrchr(exePath, '\\');
    if (lastBackslash) {
        *lastBackslash = '\0';
    }

    char webPath[MAX_PATH];
    char webDir[MAX_PATH];
    
    // Try multiple locations for web files
    const char* possibleLocations[] = {
        "%s\\web\\index.html",           // Same directory
        "%s\\..\\web\\index.html",       // Parent directory
        "%s\\..\\..\\web\\index.html",   // Two levels up
        "%s\\cpp-backend\\web\\index.html", // In cpp-backend subfolder
    };

    bool found = false;
    for (int i = 0; i < 4; i++) {
        sprintf_s(webPath, MAX_PATH, possibleLocations[i], exePath);
        
        if (FileExists(webPath)) {
            found = true;
            break;
        }
    }

    if (!found) {
        // Try to find web directory
        sprintf_s(webDir, MAX_PATH, "%s\\web", exePath);
        if (!DirectoryExists(webDir)) {
            sprintf_s(webDir, MAX_PATH, "%s\\..\\web", exePath);
            if (!DirectoryExists(webDir)) {
                sprintf_s(webDir, MAX_PATH, "%s\\..\\..\\web", exePath);
                if (!DirectoryExists(webDir)) {
                    sprintf_s(webDir, MAX_PATH, "%s\\cpp-backend\\web", exePath);
                }
            }
        }
        
        char errorMsg[1024];
        sprintf_s(errorMsg, 1024, 
            "ERROR: Web files not found!\n\n"
            "Executable directory: %s\n\n"
            "Looking for web folder in:\n"
            "- %s\\web\n"
            "- %s\\..\\web\n"
            "- %s\\..\\..\\web\n\n"
            "Make sure the 'web' folder with all HTML files is in one of these locations.",
            exePath, exePath, exePath, exePath);
        
        MessageBoxA(nullptr, errorMsg, "QIX - AI Creator Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Open the HTML file
    HINSTANCE result = ShellExecuteA(nullptr, "open", webPath, nullptr, nullptr, SW_SHOW);
    
    if ((int)result <= 32) {
        // Try with file:// protocol
        char fileUrl[MAX_PATH];
        strcpy_s(fileUrl, MAX_PATH, webPath);
        
        // Replace backslashes with forward slashes
        for (int i = 0; fileUrl[i]; i++) {
            if (fileUrl[i] == '\\') {
                fileUrl[i] = '/';
            }
        }
        
        // Prepend file:///
        char fullUrl[MAX_PATH];
        sprintf_s(fullUrl, MAX_PATH, "file:///%s", fileUrl);
        
        ShellExecuteA(nullptr, "open", fullUrl, nullptr, nullptr, SW_SHOW);
    }

    return 0;
}
