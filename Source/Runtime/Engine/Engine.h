#pragma once

#include <string>
#include <functional>

class Engine
{
public:
    Engine()
    {
    }

    Engine(Engine &) = delete;

    void Init(const std::string &commandLine);
    void Tick();

    static Engine *GetInstance()
    {
        return instance;
    }

private:
    std::string commandLine;

    static Engine *instance;
};

extern bool IsExitRequested;

inline bool GetIsExitRequested()
{
    return IsExitRequested;
}

// void f()
// {
//     auto a = std::mem_fn(&Engine::Tick);
//     std::apply();
//     auto f = std::bind(&Engine::Init, _1);
// }
