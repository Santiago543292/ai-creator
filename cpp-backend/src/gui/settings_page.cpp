#include "gui/settings_page.h"
#include "gui/ui_utils.h"

namespace AICreator {
namespace GUI {

SettingsPage::SettingsPage(HWND parent)
    : hwnd_(nullptr), parent_(parent) {
    const wchar_t* CLASS_NAME = L"AICreatorSettingsPage";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(UIUtils::COLOR_DARK_BG);

    RegisterClassW(&wc);

    hwnd_ = CreateWindowExW(
        0, CLASS_NAME, L"Settings",
        WS_CHILD,
        0, 50, 1200, 750,
        parent, nullptr,
        GetModuleHandleW(nullptr), nullptr
    );
}

SettingsPage::~SettingsPage() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
    }
}

void SettingsPage::show() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_SHOW);
        UpdateWindow(hwnd_);
    }
}

void SettingsPage::hide() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_HIDE);
    }
}

void SettingsPage::applySettings() {
    // Apply settings
}

} // namespace GUI
} // namespace AICreator
