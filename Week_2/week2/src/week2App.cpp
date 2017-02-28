#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class week2App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    Rectf getRectf(glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale = glm::vec2(1.f, 1.f)) ;
    
    ci::Surface8u mSurface ;
    gl::TextureRef mTexture ;
    ci::Surface8u mSurfaceDistorted ;
    gl::TextureRef mTexFromSurface ;
    
    
    float mWidth ;
    float mHeight ;
    
    void distort(ci::Surface8u *surface, Area area, float angle) ;
    
 
};

void week2App::setup()
{
    mWidth = 1280.f/1.5 ;
    mHeight = 960.f/1.5 ;
    ci::app::setWindowSize(1280.f, 960.f) ;
    try {
        mTexture = gl::Texture::create(loadImage(loadAsset("pupa.jpg"))) ;
        mSurface = loadImage(ci::app::loadAsset("pupa.jpg")) ;
        mSurfaceDistorted = mSurface.clone() ;
    } catch (exception& e) {
        ci::app::console() << e.what() << endl ;
    }
    
    ci::Surface::Iter iter = mSurfaceDistorted.getIter(mSurface.getBounds()) ;
    while(iter.line()) {
        while(iter.pixel()) {
            iter.r() = iter.r(iter.x(), iter.y()) ;
            iter.g() = iter.g(-100, 100) ;
            iter.b() = iter.b() ;
            iter.a() = 10 ;
        }
    }
}

void week2App::mouseDown( MouseEvent event )
{
}

void week2App::update()
{
}

void week2App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::draw(mTexture, getRectf(glm::vec2(10.f, 10.f), glm::vec2(mWidth, mHeight))) ;
    mTexFromSurface = gl::Texture::create(mSurfaceDistorted) ;
//    vec2 circlePos = (getMousePos()) ;
//    float circleRad = 10.f ;
//    gl::drawStrokedCircle(circlePos, circleRad) ;
    gl::draw(mTexFromSurface, getRectf(glm::vec2(getMousePos()), glm::vec2(getMousePos()+100))) ;
}

Rectf week2App::getRectf(glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale) {
    return Rectf(startingPoint.x, startingPoint.y, (size.x+startingPoint.x) * scale.x, (size.y+startingPoint.y) * scale.y) ;
}

void week2App::distort(ci::Surface8u *surface, Area area, float angle) {
    ci::Surface8u newSurface = surface->clone() ;
}
CINDER_APP( week2App, RendererGl )
