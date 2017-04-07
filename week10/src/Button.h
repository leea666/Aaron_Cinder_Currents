//
//  Button.hpp
//  week10
//
//  Created by Aaron Lee on 4/4/17.
//
//

#pragma once

#include "poNodeContainer.h"
#include "poShape.h"

class Button ;
typedef std::shared_ptr<Button> ButtonRef ;

class Button : public po::scene::NodeContainer {
    
public:
    static ButtonRef create(float radius, ci::gl::TextureRef texture1, ci::gl::TextureRef texture2) ;
    bool        isAct ;
    
private:
    Button() ;
    void setup(float radius, ci::gl::TextureRef texture1, ci::gl::TextureRef texture2) ;
    void addBackground() ;
    void onMouseEvent(po::scene::MouseEvent &event) ;

    
    po::scene::ShapeRef     mCircle ;
    po::scene::ShapeRef     mPopOut ;
    
    float       mRadius ;
    ci::Color   mColor ;
    ci::Color   mActColor ;
    ci::gl::TextureRef mTexture ;
    ci::gl::TextureRef mActTexture ;
    ci::gl::TextureRef  mButtonTexture = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset("Button.png"))) ;
    ci::gl::TextureRef  mActButtonTexture = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset("ButtonAct.png"))) ;
    
    
    float       animTime = 0.5f ;
    
};
