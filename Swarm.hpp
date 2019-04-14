//
//  Swarm.hpp
//  Particle
//
//  Created by Edric.Dang on 16/8/18.
//  Copyright © 2018 Edric.Dang. All rights reserved.
//

#ifndef Swarm_hpp
#define Swarm_hpp

#include <stdio.h>
#include "Particle.hpp"

namespace colorchange{
    class Swarm{
    public:
        const static int NPARTICLES = 5000;
    private:
        Particle *pParticles;
        int lastime;
        
    public:
        Swarm();
        virtual ~Swarm();
        const Particle *getParticles(){return pParticles;};
        void update(int tick);
    };
    
    
    
}

#endif /* Swarm_hpp */
