//
//  Particle.cpp
//  week3
//
//  Created by Aaron Lee on 2/12/17.
//
//

#include "Particle.hpp"


Particle::Particle(float startPosX, float startPosY) {
    mPosition = glm::vec2(startPosX, startPosY) ;
    posX = startPosX ;
    posY = startPosY ;
    movement = 0.f ;

    mFriction = 0.90 ;
    mVelocity = glm:: vec2(0.f, 0.f) ;
    mAcceleration = glm::vec2(0.f, 0.f) ;
    mTexture = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset("snowflake.png"))) ;

    
}

void Particle::setup() {
//    mTexture = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset("IMG_3886.jpg"))) ;
}

void Particle::bounceForce(float damping, bool isVerticle) {
    if(isVerticle) {
        mVelocity.y = -mVelocity.y * damping ;
    } else {
        mVelocity.x = -mVelocity.x * damping ;
    }
}


void Particle::draw() {
//    ci::gl::drawSolidCircle(mPosition, 1.f) ;
    cinder::gl::draw(mTexture, cinder::Rectf(0.f+posX, 0.f+posY+movement, 50.f+posX, 50.f+posY+movement)) ;
}

void Particle::update() {
    //add acc to vel
    mVelocity += mAcceleration ;
    //apply friction
    mVelocity *= mFriction ;
    //apply velocity to position
    mPosition += mVelocity ;
    
    //reset acceleration
    mAcceleration *= 0.f ;
}

void Particle::applyForce(glm::vec2 force) {
    //apply force to acceleration
    mAcceleration += force ;
}

glm::vec2 Particle::getPosition() {
    return mPosition ;
}
