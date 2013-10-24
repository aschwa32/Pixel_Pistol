#include <stdexcept>
#include <string>
#include <iostream>

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "window.cpp"
#include "matrix_to_im.h"
#include "text_box.cpp"

using namespace std;
/*mouse vairables*/
int mouse_x,mouse_y;
/*page_size*/
int w_pixels, h_pixels;
bool page_mouse_down = false;
/*current color*/
Uint8 r_color2,g_color2,b_color2;

/*frames*/
SDL_Rect p_frame, l_frame, c_frame, s_frame;
SDL_Rect r_frame, r_text_frame, r_text_frame2;
SDL_Rect g_frame, g_text_frame, g_text_frame2;
SDL_Rect b_frame, b_text_frame, b_text_frame2;

Text_Box msg,smsg,rmsg,gmsg,bmsg,rmsg2,gmsg2,bmsg2;

/*pixels sizes*/
int w_sqr_size,h_sqr_size;

/*color matrix*/
SDL_Color** colors;


/*color bar*/
SDL_Texture *cbarmsg;


void make_frames();
void draw_all();

int main(){

	/*initialize window*/
	try {
		Window::Init("Pixel Pistol");
	}
	catch (const std::runtime_error &e){
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}

	/*initialize parameters*/
	/*page vairables*/
	h_pixels = 64;
	w_pixels = 64;
	

	r_color2 = 255;
	g_color2 = 0;
	b_color2 = 0;

	/*set frames*/
	make_frames();	

	/*program variables*/
	bool quit = false;
	SDL_Texture *sqr;
	SDL_Event e;
	int cx,cy;
	SDL_Rect pos;
	int c_scale;



	/*pixel matrix*/
	colors = new SDL_Color*[h_pixels];
	for(int i = 0;i<h_pixels;i++){
		colors[i] = new SDL_Color[w_pixels];
		for(int j=0;j<w_pixels;j++){
			colors[i][j] = {255,255,255,255};
		}
	}

	/*image*/
	unsigned char*** image = new unsigned char**[h_pixels];
	for(int i=0;i<h_pixels;i++){
		image[i] = new unsigned char*[w_pixels];
		for(int j=0;j<w_pixels;j++){
			image[i][j] = new unsigned char[4];		
		}
	}
	


	/*do some text stuff*/
	string fontFile = "./font/SourceSansPro-Regular.ttf";
	SDL_Color color = { 255, 255, 255 };
	try {
		cbarmsg = Window::RenderText("0<---->255", fontFile, color, 25);
	}
	catch (const std::runtime_error &e){
		//Catch error and crash
		std::cout << e.what() << std::endl;
		Window::Quit();
		return -1;
	}


	draw_all();

	/*set max size for input color text*/
	rmsg2.Set_Max_Chars(3);
	gmsg2.Set_Max_Chars(3);
	bmsg2.Set_Max_Chars(3);




	/*program loop*/
	while(!quit){

		while (SDL_PollEvent(&e)){

			if(!page_mouse_down){
			switch(e.type){

				case SDL_QUIT: quit = true;
	
				case SDL_KEYDOWN:{
					switch(e.key.keysym.sym){
						
						case SDLK_ESCAPE: quit = true;
			
					}
				}

				case SDL_MOUSEBUTTONDOWN:{

					/*page frame*/
					if(Window::In_Frame(e.button.x,e.button.y,p_frame)){
						cy = (int)((e.button.y-p_frame.y)/h_sqr_size);
						cx = (int)((e.button.x-p_frame.x)/w_sqr_size);
						colors[cy][cx] = {r_color2,g_color2,b_color2,255};

						pos = { p_frame.x+w_sqr_size*cx,p_frame.y+h_sqr_size*cy,w_sqr_size, h_sqr_size };

						sqr = Window::ColorSquare(1,1,colors[cy][cx].r,colors[cy][cx].g,colors[cy][cx].b,colors[cy][cx].a);
						Window::Draw(sqr,pos,NULL,0);
						page_mouse_down = true;
					}

					/*red scale*/
					if(Window::In_Frame(e.button.x,e.button.y,r_text_frame)){
					
						c_scale = (int)(((double)(e.button.x-r_text_frame.x)/r_text_frame.w)*255);
						r_color2 = c_scale;

						sqr = Window::ColorSquare(10,10,r_color2,g_color2,b_color2,255);
						Window::Draw(sqr, c_frame, NULL, 0);

						rmsg2.Overwrite(to_string(r_color2));
					}

					if(Window::In_Frame(e.button.x,e.button.y,r_text_frame2)){

						rmsg2.Over_Edit();
						if(atoi(rmsg2.Get_Text().c_str())>255){
							rmsg2.Overwrite(to_string(255));
						}
						r_color2 = atoi(rmsg2.Get_Text().c_str());

						sqr = Window::ColorSquare(10,10,r_color2,g_color2,b_color2,255);
						Window::Draw(sqr, c_frame, NULL, 0);
					}

					/*green scale*/
					if(Window::In_Frame(e.button.x,e.button.y,g_text_frame)){
					
						c_scale = (int)(((double)(e.button.x-g_text_frame.x)/g_text_frame.w)*255);
						g_color2 = c_scale;

						sqr = Window::ColorSquare(10,10,r_color2,g_color2,b_color2,255);
						Window::Draw(sqr, c_frame, NULL, 0);

						gmsg2.Overwrite(to_string(g_color2));
					}

					if(Window::In_Frame(e.button.x,e.button.y,g_text_frame2)){

						gmsg2.Over_Edit();
						if(atoi(gmsg2.Get_Text().c_str())>255){
							gmsg2.Overwrite(to_string(255));
						}
						g_color2 = atoi(gmsg2.Get_Text().c_str());

						sqr = Window::ColorSquare(10,10,r_color2,g_color2,b_color2,255);
						Window::Draw(sqr, c_frame, NULL, 0);
					}

					/*blue scale*/
					if(Window::In_Frame(e.button.x,e.button.y,b_text_frame)){
					
						c_scale = (int)(((double)(e.button.x-b_text_frame.x)/b_text_frame.w)*255);
						b_color2 = c_scale;

						sqr = Window::ColorSquare(10,10,r_color2,g_color2,b_color2,255);
						Window::Draw(sqr, c_frame, NULL, 0);

						bmsg2.Overwrite(to_string(b_color2));
					}

					if(Window::In_Frame(e.button.x,e.button.y,b_text_frame2)){

						bmsg2.Over_Edit();
						if(atoi(bmsg2.Get_Text().c_str())>255){
							bmsg2.Overwrite(to_string(255));
						}
						b_color2 = atoi(bmsg2.Get_Text().c_str());

						sqr = Window::ColorSquare(10,10,r_color2,g_color2,b_color2,255);
						Window::Draw(sqr, c_frame, NULL, 0);
					}

					/*save*/
					if(Window::In_Frame(e.button.x,e.button.y,s_frame)){

						for(int i=0;i<h_pixels;i++){
							for(int j=0;j<w_pixels;j++){
								image[h_pixels-i-1][j][0] = (unsigned char)(colors[i][j].b);
								image[h_pixels-i-1][j][1] = (unsigned char)(colors[i][j].g);
								image[h_pixels-i-1][j][2] = (unsigned char)(colors[i][j].r);
								image[h_pixels-i-1][j][3] = (unsigned char)(colors[i][j].a);
							}
						}

						matrix_to_im(w_pixels,h_pixels, image);

					}
					
				}

				case SDL_WINDOWEVENT:{
					switch (e.window.event)  {
						case SDL_WINDOWEVENT_SIZE_CHANGED:  {

							Window::Resize(e.window.data1,e.window.data2);
							make_frames();
							draw_all();
                			break;
             			}

					}

				}
			}}else{
				if(e.type == SDL_MOUSEBUTTONUP){
					page_mouse_down = false;
				}
				SDL_GetMouseState(&mouse_x, &mouse_y);
				
				cy = (int)((mouse_y-p_frame.y)/h_sqr_size);
				cx = (int)((mouse_x-p_frame.x)/w_sqr_size);
				if(cy>=0&&cx>=0&&cy<h_pixels&&cx<w_pixels){
				if(!(colors[cy][cx].r == r_color2 && colors[cy][cx].g == g_color2 
					&& colors[cy][cx].b ==b_color2 && colors[cy][cx].a ==255)){
					colors[cy][cx] = {r_color2,g_color2,b_color2,255};

					pos = { p_frame.x+w_sqr_size*cx,p_frame.y+h_sqr_size*cy,w_sqr_size, h_sqr_size };

					sqr = Window::ColorSquare(1,1,colors[cy][cx].r,colors[cy][cx].g,colors[cy][cx].b,colors[cy][cx].a);
					Window::Draw(sqr,pos,NULL,0);
					page_mouse_down = true;
				}}
				
			}
		}

	
		Window::Present();
	}

	Window::Quit();
}

void make_frames(){
	/*create frames based on current window size*/
	p_frame = Window::Create_Frame(.05,.2,.25,.05);
	l_frame = Window::Create_Frame(.05,.05,.05,.85);
	c_frame = Window::Create_Frame(.75,.8,.15,.15);
	s_frame = Window::Create_Frame(.75,.90,.15,.05);
	r_frame = Window::Create_Frame(.75,.2,.15,.75);
	r_text_frame = Window::Create_Frame(.75,.25,.15,.70);
	r_text_frame2 = Window::Create_Frame(.75,.30,.15,.65);
	g_frame = Window::Create_Frame(.75,.4,.15,.55);
	g_text_frame = Window::Create_Frame(.75,.45,.15,.5);
	g_text_frame2 = Window::Create_Frame(.75,.5,.15,.45);
	b_frame = Window::Create_Frame(.75,.6,.15,.35);
	b_text_frame = Window::Create_Frame(.75,.65,.15,.3);
	b_text_frame2 = Window::Create_Frame(.75,.7,.15,.25);

	/*touch-up p_frame*/
	p_frame = {p_frame.x,p_frame.y,((int)(p_frame.w/w_pixels))*w_pixels,((int)(p_frame.h/h_pixels))*h_pixels};

	return;
}

void draw_all(){
	SDL_Texture *sqr;
	SDL_Rect pos;

	Window::Clear();
	msg.Init(l_frame);
	smsg.Init(s_frame);
	rmsg.Init(r_frame);
	gmsg.Init(g_frame);
	bmsg.Init(b_frame);
	rmsg2.Init(r_text_frame2);
	gmsg2.Init(g_text_frame2);
	bmsg2.Init(b_text_frame2);
	msg.Overwrite("P I X E L  P I S T O L");
	smsg.Overwrite("S A V E");
	rmsg.Overwrite("Red");
	gmsg.Overwrite("Green");
	bmsg.Overwrite("Blue");
	rmsg2.Overwrite(to_string(r_color2));
	gmsg2.Overwrite(to_string(g_color2));
	bmsg2.Overwrite(to_string(b_color2));

	Window::Draw(cbarmsg, r_text_frame, NULL, 0);
	Window::Draw(cbarmsg, g_text_frame, NULL, 0);
	Window::Draw(cbarmsg, b_text_frame, NULL, 0);

	sqr = Window::ColorSquare(10,10,r_color2,g_color2,b_color2,255);
	Window::Draw(sqr, c_frame, NULL, 0);

	/*initialize page squares*/
	w_sqr_size = p_frame.w/w_pixels;
	h_sqr_size = p_frame.h/h_pixels;
	for(int i=0;i<h_pixels;i++){
		for(int j=0;j<w_pixels;j++){
			pos = { p_frame.x+w_sqr_size*j,
				p_frame.y+h_sqr_size*i,
				w_sqr_size, h_sqr_size };
			sqr = Window::ColorSquare(10,10,colors[i][j].r,colors[i][j].g,colors[i][j].b,colors[i][j].a);
			Window::Draw(sqr,pos,NULL,0);
		}
	}

}



