#include "Window.hpp"
#include "DirectX.hpp"
#include "String.hpp"
#include "Date.hpp"
int main(int argc, char** argv) {
  auto window = Window("Principal")
    .setTitle("test")
    .show();
  auto directX = DirectX(window);
  directX.clearColor(1.f);
  auto shader = directX.createShader("ps_paint.cso", "vs_paint.cso");
  directX.useShader(shader);
  while (window.isOpen()) {
    directX.clear();
    
    directX.render();
  }
  return 0;
}