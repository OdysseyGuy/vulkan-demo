#include "Linux/LinuxWindow.h"
#include "Linux/LinuxPlatform.h"
#include "Linux/LinuxApplication.h"

constexpr uint32_t defaultMinWindowWidth = 800;
constexpr uint32_t defaultMinWindowHeight = 600;

LinuxWindow::LinuxWindow()
    : handle(nullptr)
    , visible(false)
{
}

void LinuxWindow::Initialize(LinuxApplication *inOwner, const WindowProps &inProps,
                             LinuxWindow *parent)
{
    props = inProps;
    owner = inOwner;

    if (!LinuxPlatform::InitSDL()) {
        // error SDL was not initialized
    }

    uint32_t windowFlags = SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;
    handle = SDL_CreateWindowWithPosition(props.title, props.x, props.y, props.width, props.height,
                                          windowFlags);
    if (handle == nullptr) {
        // error failed to create a window
    }

    SDL_SetWindowMinimumSize(handle, defaultMinWindowWidth, defaultMinWindowHeight);

    // Re-enable this if we really create a custom window
    // SDL_SetWindowHitTest(handle, LinuxWindow::HitTest, this);
}

std::shared_ptr<LinuxWindow> LinuxWindow::Create()
{
    return std::make_shared<LinuxWindow>();
}

void LinuxWindow::Reshape(const uint32_t &height, const uint32_t &width)
{
    SDL_SetWindowSize(handle, width, height);
}

void LinuxWindow::MoveTo(const int32_t &x, const int32_t &y)
{
    SDL_SetWindowPosition(handle, x, y);
}

void LinuxWindow::Maximize()
{
    SDL_MaximizeWindow(handle);
}

void LinuxWindow::Minimize()
{
    SDL_MinimizeWindow(handle);
}

void LinuxWindow::Restore()
{
    SDL_RestoreWindow(handle);
}

void LinuxWindow::Show()
{
    if (!visible) {
        SDL_ShowWindow(handle);
        visible = true;
    }

    if (!IsMaximized()) {
        Restore();
    }
}

void LinuxWindow::Hide()
{
    if (visible) {
        SDL_HideWindow(handle);
        visible = false;
    }
}

void LinuxWindow::Close()
{
}

bool LinuxWindow::IsVisible() const
{
    return false;
}

bool LinuxWindow::IsMaximized() const
{
    return SDL_GetWindowFlags(handle) & SDL_WINDOW_MAXIMIZED;
}

bool LinuxWindow::IsMinimized() const
{
    return SDL_GetWindowFlags(handle) & SDL_WINDOW_MINIMIZED;
}

void *LinuxWindow::GetNativeHandle()
{
    return static_cast<void *>(handle);
}

SDL_HitTestResult LinuxWindow::HitTest(SDL_Window *window, const SDL_Point *point, void *data)
{
    LinuxWindow *selfPtr = static_cast<LinuxWindow *>(data);
    std::shared_ptr<LinuxWindow> self = selfPtr->owner->GetWindowFromHandle(window);

    return SDL_HitTestResult();
}
