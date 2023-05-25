#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static HWND usrLbl;
static HWND usrEdit;
static HWND usrButton;
static HWND usrButton2;
static HWND hwndListBox;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char* className = "MyWindowClass";
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = className;

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Error al registrar la clase de la ventana.", "Error", MB_ICONERROR | MB_OK);
        return 0;
    }

    // Creacion ventana principal
    HWND hwnd = CreateWindowEx(0, className, "Mi App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

    // Captura de ventana de consola
    HWND hwndConsole = GetConsoleWindow();

    ShowWindow(hwndConsole, SW_HIDE); // Oculta la ventana de la consola
    ShowWindow(hwnd, nCmdShow); //Muestra la ventana principal
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE: // Creacion de componentes.
    {
        usrLbl      = CreateWindowEx(0, "STATIC", "Mi App", WS_VISIBLE | WS_CHILD, 50, 50, 100, 20, hwnd, NULL, NULL, NULL);
        usrEdit     = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 80, 200, 20, hwnd, NULL, NULL, NULL);
        hwndListBox = CreateWindowEx(0, "LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_STANDARD, 50, 110, 200, 150, hwnd, NULL, NULL, NULL);
        usrButton   = CreateWindowEx(0, "BUTTON", "Iniciar", WS_VISIBLE | WS_CHILD | BS_FLAT, 270, 80, 75, 20, hwnd, NULL, NULL, NULL);
        usrButton2  = CreateWindowEx(0, "BUTTON", "Detener", WS_VISIBLE | WS_CHILD | BS_FLAT, 350, 80, 75, 20, hwnd, NULL, NULL, NULL);

        break;
    }
    case WM_CTLCOLORSTATIC: // background del label del mismo color de la ventana principal.
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0)); // Color negro
        SetBkColor(hdcStatic, GetSysColor(COLOR_WINDOW));

        return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
    }
    case WM_DESTROY: //Destruccion de aplicacion
        PostQuitMessage(0);
        DestroyWindow(hwnd);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
