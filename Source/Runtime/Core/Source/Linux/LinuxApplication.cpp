#include "Linux/LinuxApplication.h"

LinuxApplication *LinuxApplication::instance = nullptr;

std::shared_ptr<AbstractWindow> LinuxApplication::CreateWindow(const WindowProps &initializer,
                                                               AbstractWindow *inParent)
{
    std::shared_ptr<LinuxWindow> window = LinuxWindow::Create();
    LinuxWindow *parent = static_cast<LinuxWindow *>(inParent);

    window->Initialize(this, initializer, parent);
    windows.emplace_back(window);

    return window;
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
