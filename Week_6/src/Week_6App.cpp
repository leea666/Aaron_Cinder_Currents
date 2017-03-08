#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "VideoPlayer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Week_6App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override ;
	void update() override;
	void draw() override;

    
    Rectf makeRect(glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale = glm::vec2(1.f, 1.f)) ;
    void onPlayerEnded() ;
    
    VideoPlayerRef      mPlayer ;
    int playCount ;
    
    VideoPlayerRef      mNewPlayer ;
    
    ci::Surface8u       mPlaySurf ;
    gl::TextureRef      mPlayButton ;
    ci::Surface8u       mPauseSurf ;
    gl::TextureRef      mPauseButton ;
    ci::Surface8u       mOpenSurf ;
    gl::TextureRef      mOpenButton ;
    
    float               mWidth ;
    float               mHeight ;
    
    bool                mVideoState = true ;
    float               seekerMovement ;
    int playCounter ;
    
    MouseEvent          seekingEvent ;
    string              text = "Video is finished playing. Press play to play again or open a new file" ;
    
    bool                mVideoFinished = false ;
};

void preparedSetup(Week_6App::Settings *settings) {
    settings->setHighDensityDisplayEnabled() ;
}


void Week_6App::setup()
{
    
    mWidth = 626.f/15.f ;
    mHeight = 626.f/15.f ;
    playCounter = 0 ;
    
    mPlayer = VideoPlayer::create() ;
    mPlayer->getVideoPlayerEndedSignal().connect(std::bind(&Week_6App::onPlayerEnded, this)) ;
    fs::path moviePath = getOpenFilePath();
    if( ! moviePath.empty() ) {
        mPlayer -> loadVideo( moviePath );
    }
    
    try {
        mPlayButton = gl::Texture::create(loadImage(loadAsset("playButton.png"))) ;
        mPlaySurf = loadImage(ci::app::loadAsset("playButton.png")) ;
        mPauseButton = gl::Texture::create(loadImage(loadAsset("pauseButton.png"))) ;
        mOpenButton = gl::Texture::create(loadImage(loadAsset("openButton.png"))) ;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl ;
    }

}

void Week_6App::mouseDown( MouseEvent event )
{

    if(mVideoState == false) {
        //play button
        if((event.getX() >= ci::app::getWindowCenter().x && event.getX() <= ci::app::getWindowCenter().x+mWidth) && (event.getY() >=ci::app::getWindowHeight()-(mHeight+5.f) && event.getY() <= ci::app::getWindowHeight()-(mHeight+5.f)+mHeight)) {
            std::cout << "Play button pressed" << std::endl ;
            mPlayer -> playMovie() ;
            mVideoState = true ;
            mVideoFinished = false ;
        }
    }else {
        //pause button
        if((event.getX() >= ci::app::getWindowCenter().x && event.getX() <= ci::app::getWindowCenter().x+mWidth) && (event.getY() >=ci::app::getWindowHeight()-(mHeight+5.f) && event.getY() <= ci::app::getWindowHeight()-(mHeight+5.f)+mHeight)) {
            std::cout << "Pause button pressed" << std::endl ;
            mPlayer -> pauseMovie() ;
            mVideoState = false ;
            mVideoFinished = false ;
        }
    }
    //open button and video seeking
    if((event.getX() >= ci::app::getWindowCenter().x - mWidth - 5.f && event.getX() <= ci::app::getWindowCenter().x - 5.f) && (event.getY() >=ci::app::getWindowHeight()-(mHeight+5.f) && event.getY() <= ci::app::getWindowHeight()-(mHeight+5.f)+mHeight)) {
        std::cout << "Open button pressed" << std::endl ;
        mPlayer = VideoPlayer::create() ;
        fs::path moviePath = getOpenFilePath();
        mPlayer->getVideoPlayerEndedSignal().connect(std::bind(&Week_6App::onPlayerEnded, this)) ;
        if( ! moviePath.empty() ) {
            mPlayer -> loadVideo( moviePath );
        }
        mVideoState = true ;
        mVideoFinished = false ;
        playCounter = 0 ;
    }

    if((event.getX() >= 0 && event.getX() <= ci::app::getWindowWidth()) && (event.getY() >= ci::app::getWindowHeight()-60.f && event.getY() <= ci::app::getWindowHeight() - 55.f)) {
                std::cout << "Video Seeking" << std::endl ;
        mPlayer -> pauseMovie() ;
        mouseUp(event) ;
        seekerMovement = (event.getX() * mPlayer -> getVideoDuration())/ci::app::getWindowWidth() ;
        mPlayer -> seeking(seekerMovement) ;
        mPlayer -> playMovie() ;
        mVideoFinished = false ;
    }
}

void Week_6App::onPlayerEnded()
{
    playCounter++ ;
    ci::app::console() << "video just finished playing, play count is: " << playCounter << std::endl ;
    mPlayer -> pauseMovie() ;
    
    mVideoFinished = true ;
    mVideoState = false ;

}


Rectf Week_6App::makeRect(glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale) {
    return Rectf(startingPoint.x, startingPoint.y, (size.x+startingPoint.x) * scale.x, (size.y+startingPoint.y) * scale.y) ;
}

void Week_6App::update()
{
    mPlayer -> update() ;

}

void Week_6App::draw()
{
    gl::clear( Color( 56.f/255.f, 116.f/255.f, 199.f/255.f ), true );
    gl::enableAlphaBlending() ;
    mPlayer -> draw() ;
    
    if(mVideoState == false) {
    gl::draw(mPlayButton, makeRect(glm::vec2(ci::app::getWindowCenter().x, ci::app::getWindowHeight()-(mHeight+5.f)), glm::vec2(mWidth, mHeight))) ;
    } else {
        gl::draw(mPauseButton, makeRect(glm::vec2(ci::app::getWindowCenter().x , ci::app::getWindowHeight()-(mHeight+5.f)), glm::vec2(mWidth, mHeight))) ;
    }
    gl::draw(mOpenButton, makeRect(glm::vec2(ci::app::getWindowCenter().x - mWidth - 5.f, ci::app::getWindowHeight()-(mHeight+5.f)), glm::vec2(mWidth, mHeight))) ;
    
    {
        gl::ScopedColor newColor1(1.f, 1.f, 1.f) ;
        gl::drawSolidRect(makeRect(glm::vec2(0,ci::app::getWindowHeight()-60.f), glm::vec2(ci::app::getWindowWidth(), 5.f))) ;
    }
    
    {
        gl::ScopedColor newColor2(1.0, 0.f, 0.f, .5f) ;
        gl::drawSolidRect(makeRect(glm::vec2(0,ci::app::getWindowHeight()-60.f), glm::vec2(mPlayer ->getVideoTime(), 5.f))) ;
    }
    
    seekerMovement = mPlayer -> getVideoTime() ;
    {
        gl::ScopedColor newColor3(0.35f, 0.35f, 0.35f) ;
        gl::drawSolidCircle(glm::vec2(seekerMovement, ci::app::getWindowHeight()-57.5f), 7.f) ;
    }
    
    if(mVideoFinished == true) {
        gl::drawString( text , ci::vec2( ci::app::getWindowCenter().x/2, ci::app::getWindowCenter().y), ci::Color( 0.5f, 0.5f, 0.5f ) );
    }
}

CINDER_APP( Week_6App, RendererGl )
