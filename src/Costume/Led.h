//
//  Led.h
//
//  Created by Imanol Gomez on 09/07/15.
//

#pragma once

#include "ofMain.h"
#include "BasicVisual.h"


class Led: public BasicVisual {
    
    public:
    
        Led(const BasicVisual& visual, int id, int channel);
    
        virtual ~Led();
       
        void draw();
    
        int getId() const {return m_id;}
    
        int getChannel() const {return m_channel;}

    private:

        void setup();
        
    private:
            
        int m_id;

        int m_channel;
};




