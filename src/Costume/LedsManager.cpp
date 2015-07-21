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


const string LedsManager::LEDS_LIST_PATH = "led_list/";


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
    
    this->setupLeds();
    
    ofLogNotice() <<"LedsManager::initialized" ;
    
}

void LedsManager::setupLeds()
{
    this->readLedsPosition();
    this->normalizeLeds();

}

void LedsManager::readLedsPosition()
{
    
    int numSectionsInGroupA = 7;
    int id = 0;
    readLedsPositionFromGroup("A", id, numSectionsInGroupA);
    
    int numSectionsInGroupJ = 5;
    readLedsPositionFromGroup("J", id, numSectionsInGroupA);
    
}

void LedsManager::normalizeLeds()
{
    
    m_boundingBox.setX(67.16);
    m_boundingBox.setY(49.62);
    m_boundingBox.setWidth(3478.78 - m_boundingBox.getX());
    m_boundingBox.setHeight(1724.33 - m_boundingBox.getY());
    
    float width = AppManager::getInstance().getCostumeManager().getWidth();
    float height = AppManager::getInstance().getCostumeManager().getHeight();
    
    
    ofLogNotice() <<"LedsManager::readLedsPosition -> width " << width<< ", height = "  << height;
    
    for (auto led : m_leds) {
        
        ofPoint pos = led->getPosition();
        pos.x = (pos.x - m_boundingBox.getX()) / m_boundingBox.getWidth();
        pos.y = (pos.y - m_boundingBox.getY()) / m_boundingBox.getHeight();
        pos.y = 1 - pos.y;

        
        led->setPosition(pos);
        
        //ofLogNotice() <<"LedsManager::readLedsPosition -> id " << led->getId() << ", channel = "  << led->getChannel()  << ", x = "  << led->getPosition().x << ", y = "  << led->getPosition().y << ", z = " << led->getPosition().z ;
        
    }
    
}

void LedsManager::readLedsPositionFromGroup(const string& groupName, int& id, int numberOfSections)
{
    int channel = 0;
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
                    createLed(ledPosition, id, channel);
                    id++;
                }
                
            }
        }
        
        channel++;
    }

}

void LedsManager::createLed(const ofPoint& position, int id, int channel)
{
    int width = 4;
    int height = width;
    BasicVisual visual(position, width, height);
    
    ofPtr<Led> led = ofPtr<Led> (new Led ( visual, id, channel ) );
    
    
    m_leds.push_back(led);
    
    
    //ofLogNotice() <<"LedsManager::readLedsPosition -> id " << led->getId() << ", channel = "  << led->getChannel()  << ", x = "  << led->getPosition().x << ", y = "  << led->getPosition().y << ", z = " << led->getPosition().z ;
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
    for (auto led : m_leds) {
        ofPoint pos = led->getPosition();
        pos.x *= pixels.getWidth();
        pos.y *= pixels.getHeight();
        
        ofColor color = pixels.getColor(pos.x, pos.y);
        
        led->setColor(color);
    }
    
    AppManager::getInstance().getImageManager().update();
}



void LedsManager::draw()
{
    for (auto led : m_leds) {
        led->draw();
    }
}


