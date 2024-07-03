#define WIN32_LEAN_AND_MEAN
#define NOMINAX
#include <windows.h> //Include Windows

//////////////////////////////////////////////////////////////////
//                         Variables                            //
//////////////////////////////////////////////////////////////////

static HWND Window;

//////////////////////////////////////////////////////////////////
//                         Functions                            //
//////////////////////////////////////////////////////////////////

bool PlatformCreateWindow(int width, int height, char* title)
{
    HINSTANCE instance = GetModuleHandleA(0); //GetModuleHandle() usually calls this function, A is just the encoder

    char* ID = "BedEngineGame";

    WNDCLASSA WindowClass = {}; //Window class
    WindowClass.hInstance = instance; //set the window handle instance to the instance we set earlier
    WindowClass.hIcon = LoadIcon(instance, IDI_APPLICATION); //set the window icon, IDI_APPLICATION is the default window icon
    WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW); //Set the cursor
    WindowClass.lpszClassName = ID; //This is an ID not the actual name of the title
    WindowClass.lpfnWndProc = DefWindowProcA; // Call back for input in window

    if(!RegisterClassA(&WindowClass))
    {
        return false;
    }
    
    //WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
    int dwStyle = WS_OVERLAPPEDWINDOW;

    Window = CreateWindowExA(0, ID, title, dwStyle, 100, 100, width, height, NULL, NULL, instance, NULL);

    if(Window == NULL)
    {
        return false;
    }

    ShowWindow(Window, SW_SHOW);

    return true;
}

void PlatformUpdateWindow()
{
    MSG msg;

    while(PeekMessageA(&msg, Window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg); //send it to the call back of the window (WindowClass.lpfnWndProc)
    }
}