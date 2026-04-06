#ifndef AI_CREATOR_UI_UTILS_H
#define AI_CREATOR_UI_UTILS_H

#include <windows.h>
#include <string>

namespace AICreator {
namespace GUI {

/**
 * UI Utilities - Common UI helper functions
 */
class UIUtils {
public:
    // Color constants (QIX Branding)
    static constexpr COLORREF COLOR_NEON_GREEN = RGB(0, 221, 0);      // #00DD00
    static constexpr COLORREF COLOR_DARK_BG = RGB(20, 20, 20);        // #141414
    static constexpr COLORREF COLOR_DARK_CARD = RGB(30, 30, 30);      // #1E1E1E
    static constexpr COLORREF COLOR_TEXT_LIGHT = RGB(240, 240, 240);  // #F0F0F0
    static constexpr COLORREF COLOR_TEXT_DARK = RGB(100, 100, 100);   // #646464

    // Font utilities
    static HFONT createFont(int height, const wchar_t* name, int weight = FW_NORMAL);
    static void deleteFont(HFONT font);

    // Control creation
    static HWND createButton(HWND parent, const wchar_t* text, int x, int y, int w, int h, UINT id);
    static HWND createLabel(HWND parent, const wchar_t* text, int x, int y, int w, int h);
    static HWND createTextBox(HWND parent, int x, int y, int w, int h, UINT id);
    static HWND createComboBox(HWND parent, int x, int y, int w, int h, UINT id);
    static HWND createListView(HWND parent, int x, int y, int w, int h, UINT id);
    static HWND createTabControl(HWND parent, int x, int y, int w, int h, UINT id);

    // Drawing utilities
    static void drawGradient(HDC hdc, RECT rect, COLORREF color1, COLORREF color2);
    static void drawRoundedRect(HDC hdc, RECT rect, int radius, COLORREF color);
    static void drawBorder(HDC hdc, RECT rect, COLORREF color, int width = 1);

    // Message boxes
    static void showInfo(HWND parent, const wchar_t* title, const wchar_t* message);
    static void showError(HWND parent, const wchar_t* title, const wchar_t* message);
    static int showQuestion(HWND parent, const wchar_t* title, const wchar_t* message);

    // String utilities
    static std::wstring stringToWide(const std::string& str);
    static std::string wideToString(const std::wstring& wstr);

    // DPI awareness
    static int getDPI();
    static int scaleDPI(int value);
};

} // namespace GUI
} // namespace AICreator

#endif // AI_CREATOR_UI_UTILS_H
