//
//  Screen.cpp
//  Particle
//
//  Created by Edric.Dang on 15/8/18.
//  Copyright © 2018 Edric.Dang. All rights reserved.
//

#include "Screen.hpp"


namespace colorchange {
    
    Screen::Screen(){
        m_window = NULL;
        m_renderer = NULL;
        m_texture = NULL;
        pixel_buffer= NULL;
        pixel_buffer_later = NULL;
    }
    
    bool Screen::init(){
        if(SDL_Init(SDL_INIT_VIDEO) <0){
            std::cout << "Fail to init SDL" << std::endl;
            return false;
        }
        
        m_window =
        SDL_CreateWindow("EXPLOSION",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         SCREEN_WIDTH,
                         SCREEN_HEIGHT,
                         SDL_WINDOW_SHOWN);
        if (m_window == NULL){
            SDL_Quit();
            std::cout<< "Window not created" <<std::endl;
            return false;
        }
        
        
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH,SCREEN_HEIGHT);
        
        pixel_buffer = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];
        pixel_buffer_later = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];
        
        if (m_renderer == NULL||m_texture == NULL){
            SDL_Quit();
            std::cout<< "Window not created" <<std::endl;
            return false;
        }
        memset(pixel_buffer, 0, SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));
        memset(pixel_buffer_later, 0, SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));
        
        return true;
    }
    
    bool Screen::update(){
        SDL_UpdateTexture(m_texture, NULL, pixel_buffer, SCREEN_WIDTH*sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
        return true;
    }
    
    bool Screen::process_event(){
        SDL_Event sdl_event;
        
        while(SDL_PollEvent(&sdl_event)){
            if(sdl_event.type == SDL_QUIT){
                return false;
            }
        }
        
        return true;
    }
    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
        
        if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT){
            return;
        }
        Uint32 color = 0;
        color += red;
        color <<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;
        pixel_buffer[(y * SCREEN_WIDTH)+x] = color;
        
    }
    
    void Screen::boxBlur(){
        //swap the buffers so pixel is in buffer2 and we are drawing to buffer 1
        Uint32 *temp = pixel_buffer;
        pixel_buffer = pixel_buffer_later;
        pixel_buffer_later = temp;
        
    
        for(int y = 0; y < SCREEN_HEIGHT; y++){
            for(int x = 0; x < SCREEN_WIDTH; x++){
                /*
                 * 0 0 0
                 * 0 1 0
                 * 0 0 0
                 */
                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;
                
                for(int row = -1; row<= 1; row++){
                    for(int col = -1; col <= 1; col++){
                        int currentX = x + col;
                        int currentY = y + row;
                        if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT){
                            Uint32 color = pixel_buffer_later[currentY * SCREEN_WIDTH + currentX];
                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;
                            
                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }
                }
                
                Uint8 red = redTotal / 9;
                Uint8 green = greenTotal / 9;
                Uint8 blue = blueTotal / 9;
                setPixel(x, y, red, green, blue);
            }
        }
    }
    
//    void Screen::clear(){
//         memset(pixel_buffer, 0x00, SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));
//        memset(pixel_buffer_later, 0x00, SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));
//    }
    
    void Screen::close(){
        delete [] pixel_buffer;
        delete [] pixel_buffer_later;
        SDL_DestroyTexture(m_texture);
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
    
    
}
