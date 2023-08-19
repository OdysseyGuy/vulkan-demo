#include "Linux/LinuxPlatform.h"

#include "SDL3/SDL.h"

bool IsSDLInitialized = false;

bool LinuxPlatform::InitSDL()
{
    if (!IsSDLInitialized) {
        if (SDL_Init(SDL_INIT_EVERYTHING ^ SDL_INIT_AUDIO) != 0) {
            return false;
        }

        SDL_version compileVersion;
        SDL_version runtimeVersion;
        SDL_VERSION(&compileVersion);
        SDL_GetVersion(&runtimeVersion);
        const char *sldRevision = SDL_GetRevision();

        IsSDLInitialized = true;
    }

    return true;
}

bool LinuxPlatform::CopyToClipboard(const char *data)
{
    if (SDL_WasInit(SDL_INIT_VIDEO) && SDL_SetClipboardText(data)) {
        return false;
    }
}

bool LinuxPlatform::PasteFromClipboard(std::string &data)
{
    char *clipboardData;
    clipboardData = SDL_GetClipboardText();

    if (!clipboardData) {
        data = "";
    } else {
        data = std::string(clipboardData);
    }

    SDL_free(clipboardData);
}
