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
    Particle(glm::vec2 startPos) ;
    void setup() ;
    void update() ;
    void draw() ;
    void applyForce(glm::vec2 force) ;
    glm::vec2 getPosition() ;
    void bounceForce(float damping, bool isVertical) ;
    
private:
    float mFriction ;
//    cinder::gl::TextureRef  mTexture = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset("IMG_3886.jpg"))) ;
    glm::vec2 mPosition ;
    glm::vec2 mVelocity ;
    glm::vec2 mAcceleration ;
};


#endif /* Particle_hpp */
