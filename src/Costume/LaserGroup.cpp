//
//  LaserGroup.cpp
//  Led Costume
//
//  Created by Imanol Gomez on 22/07/15.
//
//--------------------------------------------------------------

#include "LaserGroup.h"


LaserGroup::LaserGroup(int id, int channel): BasicVisual(), m_id(id), m_channel(channel)
{
    
    //Intentionaly left empty
}

LaserGroup::~LaserGroup()
{
    //Intentionaly left empty
}

void LaserGroup::draw()
{
    for(auto laser: m_lasers){
        laser->draw();
    }
}

void LaserGroup::draw(int width, int height)
{
    for(auto laser: m_lasers){
        auto pos = laser->getPosition();
        
        ofPushMatrix();
        ofTranslate(pos.x*width, pos.y*height);
            laser->draw();
        ofPopMatrix();
    }
}


void  LaserGroup::updateColor()
{
    m_color = ofColor::black;
    
    if(m_lasers.size() > 0){
        m_color.r =  m_lasers[0]->getColor().getBrightness();
    }
    
    if(m_lasers.size() > 1){
        m_color.g =  m_lasers[1]->getColor().getBrightness();
    }
    
    if(m_lasers.size() > 2){
        m_color.b =  m_lasers[2]->getColor().getBrightness();
    }
    
}


void LaserGroup::normalize(const ofRectangle& boundingBox)
{
    for(auto laser: m_lasers)
    {
        ofPoint pos = laser->getPosition();
        pos.x = (pos.x - boundingBox.getX()) / boundingBox.getWidth();
        pos.y = (pos.y - boundingBox.getY()) / boundingBox.getHeight();
        pos.y = 1 - pos.y;
        laser->setPosition(pos);
        
        //ofLogNotice() <<"LaserGroup::normalize -> id " << getId()<< ", channel = "  << getChannel()  << ", x = "  << laser->getPosition().x << ", y = "  << laser->getPosition().y << ", z = " << laser->getPosition().z ;

    }
}

void LaserGroup::setPixelsColors(ofPixelsRef pixels)
{
    for(auto laser: m_lasers)
    {
        const ofPoint& pos = laser->getPosition();
        ofColor color = pixels.getColor(pos.x*pixels.getWidth(), pos.y*pixels.getHeight());
        laser->setColor(color);
    }
    
    this->updateColor();
}

