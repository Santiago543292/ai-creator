#include "gui/create_ai_page.h"
#include "gui/ui_utils.h"

namespace AICreator {
namespace GUI {

CreateAIPage::CreateAIPage(HWND parent)
    : hwnd_(nullptr), parent_(parent) {
    const wchar_t* CLASS_NAME = L"AICreatorCreateAIPage";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(UIUtils::COLOR_DARK_BG);

    RegisterClassW(&wc);

    hwnd_ = CreateWindowExW(
        0, CLASS_NAME, L"Create AI",
        WS_CHILD,
        0, 50, 1200, 750,
        parent, nullptr,
        GetModuleHandleW(nullptr), nullptr
    );
}

CreateAIPage::~CreateAIPage() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
    }
}

void CreateAIPage::show() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_SHOW);
        UpdateWindow(hwnd_);
    }
}

void CreateAIPage::hide() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_HIDE);
    }
}

} // namespace GUI
} // namespace AICreator
