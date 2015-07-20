/*
 *  VideoManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 20/07/15.
 *
 */


#pragma once

#include "Manager.h"


//========================== class VideoManager ==============================
//============================================================================
/** \class VideoManager VideoManager.h
 *	\brief Class managing the video player visuals
 *	\details it creates and updates the video player
 */


class VideoManager: public Manager
{
    
    static const string VIDEO_PATH;
    
    public:

        //! Constructor
        VideoManager();

        //! Destructor
        ~VideoManager();

        //! Setup the Video Manager
        void setup();

        //! Update the Video Manager
        void update();
    
        //! Draw the Video Manager
        void draw();
    
        void  onPlayVideoChange(bool value);
    
        void  onNextVideoChange();
    
        void resetPosition();
    
    
    private:
    
        void loadVideos();
    
        void setupBoundingBox();

    
    private:
    
    typedef vector <string> Videos;
    
    ofVideoPlayer 	m_videoPlayer;
    Videos          m_videos;
    string          m_currentVideo;
    
    bool            m_playVideo;
    ofRectangle     m_boundingBox;

};




