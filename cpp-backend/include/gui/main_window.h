#ifndef AI_CREATOR_MAIN_WINDOW_H
#define AI_CREATOR_MAIN_WINDOW_H

#include <windows.h>
#include <string>
#include <memory>

namespace AICreator {
namespace GUI {

class HomePage;
class DashboardPage;
class CreateAIPage;
class ModelsPage;
class SettingsPage;

/**
 * Main Window - Primary application window
 * Manages page navigation and overall UI layout
 */
class MainWindow {
public:
    MainWindow();
    ~MainWindow();

    // Initialize and show the window
    bool initialize();
    void show();
    void hide();
    void close();

    // Page navigation
    void showHomePage();
    void showDashboardPage();
    void showCreateAIPage();
    void showModelsPage();
    void showSettingsPage();

    // Get window handle
    HWND getHandle() const { return hwnd_; }

    // Message loop
    static int run();

private:
    HWND hwnd_;
    HINSTANCE hInstance_;

    // Page instances
    std::unique_ptr<HomePage> home_page_;
    std::unique_ptr<DashboardPage> dashboard_page_;
    std::unique_ptr<CreateAIPage> create_ai_page_;
    std::unique_ptr<ModelsPage> models_page_;
    std::unique_ptr<SettingsPage> settings_page_;

    // Current active page
    int current_page_;

    // Window procedure
    static LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT handleMessage(UINT msg, WPARAM wParam, LPARAM lParam);

    // UI creation
    void createMenuBar();
    void createToolbar();
    void createStatusBar();
    void createPages();
    void layoutPages();
};

} // namespace GUI
} // namespace AICreator

#endif // AI_CREATOR_MAIN_WINDOW_H
