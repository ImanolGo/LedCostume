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
#include "LaserGroup.h"

//========================== class LedsManager ==============================
//============================================================================
/** \class LedsManager LedsManager.h
 *	\brief Class managing the LEDs and lasers
 *	\details It controls the postion and color of the LEDs and lasers
 */


class LedsManager: public Manager
{

    static const string LEDS_LIST_PATH;
    static const string LASERS_LIST_PATH;
    
    public:
    
        typedef vector<int> IntVector;
        typedef vector< ofPtr<Led> > LedVector;
        typedef vector< ofPtr<LaserGroup> > LaserVector;
        typedef map< string, LedVector> LedMap;
        typedef map< string, LaserVector> LaserMap;
        typedef map< string, IntVector>   ChannelMap;
    
    public:

        //! Constructor
        LedsManager();

        //! Destructor
        ~LedsManager();

        //! Setup the Halo Manager
        void setup();

        //! Update the Led Manager
        void update();
    
        //! Draw the Led Manager
        void draw();
    
        //! Draw the Led Manager according to a certain width or height
        void draw(int width, int height);
    
        const LedMap& getLeds() const {return m_leds;}
    
        const LaserMap& getLasers() const {return m_lasers;}
    
        const ChannelMap& getLedChannels() const {return m_ledChannels;}
    
        const ChannelMap& getLaserChannels() const {return m_laserChannels;}
    
        int getNumberLeds(const string& key) const;
    
        int getNumberLasers(const string& key) const;
    
        void setPixels(ofPixelsRef pixels);
    
        void setLedColors(ofPixelsRef pixels);
    
        void setLaserColors(ofPixelsRef pixels);
    
    
    private:
    
        void setupBoundingBox();
    
        void setupLeds();
    
        void readLedsPosition();
    
        void normalizeLeds();
    
        void readLedsPositionFromGroup(const string& groupName, int& id, int numberOfSections);
    
        void readLasersPositionFromGroup(const string& groupName, int& id, vector<int>& sections);
    
        bool parseLedLine(string& line, ofPoint& position);
    
        void removeCharsFromString( string &str, char* charsToRemove );
    
        void createLed(const ofPoint& position, int& id, int channel, LedVector& leds);
    
        void createLaser(const ofPoint& position, int& id, int channel, LaserVector& lasers);
    
        void drawLasers(int width = 1, int height = 1);
    
        void drawLeds(int width = 1, int height = 1);
    
    private:
    
    
    
        LedMap          m_leds;
        LaserMap        m_lasers;
        ChannelMap      m_ledChannels;
        ChannelMap      m_laserChannels;
        ofRectangle     m_boundingBox;
    
};



