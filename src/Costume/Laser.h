//
//  Laser.h
//
//  Created by Imanol Gomez on 22/07/15.
//

#pragma once

#include "ofMain.h"
#include "BasicVisual.h"


class Laser: public BasicVisual {
    
    public:
    
        Laser(const BasicVisual& visual, int id, int channel);
    
        virtual ~Laser();
       
        void draw();
    
        int getId() const {return m_id;}
    
        int getChannel() const {return m_channel;}

    private:

        void setup();
        
    private:
            
        int m_id;

        int m_channel;
};




