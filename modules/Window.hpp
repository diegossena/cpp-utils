#pragma once
#include <tchar.h>
#include <windows.h>
#include "String.hpp"
class Window {
  static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
    if (message == WM_CREATE)
    {
      LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
      Window* pWindow = (Window*)pcs->lpCreateParams;

      ::SetWindowLongPtrW(
        hWnd,
        GWLP_USERDATA,
        PtrToUlong(pWindow));

      return 1;
    }

    Window* pWindow = reinterpret_cast<Window*>(
      ::GetWindowLongPtr(hWnd, GWLP_USERDATA));

    if (pWindow)
    {
      switch (message)
      {
      case WM_SETFOCUS:
      {
        //pWindow->onFocus(true);
        return 0;
      }
      case WM_KILLFOCUS:
      {
        //pWindow->onFocus(false);
        return 0;
      }
      case WM_SIZE:
      {
        unsigned short width = LOWORD(lParam);
        unsigned short height = HIWORD(lParam);
        //pWindow->onResize(width, height);
        return 0;
      }
      case WM_DESTROY:
      {
        PostQuitMessage(0);
        return 1;
      }
      }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  HWND hwnd_;
public:
  Window(const char* title) {
    WNDCLASSEXA wc = {};

    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Window::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.lpszClassName = title;

    RegisterClassExA(&wc);

    RECT wr = { 0, 0, 800, 600 };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    hwnd_ = CreateWindowExA(
      0,                   // extended window style
      wc.lpszClassName,    // pointer to registered class name
      wc.lpszClassName,    // pointer to window name
      WS_OVERLAPPEDWINDOW, // window style
      CW_USEDEFAULT,       // horizontal position of window
      CW_USEDEFAULT,       // vertical position of window
      wr.right - wr.left,  // window width
      wr.bottom - wr.top,  // window height
      0,                   // handle to parent or owner window
      0,                   // handle to menu, or child-window identifier
      wc.hInstance,        // handle to application instance
      this                 // pointer to window-creation data
    );
    ShowWindow(hwnd_, SW_SHOWDEFAULT);
  }
  bool isOpen()
  {
    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      if (msg.message == WM_QUIT)
        return false;
    }
    return true;
  }
  Window& setTitle() {
    SetWindowTextA(hwnd_, "Test");
    return *this;
  }
  Window& show() {
    ShowWindow(hwnd_, SW_SHOWDEFAULT);
    return *this;
  }
  void hide() {
    ShowWindow(hwnd_, SW_HIDE);
  }
};