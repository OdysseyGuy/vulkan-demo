#pragma once

#include <stdint.h>

/** Window creation hints. Hints define the purpose the window is created for. */
enum WindowHint {
    WINDOW_HINT_NOTITLEBAR = (1 << 0), /** Create a window with no titlebar. */
    WINDOW_HINT_MAXIMIZED = (1 << 1),  /** Create a window that is maximized by default. */
};

enum WindowType {
    Tooltip = 0,
    Windowed,
};

/** Data required to initialize a window. */
struct WindowProps
{
    char *title;
    uint32_t height, width;
    uint32_t x, y;
    uint32_t hints;
    WindowType type;
};

/** Base class for all platform-specific window implementation. */
class AbstractWindow
{
public:
    virtual ~AbstractWindow()
    {
    }

    virtual void Reshape(const uint32_t &height, const uint32_t &width) = 0;
    virtual void MoveTo(const int32_t &x, const int32_t &y) = 0;

    virtual void Maximize() = 0;
    virtual void Minimize() = 0;
    virtual void Restore() = 0;

    /** Interface method to show the window. */
    virtual void Show() = 0;
    /** Interface method to hide the window. */
    virtual void Hide() = 0;
    /** Interface method to close the window. */
    virtual void Close() = 0;

    virtual bool IsVisible() const = 0;
    virtual bool IsMaximized() const = 0;
    virtual bool IsMinimized() const = 0;

    /** Interface to method to retrieve implementation handle. */
    virtual void *GetNativeHandle() = 0;
};
