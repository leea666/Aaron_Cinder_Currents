#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"
#include "cinder/CinderMath.h"
#include "cinder/CinderGlm.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class week5App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    ci::Anim<ci::vec2> mCircleOne, mCircleTwo, mCircleThree ;
    ci::Anim<float> mFactorX ;
    ci::Anim<float> mFactorY ;
    int counter = 0 ;
//    float time = 0 ;
//    int numCircles = 16;
    bool holder = true ;
    bool firstCell = false ;
    bool firstRound = true ;
//    float radius = getWindowHeight() / 2 - 30;
    
    float basicA = getAverageFps()*0.01f;
    float r = 125 ;
    float xPos = 0 ;
    float yPos = 0 ;
    ci::Anim<float> mOpacity ;
};

void week5App::setup()
{
    ci::app::setWindowSize(500, 500) ;
    mCircleOne = ci::vec2(0,0) ;
    mCircleTwo = mCircleOne ;
    mCircleThree = mCircleOne ;
    mFactorX = 1.0f ;
    mFactorY = 1.0f ;
    mOpacity = 1.0f ;
}

void week5App::mouseDown( MouseEvent event )
{
    firstRound = false ;
    
    if(counter == 0) {
        if(holder == true) {
            if(firstCell == true) {
                firstCell = false ;
            } else {
                firstCell = true ;
            }
            timeline().apply(&mFactorX, 2.f, 2.5f, ci::EaseOutExpo()) ;
            mOpacity = 1.0f ;
            timeline().apply(&mCircleOne, ci::vec2(125, 0), 5.0f, ci::EaseInOutBack()) ;
            timeline().apply(&mCircleTwo, ci::vec2(-125, 0), 5.0f, ci::EaseInOutBack()) ;
            timeline().appendTo(&mFactorX, 1.f, 2.5f) ;
            holder = false ;
        } else {
            counter++ ;
            holder = true ;
        }
    }else if(counter == 1) {
        if(holder == true) {
            timeline().apply(&mCircleOne, ci::vec2(125, -125), 5.0f, ci::EaseInSine()) ;
            timeline().apply(&mCircleTwo, ci::vec2(-125, 125), 5.0f, ci::EaseInSine()) ;
            holder = false ;
        } else {
            counter++ ;
            holder = true ;
        }
    } else if(counter == 2) {
        if(holder == true) {
            timeline().apply(&mCircleOne, ci::vec2(0, -125), 5.0f, ci::EaseInSine()) ;
            timeline().apply(&mCircleTwo, ci::vec2(0, 125), 5.0f, ci::EaseInSine()) ;
            holder = false ;
        } else {
            counter++ ;
            holder = true ;
        }
    }else if (counter == 3) {
        if(holder == true) {
            holder = false ;
        } else {
            counter++ ;
            holder = true ;
            mCircleOne = ci::vec2(0, 125) ;
            mCircleTwo = ci::vec2(0, -125) ;
        }
    }else if (counter == 4) {
        if(holder == true) {
            timeline().apply(&mCircleOne, ci::vec2(125, 0), 5.0f, ci::EaseInSine()) ;
            timeline().apply(&mCircleTwo, ci::vec2(-125, 0), 5.0f, ci::EaseInSine()) ;
            holder = false ;
        } else {
            counter++ ;
            holder = true ;
        }
    } else if(counter == 5) {
        if(holder == true) {
            timeline().apply(&mOpacity, 0.f, 5.0f, ci::EaseInOutQuad()) ;
            timeline().apply(&mCircleOne, ci::vec2(0, 0), 5.0f, ci::EaseInOutQuad()) ;
            timeline().apply(&mCircleTwo, ci::vec2(0, 0), 5.0f, ci::EaseInOutQuad()) ;
            holder = false ;
        } else {
            counter = 0 ;
            holder = true ;
        }
    }
}

void week5App::update()
{
}

void week5App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    if(counter != 3) {
        if(firstCell == true) {
            gl::pushModelMatrix() ;
            gl::translate(getWindowCenter()) ;
            gl::color(0.f, 0.75f , 1.0f, 1.0f) ;
            gl::drawSolidEllipse(mCircleOne, 20*mFactorX, 20*mFactorY) ;
            gl::color(0.f, 0.f, 1.0f, mOpacity) ;
            gl::drawSolidEllipse(mCircleTwo, 20*mFactorX, 20*mFactorY) ;
            gl::popModelMatrix() ;
        } else {
            gl::pushModelMatrix() ;
            gl::translate(getWindowCenter()) ;
            gl::color(0.f, 0.f , 1.0f, 1.0f) ;
            gl::drawSolidEllipse(mCircleOne, 20*mFactorX, 20*mFactorY) ;
            gl::color(0.f, 0.75f, 1.0f, mOpacity) ;
            gl::drawSolidEllipse(mCircleTwo, 20*mFactorX, 20*mFactorY) ;
            gl::popModelMatrix() ;
        }
    } else if (counter == 3) {
        gl::pushModelMatrix() ;
        gl::translate(getWindowCenter()) ;
        for (int i=0; i < 62; i++) {
            /*https://forum.processing.org/two/discussion/2437/how-to-rotate-many-objects-around-a-circle*/
            float angle = basicA+i*0.1f ;
            xPos = cos(angle)*r ;
            yPos = sin(angle)*r ;
            mCircleOne = ci::vec2(xPos, yPos) ;
            mCircleTwo = ci::vec2(xPos, yPos) ;
            if(i % 2 == 0) {
                 gl::color(0.f, 0.f, 1.0f, 0.5f) ;
                gl::drawSolidEllipse(mCircleTwo, 20*mFactorX, 20*mFactorY) ;
            } else {
                gl::color(0.f, 0.75f , 1.0f, 0.5f) ;
                gl::drawSolidEllipse(mCircleOne, 20*mFactorX, 20*mFactorY) ;
            }
        }
        gl::popModelMatrix() ;

    }
    if(firstRound == true) {
        gl::pushModelMatrix() ;
        gl::translate(getWindowCenter()) ;
        gl::color(0.f, 0.f, 1.0f, mOpacity) ;
        gl::drawSolidEllipse(mCircleTwo, 20*mFactorX, 20*mFactorY) ;
        gl::popModelMatrix() ;
    }
}

CINDER_APP( week5App, RendererGl )
