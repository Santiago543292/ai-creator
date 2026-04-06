#ifndef AI_CREATOR_HOME_PAGE_H
#define AI_CREATOR_HOME_PAGE_H

#include <windows.h>

namespace AICreator {
namespace GUI {

/**
 * Home Page - Welcome and overview
 */
class HomePage {
public:
    HomePage(HWND parent);
    ~HomePage();

    HWND getHandle() const { return hwnd_; }
    void show();
    void hide();

private:
    HWND hwnd_;
    HWND parent_;
};

/**
 * Dashboard Page - Real-time statistics and metrics
 */
class DashboardPage {
public:
    DashboardPage(HWND parent);
    ~DashboardPage();

    HWND getHandle() const { return hwnd_; }
    void show();
    void hide();
    void updateMetrics();

private:
    HWND hwnd_;
    HWND parent_;
};

/**
 * Create AI Page - Model creation wizard
 */
class CreateAIPage {
public:
    CreateAIPage(HWND parent);
    ~CreateAIPage();

    HWND getHandle() const { return hwnd_; }
    void show();
    void hide();

private:
    HWND hwnd_;
    HWND parent_;
};

/**
 * Models Page - View and manage models
 */
class ModelsPage {
public:
    ModelsPage(HWND parent);
    ~ModelsPage();

    HWND getHandle() const { return hwnd_; }
    void show();
    void hide();
    void refreshModelList();

private:
    HWND hwnd_;
    HWND parent_;
};

/**
 * Settings Page - Configuration and preferences
 */
class SettingsPage {
public:
    SettingsPage(HWND parent);
    ~SettingsPage();

    HWND getHandle() const { return hwnd_; }
    void show();
    void hide();
    void applySettings();

private:
    HWND hwnd_;
    HWND parent_;
};

} // namespace GUI
} // namespace AICreator

#endif // AI_CREATOR_HOME_PAGE_H
