//
//  main.cpp
//  Particle
//
//  Created by Edric.Dang on 15/8/18.
//  Copyright © 2018 Edric.Dang. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.hpp"

using namespace std;
using namespace colorchange;

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    
    Screen *screen = new Screen;
    if(!(screen->init())){
        
    };
    
    Swarm swarm;
    
    
    while (true) {
        int tick = SDL_GetTicks();
        swarm.update(tick);
        
        unsigned char red = (1 + sin(tick*0.0001)) * 128;
        unsigned char green = (1 + sin(tick*0.0002)) * 128;
        unsigned char blue = (1 + sin(tick*0.0003)) * 128;
        
//        for(int y = 0; y < Screen::SCREEN_HEIGHT; y++){
//            for(int x = 0; x < Screen::SCREEN_WIDTH; x++){
//                screen->setPixel(x, y, red, green, blue);
//            }
//        }
        const Particle * const pParticles = swarm.getParticles();
        for(int i =0; i <Swarm::NPARTICLES;i++){
            Particle particle = pParticles[i];
            int x = (particle.x +1) * Screen::SCREEN_WIDTH/2 ;
            int y = (particle.y +1) * Screen::SCREEN_HEIGHT/2;
            screen->setPixel(x, y, red, green, blue);
        }
        
        
        screen->boxBlur();
        
        screen->update();
        
        
        if((screen->process_event()) == false){
            break;
        }
    }
    screen->close();
    
    return 0;
}
