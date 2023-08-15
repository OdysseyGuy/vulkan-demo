#pragma once

#include <stdint.h>
#include <memory>

#include "AbstractWindow.h"

enum MouseButtonType { Left = 0, Middle, Right, Unknown };

class AbstractApplicationEventHandler
{
public:
    virtual bool OnKeyChar(const char character)
    {
        return false;
    }

    virtual bool OnKeyDown(const uint32_t keyCode)
    {
        return false;
    }

    virtual bool OnKeyUp(const uint32_t keyCode)
    {
        return false;
    }

    virtual bool OnMouseDown(const AbstractWindow &window, MouseButtonType type)
    {
        return false;
    }

    virtual bool OnMouseUp(const AbstractWindow &window, MouseButtonType type)
    {
        return false;
    }

    virtual bool OnMouseWheel(const float delta)
    {
        return false;
    }

    virtual bool OnMouseMove()
    {
        return false;
    }

    virtual void OnWindowResized(const AbstractWindow &window)
    {
    }

    virtual void OnWindowMoved(const AbstractWindow &window)
    {
    }
};

class AbstractApplication
{
public:
    virtual void SetEventHandler(const std::shared_ptr<AbstractApplicationEventHandler> &inHandler)
    {
        eventHandler = inHandler;
    }

    std::shared_ptr<AbstractApplicationEventHandler> GetEventHandler()
    {
        return eventHandler;
    }

    virtual void Tick(const float deltaTime)
    {
    }

    virtual void Destroy()
    {
    }

    virtual void CreateWindow(AbstractWindow *window, const WindowInitializer &initializer,
                              AbstractWindow *parent) = 0;

private:
    std::shared_ptr<AbstractApplicationEventHandler> eventHandler;
};
