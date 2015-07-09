/*
 *  LedsManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 09/07/15.
 *
 */


#pragma once

#include "Manager.h"

//========================== class LedsManager ==============================
//============================================================================
/** \class LedsManager LedsManager.h
 *	\brief Class managing the LEDs
 *	\details It controls the postion and color of the LEDs
 */


class LedsManager: public Manager
{

    static const int NUM_HALO_LEDS;
    
    public:

        //! Constructor
        LedsManager();

        //! Destructor
        ~LedsManager();

        //! Setup the Halo Manager
        void setup();

        //! Update the Halo Manager
        void update();
    
        //! Draw the Halo Manager
        void draw();
    
};



