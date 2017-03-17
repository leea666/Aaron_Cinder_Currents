//
//  ParticleSystem.hpp
//  week3
//
//  Created by Aaron Lee on 2/12/17.
//
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#pragma once
#include "Particle.hpp"

class ParticleSystem {
public:
    ParticleSystem() ;
    void setup() ;
    void update() ;
    void draw() ;
    void repulseFrom(glm::vec2 position) ;
    void bounceFromEdge() ;
    void gravity() ;
    
private:
    int mParticleNum ;
    std::vector<Particle> mParticles ;
    float mRange ;
    float mRepulsionFactor ;
    float applyingForce ;
};

#endif /* ParticleSystem_hpp */
