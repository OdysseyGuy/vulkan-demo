#pragma once

#include <vector>
#include "AbstractApplication.h"
#include "Linux/LinuxWindow.h"

class LinuxApplication : public AbstractApplication
{
public:
    virtual void CreateWindow(AbstractWindow *window, const WindowInitializer &initializer,
                              AbstractWindow *parent) override;

    /** Searches for a window by their handles. */
    std::shared_ptr<LinuxWindow> GetWindowFromHandle(SDL_Window *handle);

    static LinuxApplication *CreateLinuxApplication();

private:
    std::vector<std::shared_ptr<LinuxWindow>> windows;

    static LinuxApplication *instance;
};
