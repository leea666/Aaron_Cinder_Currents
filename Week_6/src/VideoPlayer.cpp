//
//  VideoPlayer.cpp
//  Week_6
//
//  Created by Aaron Lee on 3/2/17.
//
//

#include "VideoPlayer.h"

VideoPlayerRef VideoPlayer::create()
{
    VideoPlayerRef ref = std::shared_ptr<VideoPlayer> (new VideoPlayer()) ;
    ref -> setup() ;
    return ref ;
}

VideoPlayer::VideoPlayer()
{
    
}

void VideoPlayer::setup()
{
    
}

void VideoPlayer::onVideoEnded()
{
    mVideoPlayerEndedSignal.emit() ;
}


void VideoPlayer::loadVideo(ci::fs::path VideoPath)
{
    try {
        mMovie = ci::qtime::MovieGl::create(VideoPath) ;
        mMovie -> setLoop() ;
        mMovie -> play() ;
        mMovie->getEndedSignal().connect(std::bind(&VideoPlayer::onVideoEnded, this)) ;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl ;
        mMovie.reset() ;
    }
}

void VideoPlayer::update()
{
    if(mMovie) {
        mVideoTexture = mMovie -> getTexture() ;
    }
}

void VideoPlayer::draw()
{
    if(mVideoTexture) {
        ci::Rectf centeredRect = ci::Rectf(mVideoTexture -> getBounds()).getCenteredFit(ci::app::getWindowBounds(), true) ;
        ci::gl::draw(mVideoTexture, centeredRect) ;
    }
}

void VideoPlayer::playMovie()
{
    mMovie -> play() ;
}

void VideoPlayer::pauseMovie()
{
    mMovie -> stop() ;
}

void VideoPlayer::seeking(float newTime)
{
    mMovie -> seekToTime(newTime) ;
}

float VideoPlayer::getVideoTime()
{
    currentTime = mMovie -> getCurrentTime() ;
    currentTime = (currentTime / mMovie -> getDuration()) * ci::app::getWindowWidth() ;
    return currentTime ;
}

