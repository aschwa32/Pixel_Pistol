#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <string>
#include <memory>

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "patch.cpp"

class Text_Box: public Patch{
public:
	void Init(SDL_Rect &frame);
	void Init(SDL_Rect &frame, int size);

	void Set_Frame();
	string Get_Text();
	void Set_Max_Chars(int max);

	void Write(string chars);
	void Write(string chars, SDL_Color color);
	void Backspace();
	void Overwrite(string chars);

	bool Over_Edit();
	
private:
	int m_pos = 0;
	string m_characters;
	SDL_Color m_bg_color = {0,0,0,255};
	SDL_Color m_text_color = {255,255,255,255};

	double m_aspect_ratio = .30;
	int m_line_spacing = 0;
	int m_font_size;

	int m_font_w;
	int m_lines;
	int m_w_chars;
	int m_max_chars;

	SDL_Rect m_frame;
	TTF_Font *font;
};

#endif
