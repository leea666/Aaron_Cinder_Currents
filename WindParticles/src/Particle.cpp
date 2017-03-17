//
//  Particle.cpp
//  WindParticles
//
//  Created by Aaron Lee on 2/18/17.
//
//

#include "Particle.hpp"

ParticleRef Particle::create(glm::vec2 position, float lifespan, glm::vec2 acceleration) {
    ParticleRef ref = std::shared_ptr<Particle>(new Particle ()) ;
    ref->setup(position, lifespan, acceleration) ;
    return ref ;
}

Particle::Particle()
:mFriction(0.98f)
, mVelocity(glm::vec2(0))
, mAcceleration(glm::vec2(0)) {
    
}

void Particle::setup(glm::vec2 position, float lifespan, glm::vec2 acceleration) {
    mLifespan  = lifespan ;
    mPosition = position ;
    mAcceleration = acceleration ;
    mVelocity += mAcceleration;
    mTimer.start();
}

float Particle::getTimerLeft() {
    return (mLifespan - mTimer.getSeconds()) ;
}

void Particle::applyForce(glm::vec2 force) {
    mVelocity += force ;
}

void Particle::update() {
    mVelocity *= mFriction ;
    mPosition += mVelocity ;
}

Particle::~Particle() {
    mTimer.stop() ;
}
