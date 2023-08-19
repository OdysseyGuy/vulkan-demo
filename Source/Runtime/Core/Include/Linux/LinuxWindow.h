#pragma once

#include <memory>

#include "AbstractWindow.h"

#include "SDL3/SDL.h"

class LinuxApplication;

class LinuxWindow : public AbstractWindow
{
public:
    LinuxWindow();

    void Initialize(LinuxApplication *owner, const WindowProps &props, LinuxWindow *parent);

    static std::shared_ptr<LinuxWindow> Create();

    virtual void Reshape(const uint32_t &height, const uint32_t &width) override;
    virtual void MoveTo(const int32_t &x, const int32_t &y) override;

    virtual void Maximize() override;
    virtual void Minimize() override;
    virtual void Restore() override;

    virtual void Show() override;
    virtual void Hide() override;
    virtual void Close() override;

    virtual bool IsVisible() const override;
    virtual bool IsMaximized() const override;
    virtual bool IsMinimized() const override;

    virtual void *GetNativeHandle() override;

private:
    LinuxApplication *owner;

    SDL_Window *handle;
    bool visible;
    WindowProps props;

    static SDL_HitTestResult HitTest(SDL_Window *window, const SDL_Point *point, void *data);
};
