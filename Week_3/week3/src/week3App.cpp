#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Particle.hpp"
#include "ParticleSystem.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class week3App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    
    ParticleSystem mParticleSystem ;
};

void week3App::setup()
{
    ci::app::setWindowSize(1280,720) ;
    mParticleSystem.setup() ;
}

void week3App::mouseDown( MouseEvent event )
{
//     mParticleSystem.repulseFrom(event.getPos()) ;
}

void week3App::update()
{
    mParticleSystem.update() ;
}

void week3App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mParticleSystem.draw() ;
}

CINDER_APP( week3App, RendererGl )
