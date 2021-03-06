#pragma once
#include <windows.h>
namespace Keyboard {
  enum Key
  {
    BackSpace = VK_BACK,
    Tab,
    Enter = VK_RETURN,
    Shift = VK_SHIFT,
    Control,
    Alt,
    Pause,
    CapsLock,
    ESC = VK_ESCAPE,
    Space = VK_SPACE,
    PageUp,
    PageDown,
    End,
    Home,
    Left,
    Up,
    Right,
    Down,
    Insert = VK_INSERT,
    Delete,
    Num0 = 0x30,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    A = 'A',
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Numpad0 = VK_NUMPAD0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    Multiply,
    Add,
    Subtract = VK_SUBTRACT,
    Divide = VK_DIVIDE,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    Hyphen = VK_OEM_MINUS
  };
  static bool isKeyPressed(Key key) {
    return (GetAsyncKeyState(key) & 0x8000) != 0;
  }
};