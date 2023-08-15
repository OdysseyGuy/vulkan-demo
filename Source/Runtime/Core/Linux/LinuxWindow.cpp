#include "Linux/LinuxWindow.h"

void LinuxWindow::Initialize(LinuxApplication *owner, const WindowInitializer &initializer,
                             LinuxWindow *parent)
{
    handle = SDL_CreateWindow(initializer.title, initializer.width, initializer.height, 0);
    if (handle == nullptr) {
        // error failed to create a window
    }

    // Re-enable this if we really create a custom window
    // SDL_SetWindowHitTest(handle, LinuxWindow::HitTest, this);
}

void LinuxWindow::Maximize()
{
}

void LinuxWindow::Minimize()
{
}

void LinuxWindow::Restore()
{
}

void LinuxWindow::Show()
{
}

void LinuxWindow::Hide()
{
}

void LinuxWindow::Close()
{
}

void *LinuxWindow::GetNativeHandle()
{
    return static_cast<void *>(handle);
}

SDL_HitTestResult LinuxWindow::HitTest(SDL_Window *window, const SDL_Point *point, void *data)
{
    // LinuxWindow *self = static_cast<LinuxWindow *>(data);
    return SDL_HitTestResult();
}
