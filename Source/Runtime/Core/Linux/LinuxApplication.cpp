#include "Linux/LinuxApplication.h"

#include "Delegates/Delegates.h"

LinuxApplication *LinuxApplication::instance = nullptr;

void LinuxApplication::CreateWindow(AbstractWindow *inWindow, const WindowInitializer &initializer,
                                    AbstractWindow *inParent)
{
    LinuxWindow *window = static_cast<LinuxWindow *>(inWindow);
    LinuxWindow *parent = static_cast<LinuxWindow *>(inParent);

    window->Initialize(this, initializer, parent);
    windows.emplace_back(window);
    f();
}

std::shared_ptr<LinuxWindow> LinuxApplication::GetWindowFromHandle(SDL_Window *handle)
{
    for (uint32_t i = 0; i < windows.size(); ++i) {
        std::shared_ptr<LinuxWindow> window = windows[i];
        if (window->GetNativeHandle() == handle) {
            return window;
        }
    }
    return std::shared_ptr<LinuxWindow>(nullptr);
}

LinuxApplication *LinuxApplication::CreateLinuxApplication()
{
    instance = new LinuxApplication();
    return instance;
}
