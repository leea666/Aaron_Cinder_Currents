#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Particle.hpp"
#include "cinder/Perlin.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class WindParticlesApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    const int NUM_PARTICLES = 375 ;
    const float RANDOM_RANGE = 10.f ;
    const float RANDOM_FORCE_RANGE = 2.f ;
    const float LIFE_SPAN = 3.f ;
    
    std::vector<ParticleRef> mParticles ;
    ci::Perlin mPerlin ;
    float mTime ;
    float mFrequency = 1/100.f ;
    int counter = 0 ;
};

void WindParticlesApp::setup()
{
  ci::app::setWindowSize(1280, 720) ;
    
}

void WindParticlesApp::mouseDown( MouseEvent event )
{
    for(int i = 0 ; i < NUM_PARTICLES ; i++) {
        mParticles.push_back(Particle::create(glm::vec2(event.getPos().x, 770), LIFE_SPAN, glm::vec2(ci::randFloat(-RANDOM_FORCE_RANGE, RANDOM_FORCE_RANGE),ci::randFloat(-RANDOM_FORCE_RANGE, RANDOM_FORCE_RANGE)))) ;
    }

}

void WindParticlesApp::update()
{
    mTime = ci::app::getElapsedSeconds() * 100.f ;
    for(auto& p:mParticles) {
        p->update() ;
    }
    
    for(auto p = mParticles.begin() ; p != mParticles.end();) {
        if((*p)->getTimerLeft() < 0) {
            p = mParticles.erase(p) ;
        } else {
            ++p ;
        }
    }
}

void WindParticlesApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::ScopedBlendAdditive blend ;
    ci::gl::begin(GL_LINES);
    for (auto& p: mParticles){
        ci::gl::color(ci::ColorA(0.75f - p->getTimerLeft() ,0.5f, 1.f - p->getTimerLeft()/p->getLifeSpan()));
        if(p->getPosition().y < 100) {
            p->applyForce(glm::vec2(0, 0.1f)) ;
        }
        else if(p->getPosition().y >=100) {
            p->applyForce(glm::vec2(0,-0.1f)) ;
        }
        vec3 norm = mPerlin.dfBm( vec3( p->getPosition().x, p->getPosition().y, mTime )* mFrequency) ;
        vec2 flowForce = normalize( vec2( norm.x, norm.y ) ) * 0.1f;
        p->applyForce(flowForce);
        gl::vertex(p->getPosition());
        gl::vertex(p->getPosition() + glm::vec2(-1.f,-1.f));
        p->applyForce(glm::vec2(-0.1f,-0.1f)) ;
    }
    ci::gl::end();

}

CINDER_APP( WindParticlesApp, RendererGl )
