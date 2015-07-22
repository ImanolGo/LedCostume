/*
 *  ImageManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 15/07/15.
 *
 */


#pragma once

#include "Manager.h"
#include "Led.h"
#include "Manager.h"


//========================== class ImageManager ==============================
//============================================================================
/** \class ImageManager ImageManager.h
 *	\brief Class managing the images to be exported
 *	\details it reads from the Led visuals and saves it on a file on demand
 */


class ImageManager: public Manager
{
    
    typedef vector< ofColor > ColorVector;
    typedef map< string, ColorVector> ColorVectorMap;
    typedef map< string, ofImage> ImageMap;
    
    public:

        //! Constructor
        ImageManager();

        //! Destructor
        ~ImageManager();

        //! Setup the Image Manager
        void setup();
    
        //! Update the Image Manager
        void update();
    
        //! Draw the Image Manager
        void draw();
    
        void onRecordingChange(bool& value);
    
        void onMirroringChange(bool& value) {m_mirror = value;}
    
    private:
    
        void saveImages();
    
        void saveImageSample(const string& key);
    
        void saveImageMirror(const string& key);
    
        void updateColorPixels();
    
        void updateLedColorPixels();
    
        void updateLaserColorPixels();
    
        string getDateTime();
    
    private:
  
        bool                m_isRecording;
        bool                m_mirror;
    
        ImageMap           m_imageMap;
        ColorVectorMap     m_colorVectorMap;
};




