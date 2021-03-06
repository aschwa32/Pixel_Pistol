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

#include "layer.h"
void Layer::Init(int frame_array_size){
	m_frame_array_size = frame_array_size;
	m_frame_array = new Frame_List[m_frame_array_size];
}

int Layer::Add_Frame(int frame_type, SDL_Rect &frame, SDL_Texture *tex){
	Append_List(&(m_frame_array[(m_frame_count)%m_frame_array_size]),frame_type,frame,tex, m_frame_count);
	m_frame_count++;
	return (m_frame_count - 1);
}

void Layer::Update_Frame(int frame_type, SDL_Rect &frame, SDL_Texture *tex,int id){
	Frame_List* item = Find(&(m_frame_array[(id)%m_frame_array_size]), id);
	item->f_frame_type = frame_type;
	item->f_frame = frame;
	item->f_tex = tex;
	
	
}

void Layer::Append_List(Frame_List *c_frame_link, int frame_type, SDL_Rect &frame, SDL_Texture *tex, int id){
	if(c_frame_link->next == NULL){
		m_frame_list = {frame_type,frame,tex,};
	}else{
		Append_List(c_frame_link->next,frame_type,frame,tex, m_frame_count);
	}
}

Layer::Frame_List* Layer::Find(Frame_List *c_frame_link, int id){
	if(c_frame_link->f_id == id){
		return c_frame_link;
	}else if(c_frame_link->next == NULL){
		return NULL;
	}else{
		return Find(c_frame_link->next,id);
	}
}


