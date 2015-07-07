/*
 *  CostumeManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 07/07/15.
 *
 */


#pragma once

#include "Manager.h"
#include "ImageVisual.h"

//========================== class CostumeManager ==============================
//============================================================================
/** \class CostumeManager CostumeManager.h
 *	\brief Class managing the costume visuals
 *	\details it creates and updates the costume visuals
 */


class CostumeManager: public Manager
{

    static const int NUM_HALO_LEDS;
    
    public:

        //! Constructor
        CostumeManager();

        //! Destructor
        ~CostumeManager();

        //! Setup the Halo Manager
        void setup();

        //! Update the Halo Manager
        void update();
    
        //! Draw the Halo Manager
        void draw();
    
    
    private:
    
        void setupImages();
    
    
    ofPtr<ImageVisual>  m_costumeImage;
};


