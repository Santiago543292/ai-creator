#include "gui/dashboard_page.h"
#include "gui/ui_utils.h"

namespace AICreator {
namespace GUI {

DashboardPage::DashboardPage(HWND parent)
    : hwnd_(nullptr), parent_(parent) {
    const wchar_t* CLASS_NAME = L"AICreatorDashboardPage";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(UIUtils::COLOR_DARK_BG);

    RegisterClassW(&wc);

    hwnd_ = CreateWindowExW(
        0, CLASS_NAME, L"Dashboard",
        WS_CHILD,
        0, 50, 1200, 750,
        parent, nullptr,
        GetModuleHandleW(nullptr), nullptr
    );
}

DashboardPage::~DashboardPage() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
    }
}

void DashboardPage::show() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_SHOW);
        UpdateWindow(hwnd_);
    }
}

void DashboardPage::hide() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_HIDE);
    }
}

void DashboardPage::updateMetrics() {
    // Update dashboard metrics
}

} // namespace GUI
} // namespace AICreator
