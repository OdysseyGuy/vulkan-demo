#pragma once

#include "AbstractWindow.h"

#include "SDL3/SDL.h"

class LinuxApplication;

class LinuxWindow : public AbstractWindow
{
public:
    void Initialize(LinuxApplication *owner, const WindowInitializer &initializer,
                    LinuxWindow *parent);

    virtual void Maximize() override;
    virtual void Minimize() override;
    virtual void Restore() override;

    virtual void Show() override;
    virtual void Hide() override;
    virtual void Close() override;

    virtual void *GetNativeHandle() override;

private:
    LinuxApplication *owner;

    SDL_Window *handle;

    static SDL_HitTestResult HitTest(SDL_Window *window, const SDL_Point *point, void *data);
};
