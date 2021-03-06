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

#include "text_box.h"

/*Text_Box::Text_Box(){
	
}*/
void Text_Box::Init(SDL_Rect &frame){
	m_frame = frame;
	m_font_size = frame.h;
	font=TTF_OpenFont("./font/SourceSansPro-Regular.ttf", m_font_size);

	m_font_w = (int)(m_font_size*m_aspect_ratio)+2;

	m_lines = m_frame.h/(m_font_size+m_line_spacing);
	m_w_chars = m_frame.w/m_font_w;

	m_max_chars = m_lines*m_w_chars;
}
void Text_Box::Init(SDL_Rect &frame, int size){
	m_frame = frame;
	m_font_size = size;
	font=TTF_OpenFont("./font/SourceSansPro-Regular.ttf", m_font_size);

	m_font_w = (int)(m_font_size*m_aspect_ratio)+2;

	m_lines = m_frame.h/(m_font_size+m_line_spacing);
	m_w_chars = m_frame.w/m_font_w;

	m_max_chars = m_lines*m_w_chars;
}

string Text_Box::Get_Text(){
	string text;
	text.assign(m_characters,0,m_pos);
	return m_characters;
}

void Text_Box::Set_Max_Chars(int max){
	m_max_chars = max;
	return;
}



void Text_Box::Write(string chars){
	int length = chars.length();
	SDL_Rect letter_pos;
	SDL_Texture *current_letter;
	string letter("s");
	string font_file = "./font/SourceSansPro-Regular.ttf";

	for(int i=0;i<length && (m_pos+i)< m_max_chars;i++){
		letter_pos = {m_frame.x + ((m_pos+ i)%m_w_chars)*(m_font_w),m_frame.y + ((m_pos + i)/m_w_chars)*m_font_size,
						m_font_w,m_font_size };
		letter.replace(0,1,chars,i,1);
		current_letter = Window::RenderText(letter, font_file, m_text_color, 25);
		Window::Draw(current_letter, letter_pos, NULL, 0);
	}

	m_characters.replace(m_pos,length,chars);
	if(m_pos+length<=(m_lines*m_w_chars-1)){
		m_pos = m_pos +length;
	}else{
		m_pos = m_lines*m_w_chars-1;
	}

	return;
}

void Text_Box::Write(string chars, SDL_Color color){
	int length = chars.length();
	SDL_Rect letter_pos;
	SDL_Texture *current_letter;
	string letter("s");
	string font_file = "./font/SourceSansPro-Regular.ttf";

	for(int i=0;i<length && (m_pos+i)< m_max_chars;i++){
		letter_pos = {m_frame.x + ((m_pos+ i)%m_w_chars)*(m_font_w),m_frame.y + ((m_pos + i)/m_w_chars)*m_font_size,
						m_font_w,m_font_size };
		letter.replace(0,1,chars,i,1);
		current_letter = Window::RenderText(letter, font_file, color, 25);
		Window::Draw(current_letter, letter_pos, NULL, 0);
	}

	m_characters.replace(m_pos,length,chars);
	if(m_pos+length<m_max_chars){
		m_pos = m_pos +length;
	}else{
		m_pos = m_lines*m_w_chars-1;
	}

	return;
}

void Text_Box::Backspace(){

	if(m_pos>0){
		SDL_Texture* sqr;
		sqr = Window::ColorSquare(10,10,m_bg_color.r,m_bg_color.g,m_bg_color.b,m_bg_color.a);
		SDL_Rect letter_pos = {m_frame.x + ((m_pos-1)%m_w_chars)*(m_font_w),m_frame.y + ((m_pos -1)/m_w_chars)*m_font_size,
							m_font_w,m_font_size };
		Window::Draw(sqr, letter_pos, NULL, 0);
		m_pos = m_pos - 1;
	}
	return;
	
}

void Text_Box::Overwrite(string chars){
	int length = chars.length();
	SDL_Rect letter_pos;
	SDL_Texture *current_letter;
	string letter("s");
	string font_file = "./font/SourceSansPro-Regular.ttf";

	/*clear frame*/
	SDL_Texture* sqr;
	sqr = Window::ColorSquare(10,10,m_bg_color.r,m_bg_color.g,m_bg_color.b,m_bg_color.a);
	Window::Draw(sqr, m_frame, NULL, 0);
	m_pos = 0;


	for(int i=0;i<length && (m_pos+i)<m_max_chars;i++){
		letter_pos = {m_frame.x + ((m_pos+ i)%m_w_chars)*(m_font_w),m_frame.y + ((m_pos + i)/m_w_chars)*m_font_w,
						m_font_w,m_font_size };
		letter.replace(0,1,chars,i,1);
		current_letter = Window::RenderText(letter, font_file, m_text_color, 25);
		Window::Draw(current_letter, letter_pos, NULL, 0);
	}

	m_characters.assign(chars,0,length);
	if(length<m_max_chars){
		m_pos = length;
	}else{
		m_pos = m_max_chars;
	}


	return;
}

bool Text_Box::Over_Edit(){
	/*Overwrites and edits box with user input*/
	/*exits program when close window clicked*/
	/*exits box when click outside, press enter, or fill box*/
	bool quit = false;
	bool exit = false;
	SDL_Event e;
	string str("");
	Overwrite(str);
	while(!exit && m_pos < m_max_chars){

		while (SDL_PollEvent(&e)){

			if(e.type == SDL_QUIT){
					quit = true;
					exit = true;
				}

			if(e.type == SDL_KEYDOWN){
					if(e.key.keysym.sym == SDLK_0){
						string input("0");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_1){
						string input("1");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_2){
						string input("2");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_3){
						string input("3");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_4){
						string input("4");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_5){
						string input("5");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_6){
						string input("6");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_7){
						string input("7");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_8){
						string input("8");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_9){
						string input("9");
						Write(input,m_text_color);
					}
					if(e.key.keysym.sym ==SDLK_RETURN){
						exit = true;
					}

					if(e.key.keysym.sym ==SDLK_BACKSPACE){
						Backspace();
					}
				}

				if(e.type == SDL_MOUSEBUTTONDOWN){
					if(Window::Out_Frame(e.button.x,e.button.y,m_frame)){
						exit = true;
					}
				}
			}

			Window::Present();
	}

	

	return quit;
}


