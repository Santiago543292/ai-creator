#include "gui/ui_utils.h"
#include <codecvt>
#include <locale>

namespace AICreator {
namespace GUI {

HFONT UIUtils::createFont(int height, const wchar_t* name, int weight) {
    return CreateFontW(
        height,           // Height
        0,                // Width
        0,                // Escapement
        0,                // Orientation
        weight,           // Weight
        FALSE,            // Italic
        FALSE,            // Underline
        FALSE,            // Strikeout
        DEFAULT_CHARSET,  // Charset
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        name
    );
}

void UIUtils::deleteFont(HFONT font) {
    if (font) {
        DeleteObject(font);
    }
}

HWND UIUtils::createButton(HWND parent, const wchar_t* text, int x, int y, int w, int h, UINT id) {
    return CreateWindowExW(
        0, L"BUTTON", text,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        x, y, w, h,
        parent, (HMENU)(UINT_PTR)id,
        GetModuleHandleW(nullptr), nullptr
    );
}

HWND UIUtils::createLabel(HWND parent, const wchar_t* text, int x, int y, int w, int h) {
    return CreateWindowExW(
        0, L"STATIC", text,
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        x, y, w, h,
        parent, nullptr,
        GetModuleHandleW(nullptr), nullptr
    );
}

HWND UIUtils::createTextBox(HWND parent, int x, int y, int w, int h, UINT id) {
    return CreateWindowExW(
        WS_EX_CLIENTEDGE, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
        x, y, w, h,
        parent, (HMENU)(UINT_PTR)id,
        GetModuleHandleW(nullptr), nullptr
    );
}

HWND UIUtils::createComboBox(HWND parent, int x, int y, int w, int h, UINT id) {
    return CreateWindowExW(
        0, L"COMBOBOX", L"",
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
        x, y, w, h,
        parent, (HMENU)(UINT_PTR)id,
        GetModuleHandleW(nullptr), nullptr
    );
}

HWND UIUtils::createListView(HWND parent, int x, int y, int w, int h, UINT id) {
    return CreateWindowExW(
        WS_EX_CLIENTEDGE, WC_LISTVIEWW, L"",
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL,
        x, y, w, h,
        parent, (HMENU)(UINT_PTR)id,
        GetModuleHandleW(nullptr), nullptr
    );
}

HWND UIUtils::createTabControl(HWND parent, int x, int y, int w, int h, UINT id) {
    return CreateWindowExW(
        0, WC_TABCONTROLW, L"",
        WS_CHILD | WS_VISIBLE,
        x, y, w, h,
        parent, (HMENU)(UINT_PTR)id,
        GetModuleHandleW(nullptr), nullptr
    );
}

void UIUtils::drawGradient(HDC hdc, RECT rect, COLORREF color1, COLORREF color2) {
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    for (int i = 0; i < height; ++i) {
        // Interpolate between colors
        int r1 = GetRValue(color1);
        int g1 = GetGValue(color1);
        int b1 = GetBValue(color1);

        int r2 = GetRValue(color2);
        int g2 = GetGValue(color2);
        int b2 = GetBValue(color2);

        int r = r1 + (r2 - r1) * i / height;
        int g = g1 + (g2 - g1) * i / height;
        int b = b1 + (b2 - b1) * i / height;

        COLORREF color = RGB(r, g, b);
        HPEN pen = CreatePen(PS_SOLID, 1, color);
        SelectObject(hdc, pen);

        MoveToEx(hdc, rect.left, rect.top + i, nullptr);
        LineTo(hdc, rect.right, rect.top + i);

        DeleteObject(pen);
    }
}

void UIUtils::drawRoundedRect(HDC hdc, RECT rect, int radius, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, brush);
    RoundRect(hdc, rect.left, rect.top, rect.right, rect.bottom, radius, radius);
    DeleteObject(brush);
}

void UIUtils::drawBorder(HDC hdc, RECT rect, COLORREF color, int width) {
    HPEN pen = CreatePen(PS_SOLID, width, color);
    SelectObject(hdc, pen);

    MoveToEx(hdc, rect.left, rect.top, nullptr);
    LineTo(hdc, rect.right, rect.top);
    LineTo(hdc, rect.right, rect.bottom);
    LineTo(hdc, rect.left, rect.bottom);
    LineTo(hdc, rect.left, rect.top);

    DeleteObject(pen);
}

void UIUtils::showInfo(HWND parent, const wchar_t* title, const wchar_t* message) {
    MessageBoxW(parent, message, title, MB_OK | MB_ICONINFORMATION);
}

void UIUtils::showError(HWND parent, const wchar_t* title, const wchar_t* message) {
    MessageBoxW(parent, message, title, MB_OK | MB_ICONERROR);
}

int UIUtils::showQuestion(HWND parent, const wchar_t* title, const wchar_t* message) {
    return MessageBoxW(parent, message, title, MB_YESNO | MB_ICONQUESTION);
}

std::wstring UIUtils::stringToWide(const std::string& str) {
    if (str.empty()) return std::wstring();

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
    return wstr;
}

std::string UIUtils::wideToString(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);
    return str;
}

int UIUtils::getDPI() {
    HDC hdc = GetDC(nullptr);
    int dpi = GetDeviceCaps(hdc, LOGPIXELSX);
    ReleaseDC(nullptr, hdc);
    return dpi;
}

int UIUtils::scaleDPI(int value) {
    int dpi = getDPI();
    return (value * dpi) / 96;  // 96 is standard DPI
}

} // namespace GUI
} // namespace AICreator
