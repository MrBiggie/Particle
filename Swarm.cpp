//
//  Swarm.cpp
//  Particle
//
//  Created by Edric.Dang on 16/8/18.
//  Copyright © 2018 Edric.Dang. All rights reserved.
//

#include "Swarm.hpp"
namespace colorchange{
    
    Swarm::Swarm() : lastime(0){
        pParticles = new Particle[NPARTICLES];
    }
    
    Swarm::~Swarm(){
        delete [] pParticles;
    }
    void Swarm:: update(int tick){
        int interval = tick - lastime;
        for(int i = 0; i < Swarm::NPARTICLES; i++){
            pParticles[i].update(interval);

        }
        lastime = tick;
    }
}
