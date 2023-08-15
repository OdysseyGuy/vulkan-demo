#pragma once

#include <string>

class LinuxPlatform
{
public:
    static bool InitSDL();
    static bool CopyToClipboard(const char *data);
    static bool PasteFromClipboard(std::string &data);
};
