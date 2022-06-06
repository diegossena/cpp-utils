// Globals
#include <vector>
#include <d3d11.h>
#include <fstream>
// Modules
#include "Window.hpp"
#include "Error.hpp"
//
class DirectX {
private:
  // Props
  float COLOR_CLEAR_VALUE[4] = { .0f, .0f, .0f, .0f };
  Window window_;
  IDXGISwapChain* swapchain;
  ID3D11Device* dev;
  ID3D11DeviceContext* devcon;
  ID3D11RenderTargetView* backbuffer;

  ID3D11InputLayout* layout;        // the pointer to the input layout
  ID3D11Buffer* vertexBuffer;       // the pointer to the vertex buffer
  ID3D11Buffer* indexBuffer;        // the pointer to the index buffer
  // Create Buffer
  D3D11_BUFFER_DESC bufferDesc = {
    0,                      // ByteWidth
    D3D11_USAGE_DYNAMIC,    // USAGE: write access access by CPU and GPU
    0,                      // BindFlags
    D3D11_CPU_ACCESS_WRITE, // allow CPU to write in buffer
    0,                      // MiscFlags
    0                       //StructureByteStride
  };
  D3D11_SUBRESOURCE_DATA subResourceData;
  void InitGraphics()
  {
    // select which primtive type we are using
    devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  }

public:
  // Subclasses
  class Shader {
    ID3D11PixelShader* ppPs = nullptr;
    ID3D11VertexShader* ppVs = nullptr;
    ID3D11InputLayout* layout = nullptr;
  public:
    ~Shader() {
      ppPs->Release();
      ppVs->Release();
      layout->Release();
    }
    // Conversion
    operator ID3D11PixelShader* () {
      return ppPs;
    }
    operator ID3D11VertexShader* () {
      return ppVs;
    }
    operator ID3D11InputLayout* () {
      return layout;
    }
    operator ID3D11PixelShader** () {
      return &ppPs;
    }
    operator ID3D11VertexShader** () {
      return &ppVs;
    }
    operator ID3D11InputLayout** () {
      return &layout;
    }
  };
  //
  DirectX(const Window& window) : window_(window)
  {
    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // use 32-bit color
    scd.BufferDesc.Width = window.width;        // set the back buffer width
    scd.BufferDesc.Height = window.height;      // set the back buffer height
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // how swap chain is to be used
    scd.OutputWindow = window_;                    // the window to be used
    scd.SampleDesc.Count = 4;                           // how many multisamples
    scd.Windowed = TRUE;                                // windowed/full-screen mode
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // allow full-screen switching

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(
      0,
      D3D_DRIVER_TYPE_HARDWARE,
      0,
      0,
      0,
      0,
      D3D11_SDK_VERSION,
      &scd,
      &swapchain,
      &dev,
      0,
      &devcon
    );

    // get the address of the back buffer
    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    dev->CreateRenderTargetView(pBackBuffer, 0, &backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    devcon->OMSetRenderTargets(1, &backbuffer, 0);

    // Set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = window.width;
    viewport.Height = window.height;

    devcon->RSSetViewports(1, &viewport);

    InitGraphics();
  }
  ~DirectX()
  {
    // close and release all existing COM objects
    swapchain->Release();
    backbuffer->Release();
    dev->Release();
    devcon->Release();
    layout->Release();
    vertexBuffer->Release();
    indexBuffer->Release();
  }
  void clearColor(float red = .0f, float green = .0f, float blue = .0f, float alpha = .0f) {
    COLOR_CLEAR_VALUE[0] = red;
    COLOR_CLEAR_VALUE[1] = green;
    COLOR_CLEAR_VALUE[2] = blue;
    COLOR_CLEAR_VALUE[3] = alpha;
  }
  void clear() {
    devcon->ClearRenderTargetView(backbuffer, (float*)&COLOR_CLEAR_VALUE);
  }
  void render(void)
  {
    swapchain->Present(0, 0);
  }
  // Statics
  Shader createShader(String ps_path, String vs_path) {
    Shader shader;
    std::ifstream filestream;
    std::string data;
    // Open Pixel Shader
    filestream.open(ps_path);
    if (!filestream.is_open()) {
      cerr << "Error on file opening" << std::endl;
      throw "Error on file opening";
    }
    // memory allocation for Pixel Shader
    filestream.seekg(0, std::ios::end);
    data.reserve(filestream.tellg());
    filestream.seekg(0, std::ios::beg);
    // Load Pixel Shader cso
    data.assign(
      (std::istreambuf_iterator<char>(filestream)),
      std::istreambuf_iterator<char>()
    );
    filestream.close();
    // Create Pixel Shader
    dev->CreatePixelShader(data.c_str(), data.length(), 0, shader);
    // Open Vertex Shader
    filestream.open(vs_path);
    if (!filestream.is_open()) {
      cerr << "Error on file opening" << std::endl;
      throw "Error on file opening";
    }
    // memory allocation for Vertex Shader
    filestream.seekg(0, std::ios::end);
    data.reserve(filestream.tellg());
    filestream.seekg(0, std::ios::beg);
    // Load Vertex Shader cso
    data.assign(
      (std::istreambuf_iterator<char>(filestream)),
      std::istreambuf_iterator<char>()
    );
    filestream.close();
    // Create Vertex Shader
    dev->CreateVertexShader(data.c_str(), data.length(), 0, shader);
    // create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} };

    dev->CreateInputLayout(ied, 2, data.c_str(), data.length(), shader);
    return shader;
  }
  void useShader(Shader& shader) {
    devcon->VSSetShader(shader, 0, 0);
    devcon->PSSetShader(shader, 0, 0);
    devcon->IASetInputLayout(shader);
  }
};