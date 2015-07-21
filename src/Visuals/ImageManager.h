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
    
        void saveImage();
    
        void saveImageMirror();
    
        void saveImageSample();
    
        void updateImage();
    
        string getDateTime();
    
    private:
    
        typedef vector< ofColor > ColorVector;
        typedef vector< ColorVector> ImageVector;
  
        ofImage             m_image;
        bool                m_isRecording;
        bool                m_mirror;
    
        ImageVector         m_imageVector;
};




