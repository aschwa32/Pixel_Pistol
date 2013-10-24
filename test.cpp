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
#include "layer.cpp"

int main(){

}
