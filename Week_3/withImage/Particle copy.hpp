//
//  Particle.hpp
//  week3
//
//  Created by Aaron Lee on 2/12/17.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#pragma once

class Particle {
    
public:
    Particle(float startPosX, float startPosY) ;
    void setup() ;
    void update() ;
    void draw() ;
    void applyForce(glm::vec2 force) ;
    glm::vec2 getPosition() ;
    void bounceForce(float damping, bool isVertical) ;
    float movement ;

    
private:
    float mFriction ;
    cinder::gl::TextureRef  mTexture ;
    glm::vec2 mPosition ;
    glm::vec2 mVelocity ;
    glm::vec2 mAcceleration ;
    float posX ;
    float posY ;
};


#endif /* Particle_hpp */
