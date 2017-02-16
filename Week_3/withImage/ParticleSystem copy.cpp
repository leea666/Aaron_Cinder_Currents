//
//  ParticleSystem.cpp
//  week3
//
//  Created by Aaron Lee on 2/12/17.
//
//

#include "ParticleSystem.hpp"
#include "cinder/Rand.h"

ParticleSystem::ParticleSystem() {
    mParticleNum = 0 ;
    mRange = 10.f ;
    mRepulsionFactor = 0.05f ;
    
    for(int i = 0 ; i < mParticleNum ; i++) {
        //push particles into your array
        
    }
}

void ParticleSystem::gravity() {
    for(auto& p:mParticles) {
        p.applyForce(glm::vec2(0, ci::randFloat(0,1))) ;
        applyingForce = ci::randFloat(1,10) ;
        p.movement = p.movement + applyingForce ;
    }
}



void ParticleSystem::setup() {
    
}

void ParticleSystem::draw() {
    for(auto& p: mParticles) {
        p.draw() ;
    }
}

void ParticleSystem::update() {
        Particle singleParticle(ci::randFloat(0, 1280), 0.f);
        gravity() ;
        mParticles.push_back(singleParticle) ;
        mParticleNum++ ;

    for(int i = 0 ; i < mParticles.size() ; i++) {
        for(int j = 0 ; j < mParticles.size(); j++) {
            if (i == j ) {continue;}
            //repel from each other
            float distanceDiff = ci::length(mParticles[i].getPosition() - mParticles[j].getPosition()) ;
            if(distanceDiff < 5.f) {
                glm::vec2 repulsion = (mParticles[i].getPosition() - mParticles[j].getPosition()) * glm::vec2(mRepulsionFactor);
                mParticles[i].applyForce(repulsion) ;
            }
        }
    }
    for(auto& p: mParticles) {
        p.update() ;
        if(mParticleNum >= 300) {
            for(int i = 0 ; i < 150 ; i++) {
                mParticles.erase(mParticles.begin()) ;
                mParticleNum-- ;
            }
        }
    }
    
}
