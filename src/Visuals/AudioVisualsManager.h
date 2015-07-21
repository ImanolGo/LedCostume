/*
 *  AudioVisualsManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 21/07/15.
 *
 */


#pragma once

#include "Manager.h"


//========================== class AudioVisualsManager ==============================
//============================================================================
/** \class AudioVisualsManager AudioVisualsManager.h
 *	\brief Class managing the audio reactive visuals
 *	\details it creates and updates the audio reactive visuals
 */


class AudioVisualsManager: public Manager
{
    
    public:

        //! Constructor
        AudioVisualsManager();

        //! Destructor
        ~AudioVisualsManager();

        //! Setup the Video Manager
        void setup();

        //! Update the Video Manager
        void update();
    
        //! Draw the Video Manager
        void draw();
    
        void  onPlayAudioVisualsChange(bool value);
    
        void resetPosition();
    
    private:
    
        void setupBoundingBox();
    
    private:
    
        bool            m_playAudioVisuals;
        ofRectangle     m_boundingBox;

};




