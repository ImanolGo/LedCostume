//
//  Laser.cpp
//  Led Costume
//
//  Created by Imanol Gomez on 22/07/15.
//
//--------------------------------------------------------------

#include "Laser.h"

const int Laser::SIZE = 4;

Laser::Laser(const ofPoint& position): BasicVisual(position, SIZE, SIZE)
{
    //Intentionaly left empty
}

Laser::~Laser()
{
    //Intentionaly left empty
}


void Laser::draw()
{
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(m_position);
    ofScale(m_scale.x, m_scale.y);
    ofTranslate(-m_width*0.5,-m_height*0.5);
    
    ofRotateX(m_rotation.x);
    ofRotateY(m_rotation.y);
    
    //ofSetColor(m_color);
    ofSetColor(ofColor(m_color.getBrightness(), 0, 0));
    ofFill();
    
        ofRect(0, 0, m_width, m_height);
    
    ofPopStyle();
    ofPopMatrix();
}

