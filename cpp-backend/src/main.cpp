#include <windows.h>
#include <string>
#include <vector>
#include <cmath>

// Forward declarations
class MainWindow;
static MainWindow* g_pMainWindow = nullptr;

// QIX Color Scheme
const COLORREF COLOR_DARK_BG = RGB(20, 20, 25);
const COLORREF COLOR_NEON_GREEN = RGB(0, 221, 0);
const COLORREF COLOR_TEXT = RGB(200, 200, 200);
const COLORREF COLOR_BUTTON = RGB(40, 40, 50);
const COLORREF COLOR_BUTTON_HOVER = RGB(60, 60, 70);
const COLORREF COLOR_BORDER = RGB(50, 50, 60);
const COLORREF COLOR_GRAPH_LINE1 = RGB(100, 150, 255);  // Blue
const COLORREF COLOR_GRAPH_LINE2 = RGB(255, 100, 100);  // Red
const COLORREF COLOR_GRAPH_LINE3 = RGB(100, 255, 100);  // Green
const COLORREF COLOR_GRAPH_LINE4 = RGB(200, 100, 255);  // Purple

// Control IDs
enum ControlID {
    ID_TAB_NN_AI = 1001,
    ID_TAB_NN_STORAGE = 1002,
    ID_TAB_AI_H = 1003,
    ID_TAB_AI_B = 1004,
    ID_TAB_AI_LAB = 1005,
    ID_TAB_AI_PROMPT = 1006
};

class MainWindow {
private:
    HWND hwnd_;
    HWND hTabButtons_[6];
    int currentTab_;
    HBRUSH hBrushDark_;
    HBRUSH hBrushButton_;
    HBRUSH hBrushBorder_;
    HFONT hFontTitle_;
    HFONT hFontNormal_;
    HFONT hFontSmall_;
    HPEN hPenGreen_;
    HPEN hPenGraph1_;
    HPEN hPenGraph2_;
    HPEN hPenGraph3_;
    HPEN hPenGraph4_;

public:
    MainWindow() : hwnd_(nullptr), currentTab_(0) {
        hBrushDark_ = CreateSolidBrush(COLOR_DARK_BG);
        hBrushButton_ = CreateSolidBrush(COLOR_BUTTON);
        hBrushBorder_ = CreateSolidBrush(COLOR_BORDER);
        
        hFontTitle_ = CreateFontA(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                                   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                   DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
        hFontNormal_ = CreateFontA(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                    DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
        hFontSmall_ = CreateFontA(11, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                   DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
        
        hPenGreen_ = CreatePen(PS_SOLID, 2, COLOR_NEON_GREEN);
        hPenGraph1_ = CreatePen(PS_SOLID, 2, COLOR_GRAPH_LINE1);
        hPenGraph2_ = CreatePen(PS_SOLID, 2, COLOR_GRAPH_LINE2);
        hPenGraph3_ = CreatePen(PS_SOLID, 2, COLOR_GRAPH_LINE3);
        hPenGraph4_ = CreatePen(PS_SOLID, 2, COLOR_GRAPH_LINE4);
    }

    ~MainWindow() {
        if (hBrushDark_) DeleteObject(hBrushDark_);
        if (hBrushButton_) DeleteObject(hBrushButton_);
        if (hBrushBorder_) DeleteObject(hBrushBorder_);
        if (hFontTitle_) DeleteObject(hFontTitle_);
        if (hFontNormal_) DeleteObject(hFontNormal_);
        if (hFontSmall_) DeleteObject(hFontSmall_);
        if (hPenGreen_) DeleteObject(hPenGreen_);
        if (hPenGraph1_) DeleteObject(hPenGraph1_);
        if (hPenGraph2_) DeleteObject(hPenGraph2_);
        if (hPenGraph3_) DeleteObject(hPenGraph3_);
        if (hPenGraph4_) DeleteObject(hPenGraph4_);
    }

    bool Initialize() {
        WNDCLASSA wc = {};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandleA(nullptr);
        wc.lpszClassName = "AICreatorMainWindow";
        wc.hbrBackground = hBrushDark_;
        wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);

        if (!RegisterClassA(&wc)) return false;

        hwnd_ = CreateWindowExA(
            0,
            "AICreatorMainWindow",
            "AI Creator - Intelligent AI Generation Platform",
            WS_OVERLAPPEDWINDOW,
            0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
            nullptr, nullptr, wc.hInstance, this
        );

        if (!hwnd_) return false;

        CreateTabButtons();
        return true;
    }

    void CreateTabButtons() {
        const char* tabLabels[] = { "NN-AI", "NN-Storage", "AI-H", "AI-B", "AI-Lab", "AI-Prompt" };
        int tabIDs[] = { ID_TAB_NN_AI, ID_TAB_NN_STORAGE, ID_TAB_AI_H, ID_TAB_AI_B, ID_TAB_AI_LAB, ID_TAB_AI_PROMPT };

        for (int i = 0; i < 6; i++) {
            hTabButtons_[i] = CreateWindowExA(
                0, "BUTTON", tabLabels[i],
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                150 + (i * 140), 20, 130, 40,
                hwnd_, (HMENU)tabIDs[i], GetModuleHandleA(nullptr), nullptr
            );
            SendMessageA(hTabButtons_[i], WM_SETFONT, (WPARAM)hFontNormal_, TRUE);
        }
    }

    void OnTabClick(int tabID) {
        currentTab_ = tabID - ID_TAB_NN_AI;
        InvalidateRect(hwnd_, nullptr, FALSE);
    }

    void DrawContent(HDC hdc) {
        RECT clientRect;
        GetClientRect(hwnd_, &clientRect);
        
        // Draw title bar background
        RECT titleRect = { 0, 0, clientRect.right, 80 };
        FillRect(hdc, &titleRect, hBrushDark_);
        
        // Draw title
        SetBkColor(hdc, COLOR_DARK_BG);
        SetTextColor(hdc, COLOR_NEON_GREEN);
        SelectObject(hdc, hFontTitle_);
        TextOutA(hdc, 30, 30, "AI Creator Dashboard", 19);

        // Draw main content area
        RECT contentRect = { 0, 80, clientRect.right, clientRect.bottom };
        FillRect(hdc, &contentRect, hBrushDark_);

        // Draw three-column layout
        int leftColWidth = (clientRect.right - 300) / 2;
        int centerColWidth = (clientRect.right - 300) / 2;
        int rightColWidth = 300;

        // Left column: AI Usage
        DrawLeftColumn(hdc, 10, 100, leftColWidth - 20, clientRect.bottom - 110);
        
        // Center column: AI Stage with graphs
        DrawCenterColumn(hdc, leftColWidth + 10, 100, centerColWidth - 20, clientRect.bottom - 110);
        
        // Right sidebar
        DrawRightSidebar(hdc, leftColWidth + centerColWidth + 10, 100, rightColWidth - 20, clientRect.bottom - 110);
    }

    void DrawLeftColumn(HDC hdc, int x, int y, int width, int height) {
        // Draw border
        SelectObject(hdc, hPenGreen_);
        Rectangle(hdc, x, y, x + width, y + height);

        // Draw title
        SetTextColor(hdc, COLOR_NEON_GREEN);
        SelectObject(hdc, hFontNormal_);
        TextOutA(hdc, x + 10, y + 10, "AI-Usage", 8);

        // Draw stats
        SetTextColor(hdc, COLOR_TEXT);
        SelectObject(hdc, hFontSmall_);
        TextOutA(hdc, x + 10, y + 50, "ELA writer", 10);
        TextOutA(hdc, x + 10, y + 80, "1M - 11%", 8);
        TextOutA(hdc, x + 10, y + 110, "16M64%", 6);

        // Draw mini graph
        DrawMiniGraph(hdc, x + 10, y + 150, width - 20, height - 170);
    }

    void DrawCenterColumn(HDC hdc, int x, int y, int width, int height) {
        // Draw border
        SelectObject(hdc, hPenGreen_);
        Rectangle(hdc, x, y, x + width, y + height);

        // Draw title
        SetTextColor(hdc, COLOR_NEON_GREEN);
        SelectObject(hdc, hFontNormal_);
        TextOutA(hdc, x + 10, y + 10, "AI-Stage", 8);

        // Draw stats
        SetTextColor(hdc, COLOR_TEXT);
        SelectObject(hdc, hFontSmall_);
        TextOutA(hdc, x + 10, y + 50, "ELA-writer: 4GB", 15);
        TextOutA(hdc, x + 10, y + 80, "AI-42: Active", 12);

        // Draw main performance graph
        DrawPerformanceGraph(hdc, x + 10, y + 120, width - 20, height - 140);
    }

    void DrawRightSidebar(HDC hdc, int x, int y, int width, int height) {
        // Draw border
        SelectObject(hdc, hPenGreen_);
        Rectangle(hdc, x, y, x + width, y + height);

        // Draw title
        SetTextColor(hdc, COLOR_NEON_GREEN);
        SelectObject(hdc, hFontNormal_);
        TextOutA(hdc, x + 10, y + 10, "Sidebar", 7);

        // Draw info items
        SetTextColor(hdc, COLOR_TEXT);
        SelectObject(hdc, hFontSmall_);
        TextOutA(hdc, x + 10, y + 50, "More data", 9);
        TextOutA(hdc, x + 10, y + 80, "More defined graphs", 19);
        TextOutA(hdc, x + 10, y + 110, "Tree data", 9);
        TextOutA(hdc, x + 10, y + 140, "Page selected", 13);
        TextOutA(hdc, x + 10, y + 170, "Neural Network", 14);
        TextOutA(hdc, x + 10, y + 200, "AI-Creator creations", 20);
    }

    void DrawMiniGraph(HDC hdc, int x, int y, int width, int height) {
        // Draw graph border
        SelectObject(hdc, hPenGreen_);
        Rectangle(hdc, x, y, x + width, y + height);

        // Draw simple sine wave
        SelectObject(hdc, hPenGraph1_);
        for (int i = 0; i < width - 10; i++) {
            double angle = (double)i / 20.0;
            int y1 = y + height / 2 + (int)(50 * sin(angle));
            int y2 = y + height / 2 + (int)(50 * sin(angle + 0.1));
            MoveToEx(hdc, x + 5 + i, y1, nullptr);
            LineTo(hdc, x + 5 + i + 1, y2);
        }
    }

    void DrawPerformanceGraph(HDC hdc, int x, int y, int width, int height) {
        // Draw graph border
        SelectObject(hdc, hPenGreen_);
        Rectangle(hdc, x, y, x + width, y + height);

        // Draw grid lines
        SelectObject(hdc, hPenGreen_);
        for (int i = 0; i < 5; i++) {
            int lineY = y + (height / 4) * i;
            MoveToEx(hdc, x, lineY, nullptr);
            LineTo(hdc, x + width, lineY);
        }

        // Draw multiple performance lines
        HPEN pens[] = { hPenGraph1_, hPenGraph2_, hPenGraph3_, hPenGraph4_ };
        
        for (int line = 0; line < 4; line++) {
            SelectObject(hdc, pens[line]);
            for (int i = 0; i < width - 20; i++) {
                double angle = (double)i / 30.0 + (line * 0.5);
                int y1 = y + height / 2 + (int)((height / 3) * sin(angle));
                int y2 = y + height / 2 + (int)((height / 3) * sin(angle + 0.05));
                
                if (y1 >= y && y1 <= y + height && y2 >= y && y2 <= y + height) {
                    MoveToEx(hdc, x + 10 + i, y1, nullptr);
                    LineTo(hdc, x + 10 + i + 1, y2);
                }
            }
        }
    }

    HWND GetHwnd() const { return hwnd_; }

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        MainWindow* pThis = nullptr;

        if (msg == WM_CREATE) {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pThis = reinterpret_cast<MainWindow*>(pCreate->lpCreateParams);
            SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        } else {
            pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
        }

        if (!pThis) return DefWindowProcA(hwnd, msg, wParam, lParam);

        switch (msg) {
            case WM_COMMAND:
                pThis->OnTabClick(LOWORD(wParam));
                return 0;

            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                pThis->DrawContent(hdc);
                EndPaint(hwnd, &ps);
                return 0;
            }

            case WM_SIZE:
            case WM_SIZING:
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            default:
                return DefWindowProcA(hwnd, msg, wParam, lParam);
        }
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MainWindow mainWindow;
    
    if (!mainWindow.Initialize()) {
        MessageBoxA(nullptr, "Failed to initialize application", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(mainWindow.GetHwnd(), SW_MAXIMIZE);
    UpdateWindow(mainWindow.GetHwnd());

    MSG msg = {};
    while (GetMessageA(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return (int)msg.wParam;
}
