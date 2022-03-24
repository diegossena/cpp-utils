#pragma once
#include <tchar.h>
#include <windows.h>
#include "String.hpp"
class Window {
  static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
    if (message == WM_CREATE) {
      auto pcs = (LPCREATESTRUCT)lParam;
      Window* window = (Window*)pcs->lpCreateParams;
      ::SetWindowLongPtrA(
        hWnd,
        GWLP_USERDATA,
        (LONG_PTR)window
      );
      return 1;
    }
    Window* window = reinterpret_cast<Window*>(
      ::GetWindowLongPtrA(hWnd, GWLP_USERDATA));

    if (window) {
      switch (message) {
      case WM_SETFOCUS:
        window->hasFocus_ = true;
        break;
      case WM_KILLFOCUS:
        window->hasFocus_ = false;
        break;
      case WM_SIZE: {
        window->width_ = LOWORD(lParam);
        window->height_ = HIWORD(lParam);
        //window->onResize(width, height);
        break;
      }
      case WM_DESTROY:
        PostQuitMessage(0);
        return 1;
      }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  // Props
  HWND hwnd_;
  bool hasFocus_ = true;
  u_short width_ = 800;
  u_short height_ = 600;
public:
  // Refs
  const u_short& width = width_;
  const u_short& height = height_;
  const bool& hasFocus = hasFocus_;
  // Conversion
  operator const HWND () {
    return hwnd_;
  }
  // Constructor
  Window(const char* title) {
    WNDCLASSEXA wc = {};

    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Window::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.lpszClassName = title;

    RegisterClassExA(&wc);

    RECT wr = { 0, 0, width, height };
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
  }
  bool isOpen()
  {
    MSG msg;
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessageA(&msg);
      if (msg.message == WM_QUIT)
        return false;
    }
    return true;
  }
  Window& setTitle(String newTitle) {
    SetWindowTextA(hwnd_, newTitle);
    return *this;
  }
  Window& show() {
    ShowWindow(hwnd_, SW_SHOWDEFAULT);
    return *this;
  }
  Window& hide() {
    ShowWindow(hwnd_, SW_HIDE);
    return *this;
  }
};