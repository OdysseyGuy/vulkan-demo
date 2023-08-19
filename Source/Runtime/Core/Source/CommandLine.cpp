#include "CommandLine.h"

char *CommandLine::cmdLine = {};

const char *CommandLine::Get()
{
    return cmdLine;
}
