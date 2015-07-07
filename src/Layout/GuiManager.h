/*
 *  GuiManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 07/07/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxGui.h"
//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application´s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    
public:

    //! Constructor
    GuiManager();

    //! Destructor
    ~GuiManager();

    //! Set-up the gui
    void setup();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    

private:
    
    // Fluid GUI
    ofxPanel			gui;
    
    ofParameter<float>	guiFPS;
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================


