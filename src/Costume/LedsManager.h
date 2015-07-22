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
#include "Laser.h"

//========================== class LedsManager ==============================
//============================================================================
/** \class LedsManager LedsManager.h
 *	\brief Class managing the LEDs and lasers
 *	\details It controls the postion and color of the LEDs and lasers
 */


class LedsManager: public Manager
{

    static const string LEDS_LIST_PATH;
    
    
    public:
    
        typedef vector< ofPtr<Led> > LedVector;
        typedef vector< ofPtr<Laser> > LaserVector;
        typedef map< string, LedVector> LedMap;
        typedef map< string, LaserVector> LaserMap;
    
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
    
        const LedMap& getLeds() const {return m_leds;}
    
        const LaserMap& getLasers() const {return m_lasers;}
    
        int getNumberLeds(const string& key) const;
    
        void setPixels(ofPixelsRef pixels);
    
    
    private:
    
        void setupLeds();
    
        void readLedsPosition();
    
        void normalizeLeds();
    
        void readLedsPositionFromGroup(const string& groupName, int& id, int numberOfSections);
    
        bool parseLedLine(string& line, ofPoint& position);
    
        void removeCharsFromString( string &str, char* charsToRemove );
    
        void createLed(const ofPoint& position, int id, int channel, LedVector& leds);
    
    private:
    
    
    
        LedMap          m_leds;
        LaserMap        m_lasers;
        ofRectangle     m_boundingBox;
    
};



