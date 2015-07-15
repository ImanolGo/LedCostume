/*
 *  ImageManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 15/07/15.
 *
 */


#pragma once

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
    
        //! Draw the Image Manager
        void draw();
    
    
    private:
  
        ofImage             m_image;
};




