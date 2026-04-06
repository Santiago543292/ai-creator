#include "gui/models_page.h"
#include "gui/ui_utils.h"

namespace AICreator {
namespace GUI {

ModelsPage::ModelsPage(HWND parent)
    : hwnd_(nullptr), parent_(parent) {
    const wchar_t* CLASS_NAME = L"AICreatorModelsPage";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(UIUtils::COLOR_DARK_BG);

    RegisterClassW(&wc);

    hwnd_ = CreateWindowExW(
        0, CLASS_NAME, L"Models",
        WS_CHILD,
        0, 50, 1200, 750,
        parent, nullptr,
        GetModuleHandleW(nullptr), nullptr
    );
}

ModelsPage::~ModelsPage() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
    }
}

void ModelsPage::show() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_SHOW);
        UpdateWindow(hwnd_);
    }
}

void ModelsPage::hide() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_HIDE);
    }
}

void ModelsPage::refreshModelList() {
    // Refresh model list
}

} // namespace GUI
} // namespace AICreator
