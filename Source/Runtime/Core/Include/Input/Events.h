#pragma once

enum KeyboardModifier {
    LeftShiftModifier = (1 << 0),
    RightShiftModifier = (1 << 1),
    LeftControlModifier = (1 << 2),
    RightControlModifier = (1 << 3),
    LeftAltModifier = (1 << 4),
    RightAltModifier = (1 << 5)
};

class AbstractInputEvent
{
public:
    AbstractInputEvent()
        : modifiers()
        , isRepeat(false)
    {
    }

    AbstractInputEvent(KeyboardModifier inModifiers, const bool inIsRepeat)
        : modifiers(inModifiers)
        , isRepeat(inIsRepeat)
    {
    }

private:
    KeyboardModifier modifiers;
    bool isRepeat;
};
