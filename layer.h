#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <memory>

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif


class Layer{
private:


public:
	struct Frame_List{
		int f_frame_type;
			/* 0 image frame
			   1 text frame
			   2 pixel frame*/
		SDL_Rect f_frame;
		Patch * f_patch;
		int f_id;
		Frame_List *next;
	};


	void Init(int frame_array_size);
	int Add_Frame(int frame_type, SDL_Rect &frame, SDL_Texture *tex);
	void Update_Frame(int frame_type, SDL_Rect &frame, SDL_Texture *tex,int id);

	void Append_List(Frame_List *c_frame_link, int frame_type, SDL_Rect &frame, SDL_Texture *tex, int id);
	Frame_List* Find(Frame_List *c_frame_link, int id);

private:

	int m_frame_count;
	int m_active_frame_count;

	Frame_List m_frame_list;

	int m_frame_array_size;
	Frame_List* m_frame_array;



};

#endif
