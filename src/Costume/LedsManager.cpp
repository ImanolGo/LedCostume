/*
 *  LedsManager.cpp
 *  LED Costume
 *
 *  Created by Imanol Gomez on 09/07/15.
 *
 */


#include "ofMain.h"

#include "LedsManager.h"
#include "AppManager.h"


const string LedsManager::LEDS_LIST_PATH = "leds/";
const string LedsManager::LASERS_LIST_PATH = "lasers/";


LedsManager::LedsManager(): Manager()
{
	//Intentionally left empty
}


LedsManager::~LedsManager()
{
    ofLogNotice() <<"LedsManager::Destructor" ;
}


void LedsManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupBoundingBox();
    this->setupLeds();
    
    ofLogNotice() <<"LedsManager::initialized" ;
    
}

void LedsManager::setupBoundingBox()
{
    //m_boundingBox.setX(67.16);
    //m_boundingBox.setY(49.62);
    //m_boundingBox.setWidth(3478.78 - m_boundingBox.getX());
    //m_boundingBox.setHeight(1724.33 - m_boundingBox.getY());
    
    m_boundingBox.setX(3.56768);
    m_boundingBox.setY(316.313);
    m_boundingBox.setWidth(3491.22 - m_boundingBox.getX());
    m_boundingBox.setHeight(2227.23 - m_boundingBox.getY());
}

void LedsManager::setupLeds()
{
    this->readLedsPosition();
    this->normalizeLeds();
}

void LedsManager::readLedsPosition()
{
    
    int numSections = 8;
    int id = 0;
    readLedsPositionFromGroup("A", id, numSections);
    
    std::vector<int> sections;
    sections.push_back(1); sections.push_back(2);
    readLasersPositionFromGroup("A", id, sections);
    
    id = 0;
    numSections = 8;
    readLedsPositionFromGroup("J", id, numSections);

    sections.clear();
    sections.push_back(1); sections.push_back(2);
    readLasersPositionFromGroup("J", id, sections);
    
    
}

void LedsManager::normalizeLeds()
{
    
    float width = AppManager::getInstance().getCostumeManager().getWidth();
    float height = AppManager::getInstance().getCostumeManager().getHeight();
    
    
    ofLogNotice() <<"LedsManager::normalizeLeds -> width " << width<< ", height = "  << height;
    
    for (auto& ledmap : m_leds)
    {
        auto& ledVector = ledmap.second;
        
        for (auto led: ledVector)
        {
            led->normalize(m_boundingBox);
            //ofLogNotice() <<"LedsManager::normalizeLeds -> id " << led->getId() << ", channel = "  << led->getChannel()  << ", x = "  << led->getPosition().x << ", y = "  << led->getPosition().y << ", z = " << led->getPosition().z ;
        }
    }
    
    
    for (auto& lasermap : m_lasers)
    {
        auto& laserGroupVector = lasermap.second;
        
        for (auto laserGroup: laserGroupVector)
        {
            laserGroup->normalize(m_boundingBox);
            //ofLogNotice() <<"LedsManager::normalizeLeds -> id " << led->getId() << ", channel = "  << led->getChannel()  << ", x = "  << led->getPosition().x << ", y = "  << led->getPosition().y << ", z = " << led->getPosition().z ;
        }
        
    }
    
}

void LedsManager::readLedsPositionFromGroup(const string& groupName, int& id, int numberOfSections)
{
    int channel = 0;
    LedVector leds;
    
    for(int i = 1; i <= numberOfSections; i++)
    {
        string led_section_path = LEDS_LIST_PATH + groupName + ofToString(i) + ".txt";
        ofBuffer buffer = ofBufferFromFile(led_section_path);
        
        if(buffer.size())
        {
            while(buffer.isLastLine() == false)
            {
                string line = buffer.getNextLine();
                ofPoint ledPosition;
                if(parseLedLine(line,ledPosition)){
                    createLed(ledPosition, id, channel, leds);
                }
                
            }
        }
        
        channel++;
    }
    
    ofLogNotice() <<"LedsManager::readLedsPositionFromGroup -> groupName " << groupName << ", numLeds = "  << leds.size();
    m_leds[groupName] = leds;
}

void LedsManager::readLasersPositionFromGroup(const string& groupName, int& id, vector<int>& sections)
{
    int channel = 0;
    LaserVector lasers;
    
    for(auto section: sections)
    {
        string laser_section_path = LASERS_LIST_PATH + groupName + ofToString(section) + ".txt";
        ofBuffer buffer = ofBufferFromFile(laser_section_path);
        
        if(buffer.size())
        {
            ofLogNotice() <<"LedsManager::readLasersPositionFromGroup -> reading lasers from " << laser_section_path;
            
            while(buffer.isLastLine() == false)
            {
                string line = buffer.getNextLine();
                ofPoint laserPosition;
                if(parseLedLine(line,laserPosition)){
                    createLaser(laserPosition, id, channel, lasers);
                }
                
            }
        }
        else{
            ofLogNotice() <<"LedsManager::readLasersPositionFromGroup -> unable to read lasers from " << laser_section_path;
        }
        
        channel++;
    }
    
    
    ofLogNotice() <<"LedsManager::readLasersPositionFromGroup -> groupName " << groupName << ", numLasers = "  << lasers.size();
 
    m_lasers[groupName] = lasers;
}


void LedsManager::createLaser(const ofPoint& position, int& id, int channel, LaserVector& lasers)
{
    if (lasers.empty() || lasers.back()->getNumberLasers()>=3) {
        ofPtr<LaserGroup> laserGroup = ofPtr<LaserGroup> (new LaserGroup(id, channel) );
        lasers.push_back(laserGroup);
        id++;
    }
    
    ofPtr<Laser> laser = ofPtr<Laser> (new Laser(position) );
    laser->setColor(ofColor::black);
    lasers.back()->addLaser(laser);
    
    
    //ofLogNotice() <<"LedsManager::createLaser -> id " << lasers.back()->getId() << ", channel = "  << lasers.back()->getChannel()  << ", x = "  << laser->getPosition().x << ", y = "  << laser->getPosition().y << ", z = " << laser->getPosition().z ;
}

void LedsManager::createLed(const ofPoint& position, int& id, int channel, LedVector& leds)
{
    ofPtr<Led> led = ofPtr<Led> (new Led ( position, id, channel ) );
    led->setColor(ofColor::black);
    leds.push_back(led);
    
    id++;
    
    //ofLogNotice() <<"LedsManager::createLed -> id " << led->getId() << ", channel = "  << led->getChannel()  << ", x = "  << led->getPosition().x << ", y = "  << led->getPosition().y << ", z = " << led->getPosition().z ;
}

bool LedsManager::parseLedLine(string& line, ofPoint& position)
{
    if(line.size() == 0){
        return false;
    }

    char chars[] = "{}";
    removeCharsFromString(line, chars);
    vector <string> strings = ofSplitString(line, ", " );
    
    position.x = ofToFloat(strings[0]);
    position.y = ofToFloat(strings[1]);
    position.z = ofToFloat(strings[2]);
    
    return true;
}

void LedsManager::removeCharsFromString( string &str, char* charsToRemove ) {
    for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
        str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
    }
}

void LedsManager::update()
{
    //
}

void LedsManager::setPixels(ofPixelsRef pixels)
{
    this->setLedColors(pixels);
    this->setLaserColors(pixels);
    
    AppManager::getInstance().getImageManager().update();
}

void LedsManager::setLedColors(ofPixelsRef pixels)
{
    for (auto& ledmap : m_leds)
    {
        auto& ledVector = ledmap.second;
        
        for (auto led: ledVector)
        {
            led->setPixelColor(pixels);
        }
    }
}

void LedsManager::setLaserColors(ofPixelsRef pixels)
{
    for (auto& laserMap : m_lasers)
    {
        auto& laserGroupVector = laserMap.second;
        
        for (auto laserGroup: laserGroupVector)
        {
            laserGroup->setPixelsColors(pixels);
        }
    }
}

void LedsManager::draw()
{
    this->drawLeds();
    this->drawLasers();
}

void LedsManager::draw(int width, int height)
{
    this->drawLeds(width, height);
    this->drawLasers(width, height);
}

void LedsManager::drawLeds(int width, int height)
{
    for (auto& ledmap : m_leds)
    {
        auto& ledVector = ledmap.second;
        
        for (auto led: ledVector)
        {
            led->draw(width,height);
        }
    }
}


void LedsManager::drawLasers(int width, int height)
{
    for (auto& laserMap : m_lasers)
    {
        auto& laserGroupVector = laserMap.second;
        
        for (auto laserGroup: laserGroupVector)
        {
           laserGroup->draw(width,height);
        }
    }
}

int LedsManager::getNumberLeds(const string& key) const
{
    if (m_leds.find(key) == m_leds.end()) {
        return 0;
    }
    
    return m_leds.at(key).size();
}

int LedsManager::getNumberLasers(const string& key) const
{
    if (m_lasers.find(key) == m_lasers.end()) {
        return 0;
    }
    
    return m_lasers.at(key).size();
}


