/*
 *  LedsManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 09/07/15.
 *
 */


#pragma once

#include "Manager.h"
#include "Led.h"

//========================== class LedsManager ==============================
//============================================================================
/** \class LedsManager LedsManager.h
 *	\brief Class managing the LEDs
 *	\details It controls the postion and color of the LEDs
 */


class LedsManager: public Manager
{

    static const string LEDS_LIST_PATH;
    
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
    
    private:
    
        void readLedsPosition();
    
        bool parseLedLine(string& line, ofPoint& position);
    
        void removeCharsFromString( string &str, char* charsToRemove );
    
        void createLed(const ofPoint& position, int id, int channel);
    
    private:
    
        typedef vector< ofPtr<Led> > LedVector;
    
        LedVector m_leds;
    
};



