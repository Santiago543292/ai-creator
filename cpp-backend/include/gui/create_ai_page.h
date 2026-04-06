#pragma once

#include <windows.h>
#include <string>

namespace AICreator {
namespace GUI {

class CreateAIPage {
public:
    CreateAIPage(HWND parent);
    ~CreateAIPage();

    void show();
    void hide();

private:
    HWND hwnd_;
    HWND parent_;
};

} // namespace GUI
} // namespace AICreator
