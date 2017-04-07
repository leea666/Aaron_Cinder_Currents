#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "poNodeContainer.h"
#include "poShape.h"
#include "poScene.h"
#include "Button.h"
#include "cinder/timeline.h"
#include "poTextBox.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class week10App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    po::scene::SceneRef             mScene ;
    po::scene::NodeContainerRef     mContainer ;
    po::scene::ShapeRef             mScreen ;
    po::scene::ShapeRef             mShadow ;
    po::scene::ShapeRef             mBackground ;
    po::scene::ShapeRef             mTopBar ;
    po::scene::ShapeRef             mTop ;
    po::scene::ShapeRef             mBottomBar ;
    po::scene::ShapeRef             mBottom ;
    po::scene::ShapeRef             mPopOut ;
    
    po::scene::ShapeRef             mPicture ;
    po::scene::ShapeRef             mOutline ;
    po::scene::ShapeRef             mOutline2 ;
    
    ci::gl::TextureRef              mBackgroundTexture ;
    ci::gl::TextureRef              mScreenTexture ;
    ci::gl::TextureRef              mPictureTexture ;
    ci::gl::TextureRef              mButtonTexture ;
    ci::gl::TextureRef              mActButtonTexture ;
    
    po::scene::TextBoxRef           mPicText ;
    ci::TextBox ciText ;

    
    ButtonRef                       mButton ;
    
    int                             counter ;
    bool                            mButtonPressed ;
    
};

void week10App::setup()
{
    ci::app::setWindowSize(glm::vec2(800,500)) ;
    counter = 0 ;
    ciText.setText("Ready to evolve into a beautiful butteryfly!") ;
    
    try {
        mBackgroundTexture = gl::Texture::create(loadImage(loadAsset("Background.png"))) ;
        mScreenTexture = gl::Texture::create(loadImage(loadAsset("ScreenColor.png"))) ;
        mPictureTexture = gl::Texture::create(loadImage(loadAsset("pupaF2.png"))) ;
        mButtonTexture = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset("Button.png"))) ;
        mActButtonTexture = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset("ButtonAct.png"))) ;
    } catch(exception& e) {
        ci::app::console() << e.what() << endl ;
    }
   
    mBackgroundTexture->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    mScreenTexture->setWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER) ;
    
    mContainer = po::scene::NodeContainer::create() ;
    mScene = po::scene::Scene::create(mContainer) ;
    mScreen = po::scene::Shape::createRoundedRect(250.f, 400.f, 10.f) ;
    mBackground = po::scene::Shape::createRect(800.f,500.f) ;
    mShadow = po::scene::Shape::createRoundedRect(250.f,400.f,10.f) ;
    mTopBar = po::scene::Shape::createRoundedRect(250.f, 40.f, 10.f) ;
    mTop = po::scene::Shape::createRect(250.f, 10.f) ;
    mBottomBar = po::scene::Shape::createRoundedRect(250.f, 40.f, 10.f) ;
    mBottom = po::scene::Shape::createRect(250.f, 10.f) ;
    mOutline = po::scene::Shape::createRect(230.f, 250.f) ;
    mOutline2 = po::scene::Shape::createRect(230.f, 50.f) ;
    mPicture = po::scene::Shape::createRect(220.f, 200.f) ;
    
    mContainer->addChild(mBackground) ;
    mBackground->setPosition(ci::app::getWindowCenter()) ;
    mBackground->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
//    mBackground->setFillColor(ci::Color::hex(0xfad7a0)) ;
    mBackground->setTexture(mBackgroundTexture) ;

    
    mContainer->addChild(mShadow) ;
    mShadow->setPosition(glm::vec2(ci::app::getWindowCenter().x+10.f, ci::app::getWindowCenter().y+10.f)) ;
    mShadow->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
    mShadow->setFillColor(ci::Color::hex(0x5d6d7e)) ;
    
    mContainer->addChild(mScreen) ;
    mScreen->setPosition(ci::app::getWindowCenter()) ;
    mScreen->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
//    mScreen->setFillColor(ci::Color::hex(0x2e86c1)) ;
    mScreen->setTexture(mScreenTexture) ;
    
    mContainer->addChild(mTopBar) ;
    mTopBar->setPosition(glm::vec2(ci::app::getWindowCenter().x, ci::app::getWindowCenter().y-180.f)) ;
    mTopBar->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
    mTopBar->setFillColor(ci::Color::hex(0x17202a)) ;
    
    mContainer->addChild(mTop) ;
    mTop->setPosition(glm::vec2(ci::app::getWindowCenter().x, ci::app::getWindowCenter().y-165.f)) ;
    mTop->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
    mTop->setFillColor(ci::Color::hex(0x17202a)) ;
    
    mContainer->addChild(mOutline2) ;
    mOutline2->setPosition(glm::vec2(ci::app::getWindowCenter().x-115.f, ci::app::getWindowCenter().y+120.f)) ;
    mOutline2->setAlignment(po::scene::Alignment::TOP_LEFT) ;
    mOutline2->setFillColor(ci::Color::hex(0xecf0f1)) ;
    
    mContainer->addChild(mBottomBar) ;
    mBottomBar->setPosition(glm::vec2(ci::app::getWindowCenter().x, ci::app::getWindowCenter().y+180.f)) ;
    mBottomBar->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
    mBottomBar->setFillColor(ci::Color::hex(0x17202a)) ;

    mContainer->addChild(mBottom) ;
    mBottom->setPosition(glm::vec2(ci::app::getWindowCenter().x, ci::app::getWindowCenter().y+165.f)) ;
    mBottom->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
    mBottom->setFillColor(ci::Color::hex(0x17202a)) ;
    
    mButton = Button::create(15.f, mButtonTexture, mActButtonTexture) ;
//    mButton->setDrawBounds(true) ;
    
    mContainer->addChild(mButton) ;
    
//    mButton->setDrawBounds(true) ;
    mButton->setPosition(glm::vec2(ci::app::getWindowCenter().x-115, ci::app::getWindowCenter().y-195.f)) ;
    
    
    mContainer->addChild(mOutline) ;
    mOutline->setPosition(glm::vec2(ci::app::getWindowCenter().x-115.f, ci::app::getWindowCenter().y-150.f)) ;
    mOutline->setAlignment(po::scene::Alignment::TOP_LEFT) ;
    mOutline->setFillColor(ci::Color::hex(0xecf0f1)) ;
    
    mContainer->addChild(mPicture) ;
    mPicture->setPosition(glm::vec2(ci::app::getWindowCenter().x-110.f, ci::app::getWindowCenter().y-145.f)) ;
    mPicture->setAlignment(po::scene::Alignment::TOP_LEFT) ;
    mPicture->setTexture(mPictureTexture) ;
    
    mPicText = po::scene::TextBox::create(ciText) ;
    mPicText->setAlignment(po::scene::Alignment::CENTER_CENTER) ;
    mPicText->setPosition(glm::vec2(ci::app::getWindowCenter().x, ci::app::getWindowCenter().y+70.f)) ;
    mPicText->setFillColor(ci::Color::black()) ;
    mContainer->addChild(mPicText) ;
    
    mPopOut = po::scene::Shape::createRect(110.f, 320.f) ;
    mPopOut->setPosition(glm::vec2(ci::app::getWindowCenter().x-125.f, ci::app::getWindowCenter().y-160.f)) ;
    mPopOut->setAlignment(po::scene::Alignment::TOP_LEFT) ;
    mPopOut->setFillColor(ci::Color::hex(0x34495e)) ;
    mPopOut->setAlpha(0.0f) ;
    mContainer->addChild(mPopOut) ;
    
    

}

void week10App::mouseDown( MouseEvent event )
{
    std::cout << event.getY() << endl ;
    std::cout << ci::app::getWindowCenter().y-195.f << endl ;
    mButtonPressed = mButton->isAct ;
    if(mButtonPressed == true && (event.getX() > ci::app::getWindowCenter().x-115.f && event.getX() < ci::app::getWindowCenter().x-85.f) && (event.getY() > ci::app::getWindowCenter().y-195.f && event.getY() < ci::app::getWindowCenter().y-165.f)) {
        std::cout << "this ran" << std::endl ;
//        mContainer->addChild(mPopOut) ;
        ci::app::timeline().apply(&mPopOut->getAlphaAnim(), 1.0f, 2.0f, ci::EaseOutExpo()) ;
//        ci::app::timeline().apply(&mPopOut->getPositionAnim(), glm::vec2(ci::app::getWindowCenter().x-125.f, ci::app::getWindowCenter().y-160.f), 2.0f, ci::EaseOutExpo()) ;
    } else if (mButtonPressed == false && (event.getX() > ci::app::getWindowCenter().x-115.f && event.getX() < ci::app::getWindowCenter().x-85.f) && (event.getY() > ci::app::getWindowCenter().y-195.f && event.getY() < ci::app::getWindowCenter().y-165.f)) {
//        mContainer->removeChild(mPopOut) ;
        ci::app::timeline().apply(&mPopOut->getAlphaAnim(), 0.f, 2.0f, ci::EaseOutExpo()) ;

    }

}

void week10App::update()
{
    mScene->update() ;
//    std::cout<< getMousePos().x << endl ;
    

}

void week10App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mScene->draw() ;
}

CINDER_APP( week10App, RendererGl(RendererGl::Options().msaa(8)))
