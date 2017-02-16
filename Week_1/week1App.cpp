#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class week1App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void four() ;
    void six() ;

};

void week1App::setup()
{
    ci::app::setWindowSize(600.f, 600.f) ;
//    gl::clear(Color(0,0,0)) ;
}

void week1App::mouseDown( MouseEvent event )
{
}

void week1App::update()
{
}

void week1App::draw()
{
    gl::clear(Color(0,0,0)) ;

    gl::color(Color(1,1,1)) ;
    four() ;
    gl::color(Color(1,0,0)) ;
    six() ;

}

void week1App::four() {
//    gl::drawSolidRoundedRect(Rectf(50, 50, 100, 250), 10) ;
//    gl::drawSolidRoundedRect(Rectf(200, 50, 250, 400), 10) ;
//    gl::drawSolidRoundedRect(Rectf(50, 200, 300, 250), 10) ;
    gl::drawStrokedRoundedRect(Rectf(50, 50, 100, 250), 10) ;
    gl::drawStrokedRoundedRect(Rectf(200, 50, 250, 400), 10) ;
    gl::drawStrokedRoundedRect(Rectf(50, 200, 300, 250), 10) ;
}

void week1App::six() {
    gl::drawStrokedRoundedRect(Rectf(250+100, 50+100, 300+100, 400+100), 20) ;
    gl::drawStrokedRoundedRect(Rectf(250+100, 350+100, 450+100, 400+100), 20) ;
    gl::drawStrokedRoundedRect(Rectf(250+100, 200+100, 450+100, 250+100), 20) ;
    gl::drawStrokedRoundedRect(Rectf(400+100, 200+100, 450+100, 400+100), 20) ;
    gl::drawStrokedRoundedRect(Rectf(250+100, 50+100, 450+100, 100+100), 20) ;
}


CINDER_APP( week1App, RendererGl )
