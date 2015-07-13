//
//  Led.cpp
//  Led Costume
//
//  Created by Imanol Gomez on 09/07/15.
//
//--------------------------------------------------------------

#include "Led.h"


Led::Led(const BasicVisual& visual, int id, int channel): BasicVisual(visual), m_id(id), m_channel(channel)
{
    
    this->setup();
}

Led::~Led()
{
    //Intentionaly left empty
}

void Led::setup()
{
    //
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

