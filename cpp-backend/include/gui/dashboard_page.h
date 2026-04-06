#pragma once

#include <windows.h>
#include <string>

namespace AICreator {
namespace GUI {

class DashboardPage {
public:
    DashboardPage(HWND parent);
    ~DashboardPage();

    void show();
    void hide();
    void updateMetrics();

private:
    HWND hwnd_;
    HWND parent_;
};

} // namespace GUI
} // namespace AICreator
