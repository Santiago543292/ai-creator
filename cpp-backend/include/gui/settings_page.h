#pragma once

#include <windows.h>
#include <string>

namespace AICreator {
namespace GUI {

class SettingsPage {
public:
    SettingsPage(HWND parent);
    ~SettingsPage();

    void show();
    void hide();
    void applySettings();

private:
    HWND hwnd_;
    HWND parent_;
};

} // namespace GUI
} // namespace AICreator
