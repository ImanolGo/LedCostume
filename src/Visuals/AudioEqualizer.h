/*
 *  AudioEqualizer.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 26/08/15.
 *
 */


#pragma once


//========================== class AudioEqualizer ==============================
//============================================================================
/** \class AudioEqualizer AudioEqualizer.h
 *	\brief Class representing audio equalizer visuals
 *	\details it creates and updates the audio equalizer
 */

#include "LedsManager.h"

class AudioEqualizer
{

    public:

        //! Constructor
        AudioEqualizer();

        //! Destructor
        ~AudioEqualizer();

        //! Setup the Audio Equalizer
        void setup();

        //! Update the Audio Equalizer
        void update();
    
        //! Draw the Audio Equalizer
        void draw();
    
    private:
    
        void setupNumFrames();
    
    private:
    
        int m_numFrames;
        int m_currentFrame;
    
        LedsManager::LedVector m_leds;
};




