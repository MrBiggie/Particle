//
//  Screen.hpp
//  Particle
//
//  Created by Edric.Dang on 15/8/18.
//  Copyright © 2018 Edric.Dang. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>

namespace colorchange {
    struct Screen{
        const static int SCREEN_WIDTH = 1000;
        const static int SCREEN_HEIGHT = 1000 ;
        
    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
        Uint32 *pixel_buffer;
        Uint32 *pixel_buffer_later;
    public:
        Screen();
        bool init();
        bool process_event();
        bool update();
        void setPixel(int x, int y, Uint8 red, Uint8 blue, Uint8 green);
        void boxBlur();
//        void clear();
        void close();
    };
}

#endif /* Screen_hpp */
