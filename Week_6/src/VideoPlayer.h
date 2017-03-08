//
//  VideoPlayer.hpp
//  Week_6
//
//  Created by Aaron Lee on 3/2/17.
//
//

#ifndef VideoPlayer_hpp
#define VideoPlayer_hpp

#include <stdio.h>

#include "cinder/qtime/QuickTimeGl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#pragma once

class VideoPlayer ;

typedef std::shared_ptr<VideoPlayer> VideoPlayerRef ;
typedef ci::signals::Signal<void()> VideoPlayerEndedSignal ;

class VideoPlayer {
public:
    static VideoPlayerRef create() ;
    void loadVideo(ci::fs::path VideoPath) ;
    void update() ;
    void draw() ;
    void setup() ;
    void pauseMovie() ;
    void playMovie()  ;
    float getVideoTime();
    float getVideoDuration() {return mMovie -> getDuration() ;} ;   
    void seeking(float newTime) ;
    VideoPlayerEndedSignal& getVideoPlayerEndedSignal() {return mVideoPlayerEndedSignal;}

    
private:
    VideoPlayer() ;
    float currentTime ;
    void onVideoEnded() ;
    VideoPlayerEndedSignal  mVideoPlayerEndedSignal ;
    
    
    ci::gl::TextureRef      mVideoTexture ;
    ci::qtime::MovieGlRef   mMovie ;
    ci::fs::path            mMoviePath ;
};


#endif /* VideoPlayer_hpp */
