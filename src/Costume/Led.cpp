//
//  Led.cpp
//  Led Costume
//
//  Created by Imanol Gomez on 09/07/15.
//
//--------------------------------------------------------------

#include "Led.h"


const int Led::SIZE = 4;

Led::Led(const ofPoint& position, int id, int channel): BasicVisual(position, SIZE, SIZE), m_id(id), m_channel(channel)
{
    //Intentionaly left empty
}

Led::~Led()
{
    //Intentionaly left empty
}

void Led::draw()
{
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(m_position);
    ofScale(m_scale.x, m_scale.y);
    ofTranslate(-m_width*0.5,-m_height*0.5);
    
    ofRotateX(m_rotation.x);
    ofRotateY(m_rotation.y);
    
    ofSetColor(m_color);
    ofFill();
    
        ofRect(0, 0, m_width, m_height);
    
    ofPopStyle();
    ofPopMatrix();
}

void Led::draw(int width, int height)
{
    
    ofPushMatrix();
    ofTranslate(m_position.x * width, m_position.y * height);
        this->draw();
    ofPopMatrix();
}

void Led::normalize(const ofRectangle& boundingBox)
{
    m_position.x = (m_position.x - boundingBox.getX()) / boundingBox.getWidth();
    m_position.y = (m_position.y - boundingBox.getY()) / boundingBox.getHeight();
    m_position.y = 1 - m_position.y;
}


void Led::setPixelColor(ofPixelsRef pixels)
{
    m_color = pixels.getColor(m_position.x * pixels.getWidth(), m_position.y * pixels.getHeight());
}

