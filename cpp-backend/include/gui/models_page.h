#pragma once

#include <windows.h>
#include <string>

namespace AICreator {
namespace GUI {

class ModelsPage {
public:
    ModelsPage(HWND parent);
    ~ModelsPage();

    void show();
    void hide();
    void refreshModelList();

private:
    HWND hwnd_;
    HWND parent_;
};

} // namespace GUI
} // namespace AICreator
