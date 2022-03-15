#include "Window.hpp"
#include "DirectX11.hpp"
#include "String.hpp"
#include "Date.hpp"
int main(int argc, char** argv) {
  auto window = Window("Principal")
    .setTitle("test")
    .show();
  auto dx11 = DirectX11(window);
  dx11.clearColor(1.f);
  String psSource = "float4 main(float4 position : SV_POSITION, float4 color : Color) : SV_TARGET { return color; }}";
  String vsSource = "struct VSOut{float4 pos: SV_POSITION;float4 color:Color;};VSOut main(float4 pos:Position,float4 color:Color){VSOut output;output.pos=pos;output.color=color;return output;}";
  dx11.createPixelShader(psSource);
  cout << 77 << std::endl;
  while (window.isOpen()) {
    dx11.clear();
    dx11.render();
  }
  return 0;
}