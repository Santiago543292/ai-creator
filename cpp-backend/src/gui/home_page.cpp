#include "gui/home_page.h"
#include "gui/ui_utils.h"

namespace AICreator {
namespace GUI {

// ============================================
// Home Page Implementation
// ============================================

HomePage::HomePage(HWND parent)
    : hwnd_(nullptr), parent_(parent) {
    // Create home page window
    const wchar_t* CLASS_NAME = L"AICreatorHomePage";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(UIUtils::COLOR_DARK_BG);

    RegisterClassW(&wc);

    hwnd_ = CreateWindowExW(
        0, CLASS_NAME, L"Home",
        WS_CHILD,
        0, 50, 1200, 750,
        parent, nullptr,
        GetModuleHandleW(nullptr), nullptr
    );
}

HomePage::~HomePage() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
    }
}

void HomePage::show() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_SHOW);
        UpdateWindow(hwnd_);
    }
}

void HomePage::hide() {
    if (hwnd_) {
        ShowWindow(hwnd_, SW_HIDE);
    }
}

// ============================================
// Dashboard Page Implementation
// ============================================

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

// ============================================
// Create AI Page Implementation
// ============================================

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

// ============================================
// Models Page Implementation
// ============================================

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

// ============================================
// Settings Page Implementation
// ============================================

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
