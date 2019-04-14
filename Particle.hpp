//
//  Particle.hpp
//  Particle
//
//  Created by Edric.Dang on 16/8/18.
//  Copyright © 2018 Edric.Dang. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
namespace colorchange {
    struct Particle{
        double x;
        double y;
    private:
        double direction;
        double speed;
    private:
        void init();
    public:
        Particle();
        virtual ~Particle();
        void update(int interval);
    };
}


#endif /* Particle_hpp */
