//
//  Particle.hpp
//  WindParticles
//
//  Created by Aaron Lee on 2/18/17.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>

#pragma once


class Particle ;

typedef std::shared_ptr<Particle> ParticleRef ;

class Particle {
public:
    static ParticleRef create(glm::vec2 position, float lifespan, glm::vec2 acceleration) ;
    void update() ;
    void applyForce(glm::vec2 force) ;
    float getTimerLeft() ;
    float getLifeSpan(){return mLifespan;} ;
    glm::vec2 getPosition(){return mPosition;}
    ~Particle() ;
    
private:
    Particle() ;
    void setup(glm::vec2 position, float lifespan, glm::vec2 acceleration) ;
    glm::vec2 mPosition ;
    float mFriction ;
    float mLifespan ;
    glm::vec2 mVelocity ;
    glm::vec2 mAcceleration ;
    
    ci::Timer mTimer ;
    
};


#endif /* Particle_hpp */
