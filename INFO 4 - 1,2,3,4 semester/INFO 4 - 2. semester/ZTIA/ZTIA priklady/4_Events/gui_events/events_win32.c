// Event loop and callbacks using Win32
// https://msdn.microsoft.com/en-us/library/aa271855(v=vs.60).aspx

#include <stdio.h>
#include <windows.h>
#include <Windowsx.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {

  case WM_LBUTTONDOWN:
    int x = GET_X_LPARAM(lParam);
    int y = GET_Y_LPARAM(lParam);
    printf("MouseEvent: button=left x=%d y=%d\n", x, y);
    break;
  case WM_KEYDOWN:
    int key = wParam;
    printf("KeyboardEvent: key=%d\n", key);
    if(key == VK_ESCAPE) PostQuitMessage(0);
    break;
  case WM_CLOSE:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  MSG msg = { 0 };
  WNDCLASS wc = { 0 };
  wc.lpfnWndProc = WndProc; // Funkcia spracovania spravy
  wc.hInstance = hInstance;
  wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
  wc.lpszClassName = "minwindowsappi";
  if (!RegisterClass(&wc))
    return 1;
  if (!CreateWindow(wc.lpszClassName,
          "Win32 Application",
          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
          100, 100, 320, 320, 0, 0, hInstance, NULL))
    return 2;

  // Cyklus obsluhujuci spravy
  while (GetMessage(&msg, NULL, 0, 0) > 0)
    DispatchMessage(&msg);
  return 0;
}

int main() {
  return WinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOW);
}
