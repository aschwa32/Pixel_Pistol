#include <string>
#include <stdexcept>
#include <memory>

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

#include "window.h"
//Initialize the unique_ptr's deleters here

/*mWindow*/
std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> Window::mWindow
			= std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);

/*mRenderer*/
std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> Window::mRenderer
			= std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);

//Other static members
SDL_Rect Window::mBox;

void Window::Init(std::string title){

	//initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error("SDL Init Failed");
	if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");
	 
	//Setup our window size
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = 640;
	mBox.h = 480;

	//Create our window
	mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, mBox.w, mBox.h, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE));

	//Make sure it created ok
	if (mWindow == nullptr)
		throw std::runtime_error("Failed to create window");
	 
	//Create the renderer
	mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	//Make sure it created ok
	if (mRenderer == nullptr)
		throw std::runtime_error("Failed to create renderer");
}

void Window::Resize(int w, int h){
	mBox.w = w;
	mBox.h = h;

	/*mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));*/
	return;
}

void Window::Quit(){
	TTF_Quit();
	SDL_Quit();
}

void Window::Draw(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle,
			int xPivot, int yPivot, SDL_RendererFlip flip){

	//Convert pivot pos from relative to object's center to screen space
	xPivot += dstRect.w / 2;
	yPivot += dstRect.h / 2;
	//SDL expects an SDL_Point as the pivot location
	SDL_Point pivot = { xPivot, yPivot };
	//Draw the texture
	SDL_RenderCopyEx(mRenderer.get(), tex, clip, &dstRect, angle, &pivot, flip);
}

SDL_Texture* Window::LoadImage(const std::string &file){
	SDL_Texture *tex = nullptr;
	tex = IMG_LoadTexture(mRenderer.get(), file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
	return tex;
}

SDL_Texture* Window::RenderText(const std::string &message, const std::string &fontFile,
			SDL_Color color, int fontSize){
	//Open the font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer.get(), surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	 
	return texture;
}

SDL_Texture* Window::ColorSquare(int width, int height, int r, int g, int b, int a){
	SDL_PixelFormat *fmt;
	Uint32 color;

	SDL_Surface *surf = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
	fmt = surf->format;
	color = SDL_MapRGBA(fmt,r,g,b,a);
	SDL_FillRect(surf,NULL,color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer.get(), surf);
	SDL_FreeSurface(surf);
	return texture;
}

void Window::Clear(){
	SDL_RenderClear(mRenderer.get());
}

void Window::Present(){
	SDL_RenderPresent(mRenderer.get());
}

SDL_Rect Window::Box(){
	//Update mBox to match the current window size
	SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h);
	return mBox;
}

SDL_Rect Window::Create_Frame(double left, double top, double right, double bottom){

	int x,y,w_size,h_size;
	SDL_Rect frame;

	x = (int)(left*Window::Box().w);
	y = (int)(top*Window::Box().h);
	w_size = (int)((1-left-right)*Window::Box().w);
	h_size = (int)((1-top-bottom)*Window::Box().h);

	frame = {x,y,w_size,h_size};

	return frame;
}

bool Window::In_Frame(int x,int y,SDL_Rect frame){
	bool ins = false;
	if(x>frame.x && x<frame.x+frame.w && y>frame.y && y<frame.y+frame.h){
		ins = true;
	}

	return ins;
}

bool Window::Out_Frame(int x,int y,SDL_Rect frame){
	/*simply using !In_Frame doesnt work for some reason*/
	bool ins = false;
	if(In_Frame(x,y,mBox))
		ins = true;
	if(x>frame.x && x<frame.x+frame.w && y>frame.y && y<frame.y+frame.h){
		ins = false;
	}

	return ins;
}








