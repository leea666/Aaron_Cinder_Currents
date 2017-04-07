//
//  Button.cpp
//  week10
//
//  Created by Aaron Lee on 4/4/17.
//
//

#include "Button.h"


ButtonRef Button::create(float radius, ci::gl::TextureRef texture1, ci::gl::TextureRef texture2) {
    ButtonRef ref = std::shared_ptr<Button>(new Button()) ;
    ref ->setup(radius, texture1, texture2) ;
    return ref ;
}

Button::Button()
: mRadius(0.f),
mColor(ci::Color(0.f, 0.f, 0.f)),
mActColor(ci::Color::white()),
isAct(true)
{
    
}

void Button::setup(float radius, ci::gl::TextureRef texture1, ci::gl::TextureRef texture2) {
    mRadius = radius ;
    mTexture = texture1 ;
    mActTexture = texture2 ;
    isAct = true ;
    
    addBackground() ;
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Button::onMouseEvent, this, std::placeholders::_1)) ;
}

void Button::addBackground() {
    mCircle = po::scene::Shape::createCircle(mRadius * 2.f) ;
    mCircle->setPosition(glm::vec2(0.f, 0.f)) ;
//    mCircle->setFillColor(mColor) ;
    mCircle->setTexture(mTexture) ;
    
    addChild(mCircle) ;
}


void Button::onMouseEvent(po::scene::MouseEvent &event) {
    switch(event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            isAct = !isAct;
//            std::cout << "This switch happened" << std::endl ;
            if(isAct) {
//                ci::app::timeline().apply(&mCircle->getFillColorAnim(), mActColor, animTime, ci::EaseOutExpo()) ;
//                mCircle->setTexture(mActButtonTexture) ;
                mCircle->setTexture(mTexture) ;
            } else {
//                ci::app::timeline().apply(&mCircle->getFillColorAnim(), mColor, animTime, ci::EaseOutExpo()) ;
                mCircle->setTexture(mActTexture) ;
//                mCircle->setTexture(mButtonTexture) ;
            }
            break ;
        default:
            break ;
    }

}
