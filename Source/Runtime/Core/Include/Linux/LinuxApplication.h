#pragma once

#include <vector>
#include "AbstractApplication.h"
#include "Linux/LinuxWindow.h"

class LinuxApplication : public AbstractApplication
{
public:
    /** Searches for a window by their handles. */
    std::shared_ptr<LinuxWindow> GetWindowFromHandle(SDL_Window *handle);

    virtual std::shared_ptr<AbstractWindow> CreateWindow(const WindowProps &initializer,
                                                         AbstractWindow *parent) override;

    static LinuxApplication *CreateLinuxApplication();

private:
    std::vector<std::shared_ptr<LinuxWindow>> windows;

    static LinuxApplication *instance;
};
