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
    
    this->readLedsPosition();
    
    ofLogNotice() <<"LedsManager::initialized" ;
    
}

void LedsManager::readLedsPosition()
{
    
    int numSectionsInGroupA = 7;
    int id = 0;
    int channel = 0;
    
    for(int i = 1; i <= numSectionsInGroupA; i++)
    {
        string led_section_path = LEDS_LIST_PATH + "A" + ofToString(i) + ".txt";
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
    
    int numSectionsInGroupJ = 5;
    channel = 0;
    
    for(int i = 1; i <= numSectionsInGroupA; i++)
    {
        string led_section_path = LEDS_LIST_PATH + "J" + ofToString(i) + ".txt";
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
    
    
    ofLogNotice() <<"LedsManager::readLedsPosition -> id " << led->getId() << ", y = "  << led->getChannel()  << ", x = "  << led->getPosition().x << ", y = "  << led->getPosition().y << ", z = " << led->getPosition().z ;
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



void LedsManager::draw()
{
}


