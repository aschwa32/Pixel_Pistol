#ifndef PATCH_H
#define PATCH_H

#include <string>
#include <memory>

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Patch{
	
};
#endif
