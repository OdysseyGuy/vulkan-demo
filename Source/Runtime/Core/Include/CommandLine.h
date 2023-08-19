#pragma once

class CommandLine
{
public:
    static const char *Get();

private:
    static const void Parse();

private:
    // character buffer for the command line
    static char *cmdLine;
};
