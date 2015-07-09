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
    //
}

