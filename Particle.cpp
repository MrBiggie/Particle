//
//  Particle.cpp
//  Particle
//
//  Created by Edric.Dang on 16/8/18.
//  Copyright © 2018 Edric.Dang. All rights reserved.
//

#include "Particle.hpp"
#include <stdlib.h>
#include <math.h>

namespace colorchange {
    Particle::Particle(): x(0) , y(0){
        init();
    }
    
    void Particle::init(){
        //        x = (2.0 * rand())/RAND_MAX - 1;
        //        y = (2.0 * rand())/RAND_MAX - 1;
        //        xspeed = 0.001 * (2.0 * rand()/RAND_MAX - 1);
        //        yspeed = 0.001 * (2.0 * rand()/RAND_MAX - 1);
        x = 0;
        y = 0;
        direction = 2.0 * M_PI * rand()/RAND_MAX ;
        speed = 0.04 * rand()/RAND_MAX;
        speed *= speed;
    }
    
    Particle::~Particle(){
        
    }
    
    void Particle::update(int interval){
        
        direction += interval * 0.0003;
        
        double xspeed = speed * cos(direction);
        double yspeed = speed * sin(direction);
        x += xspeed * interval;
        y += yspeed * interval;
        if (x < -1 || x > 1 || y < -1 || y > 1){
            init();
        }
//        if(x < -1.0 || x > 1.0){
//            xspeed = -xspeed;
//        }
//
//        if(y < -1.0 || y > 1.0){
//            yspeed = -yspeed;
//        }
        if(rand() < RAND_MAX / 100){
            init();
        }
    }
    
}
