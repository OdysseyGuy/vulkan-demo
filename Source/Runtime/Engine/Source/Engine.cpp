#include <iostream>
#include "Engine.h"
#include "Delegates/Delegates.h"

Engine *Engine::instance = nullptr;
bool IsExitRequested = false;

void Engine::Init(const std::string &inCommandLine)
{
    if (instance != nullptr) {
        std::cout << "Trying to multiple instance of Engine." << std::endl;
    }

    instance = this;

    std::cout << "Begining engine initialization." << std::endl;

    this->commandLine = inCommandLine;
    f();
}

void Engine::Tick()
{
}
