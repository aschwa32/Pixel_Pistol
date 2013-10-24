#include <string>
#include <stdexcept>
#include <memory>
#include <iostream>

#if defined(_MSC_VER)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

class Patch{};

class Picture_Box: public Patch{
private:
	SDL_Texture * m_texture;
public:
	void Init(SDL_Texture *tex){
		m_texture = tex;
	}
};
