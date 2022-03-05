#include "Window.hpp"
#include "String.hpp"
int main(int argc, char** argv) {
  String window_name = "Principal";
  auto mainWindow = Window(window_name).show();
  //mainWindow.show();
  while (mainWindow.isOpen());
  return 0;
}